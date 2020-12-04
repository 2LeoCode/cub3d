/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 16:30:08 by lsuardi           #+#    #+#             */
/*   Updated: 2020/12/04 18:45:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void		updatename(char *fname, size_t blen)
{
	if (fname[blen + 1] == '9')
	{
		if (fname[blen] == '9')
			fname[blen] = '0';
		else
			fname[blen]++;
		fname[blen + 1] = '0';
	}
	else
		fname[blen + 1]++;
}

static char		*getfilename(char *basename, char *ext)
{
	size_t	blen;
	size_t	elen;
	char	*filename;
	int		fdtest;

	blen = ft_strlen(basename);
	elen = ft_strlen(basename);
	if (!(filename = malloc(sizeof(char) * (blen + elen + 4))))
		return (NULL);
	ft_memcpy(filename, basename, blen);
	ft_memcpy(filename + blen, "00.", 3);
	ft_memcpy(filename + blen + 3, ext, elen + 1);
	while ((fdtest = open(filename, O_RDONLY)) > 0)
	{
		close(fdtest);
		updatename(filename, blen);
		if (filename[blen] == '0' && filename[blen + 1] == '0')
			return (filename);
	}
	close(fdtest);
	return (filename);
}

void			writeimg(int fd, unsigned char *img, t_mlximg *screen)
{
	int				extrabytes;
	int				i;

	extrabytes = 4 - ((screen->width * 3) % 4);
	extrabytes *= (extrabytes != 4);
	i = -1;
	while (++i < screen->height)
	{
		write(fd, &img[i * screen->width * 3], screen->width * 3);
		if (extrabytes)
		{
			write(fd, "\0\0", extrabytes - 1);
			write(fd, "\255", 1);
		}
	}
}

int				save_screen(t_mlximg *screen)
{
	t_bfh			fileheader;
	t_bih			infoheader;
	int				fd;
	unsigned char	*img;
	char			*filename;

	if (!(filename = getfilename("screenshots/save", "bmp"))
	|| ((fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU)) < 0)
	|| !(img = getchararray(screen)))
		return (error_wrong_map(ER_DEFLT));
	free(filename);
	fileheader = createbitmapfileheader(screen);
	infoheader = createbitmapinfoheader(screen);
	write(fd, &fileheader, 14);
	write(fd, &infoheader, 40);
	writeimg(fd, img, screen);
	free(img);
	close(fd);
	return (0);
}

void			exit_save(t_mlxvar *mlx)
{
	if (!(mlx->id = mlx_init())
	|| init_textures(mlx)
	|| update_rays(mlx)
	|| update_screen(mlx)
	|| draw_sprites(mlx))
	{
		ft_fputs(2, "Cub3d: Error while initializing screen.\n");
		clear_mlx_err(mlx);
	}
	save_screen(&mlx->screen);
	clear_mlx(mlx);
}
