/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 00:22:47 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/15 00:22:47 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		write_header(t_bitmap_file_header bfh, t_bitmap_image_header bih, int fd)
{
	write(fd, &bfh.bitmap_type, 2);
	write(fd, &bfh.file_size, 4);
	write(fd, &bfh.reserved1, 2);
	write(fd, &bfh.reserved2, 2);
	write(fd, &bfh.offset_bits, 4);
	write(fd, &bih.size_header, 4);
	write(fd, &bih.width, 4);
	write(fd, &bih.height, 4);
	write(fd, &bih.planes, 2);
	write(fd, &bih.bit_count, 2);
	write(fd, &bih.compression, 4);
	write(fd, &bih.image_size, 4);
	write(fd, &bih.ppm_x, 4);
	write(fd, &bih.ppm_y, 4);
	write(fd, &bih.clr_used, 4);
	write(fd, &bih.clr_important, 4);
	return (0);
}

int		save_screen(t_mlximg *screen)
{
	t_bitmap_file_header	bfh;
	t_bitmap_image_header	bih;
	unsigned char			color[3];
	int						fd;
	int						i;
	unsigned char			*img;

	img = (unsigned char*)screen->img_data;
	if ((fd = open("save.bmp", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU)) < 0)
		return (error_wrong_map(ER_DEFLT));
	ft_memcpy(&bfh.bitmap_type, "BM", 2);
	bfh.file_size = screen->height * screen->width * 4 + 54;
	bfh.reserved1 = 0;
	bfh.reserved2 = 0;
	bfh.offset_bits = 0;

	bih.size_header = 14;
	bih.width = screen->width;
	bih.height = screen->height;
	bih.planes = 1;
	bih.bit_count = 24;
	bih.compression = 0;
	bih.image_size = bfh.file_size;
	bih.ppm_x = 300 * 39.375;
	bih.ppm_y = bih.ppm_x;
	bih.clr_used = 0;
	bih.clr_important = 0;
	if (write_header(bfh, bih, fd))
		return (error_wrong_map(ER_DEFLT));
	i = 0;
	while (i < bfh.file_size)
	{
		color[3] = img[++i];
		color[2] = img[++i];
		color[1] = img[++i];
		if (write(fd, &color, sizeof(color)) < 0)
			return (error_wrong_map(ER_DEFLT));
	}
	close(fd);
	return (0);
}

int		update_screen(t_mlxvar *mlxvar)
{
	int		i;
	int		j;
	double	k;
	double	size;
	int		l;
	
	if (!mlxvar->screen.img || !mlxvar->screen.img_data)
		return (clear_mlx(mlxvar));
	i = mlxvar->screen.width;
	while (--i >= 0)
	{
		size = (double)mlxvar->screen.height / (cos(mlxvar->rays[i].rot) * mlxvar->rays[i].siz);
		j = -1;
		while (++j < (int)(mlxvar->screen.height / 2))
			mlxvar->screen.img_data[j * mlxvar->screen.width + i] = mlxvar->set->C;
		while (++j < mlxvar->screen.height)
			mlxvar->screen.img_data[j * mlxvar->screen.width + i] = mlxvar->set->F;
		j = -1;
		l = (size > mlxvar->screen.height) ? 0 : (int)(mlxvar->screen.height / 2) - (size / 2);
		k = (size < mlxvar->screen.height) ? 0 : (((size / 2) - (mlxvar->screen.height / 2)) / size) * mlxvar->rays[i].texture->height;
		while (++j < (((int)size > mlxvar->screen.height) ? mlxvar->screen.height : (int)size))
		{
			mlxvar->screen.img_data[(l + j) * mlxvar->screen.width + i] = mlxvar->rays[i].texture->img_data[(int)k * mlxvar->rays[i].texture->width + mlxvar->rays[i].col_pos];
			k += mlxvar->rays[i].texture->height / size;
		}
	}
	return (0);
}

int		init_textures(t_mlxvar *mlxvar)
{
	mlxvar->wallN.img = NULL;
	mlxvar->wallN.img_data = NULL;
	mlxvar->wallE.img = NULL;
	mlxvar->wallE.img_data = NULL;
	mlxvar->wallS.img = NULL;
	mlxvar->wallS.img_data = NULL;
	mlxvar->wallW.img = NULL;
	mlxvar->wallW.img_data = NULL;
	mlxvar->sprite.img = NULL;
	mlxvar->sprite.img_data = NULL;
	mlxvar->screen.img = NULL;
	mlxvar->wallN.img_data = NULL;
	mlxvar->rays = NULL;
	mlxvar->screen.img = mlx_new_image(mlxvar->id, mlxvar->set->X, mlxvar->set->Y);
	mlxvar->screen.img_data = (int*)mlx_get_data_addr(mlxvar->screen.img, &mlxvar->screen.bpp, &mlxvar->screen.line_size, &mlxvar->screen.endian);
	mlxvar->screen.width = mlxvar->set->X;
	mlxvar->screen.height = mlxvar->set->Y;
	mlxvar->wallN.img = mlx_xpm_file_to_image(mlxvar->id , mlxvar->set->NO, &mlxvar->wallN.width, &mlxvar->wallN.height);
	mlxvar->wallN.img_data = (int*)mlx_get_data_addr(mlxvar->wallN.img, &mlxvar->wallN.bpp, &mlxvar->wallN.line_size, &mlxvar->wallN.endian);
	mlxvar->wallE.img = mlx_xpm_file_to_image(mlxvar->id , mlxvar->set->EA, &mlxvar->wallE.width, &mlxvar->wallE.height);
	mlxvar->wallE.img_data = (int*)mlx_get_data_addr(mlxvar->wallE.img, &mlxvar->wallE.bpp, &mlxvar->wallE.line_size, &mlxvar->wallE.endian);
	mlxvar->wallS.img = mlx_xpm_file_to_image(mlxvar->id , mlxvar->set->SO, &mlxvar->wallS.width, &mlxvar->wallS.height);
	mlxvar->wallS.img_data = (int*)mlx_get_data_addr(mlxvar->wallS.img, &mlxvar->wallS.bpp, &mlxvar->wallS.line_size, &mlxvar->wallS.endian);
	mlxvar->wallW.img = mlx_xpm_file_to_image(mlxvar->id , mlxvar->set->WE, &mlxvar->wallW.width, &mlxvar->wallW.height);
	mlxvar->wallW.img_data = (int*)mlx_get_data_addr(mlxvar->wallW.img, &mlxvar->wallW.bpp, &mlxvar->wallW.line_size, &mlxvar->wallW.endian);
	mlxvar->sprite.img = mlx_xpm_file_to_image(mlxvar->id , mlxvar->set->S, &mlxvar->sprite.width, &mlxvar->sprite.height);
	mlxvar->sprite.img_data = (int*)mlx_get_data_addr(mlxvar->sprite.img, &mlxvar->sprite.bpp, &mlxvar->sprite.line_size, &mlxvar->sprite.endian);
	if (!mlxvar->wallN.img || !mlxvar->wallN.img_data || !mlxvar->wallE.img
	|| !mlxvar->wallE.img_data || !mlxvar->wallS.img || !mlxvar->wallS.img_data
	|| !mlxvar->wallW.img || !mlxvar->wallW.img_data || !mlxvar->sprite.img
	|| !mlxvar->sprite.img_data	|| !mlxvar->screen.img || !mlxvar->screen.img_data)
		return (-1);
	return (0);
}

int		updateanddisplay(int key, t_mlxvar *mlxvar)
{
	double	dx;
	double	dy;
	double	dr;

	dx = (cos(mlxvar->set->rot_hor) / 20) * 4;
	dy = (sin(mlxvar->set->rot_hor) / 20) * 4;
	dr = (M_PI / 180) * 3;
	if (key == KEY_LEFT)
	{
		mlxvar->set->rot_hor -= dr;
		if (mlxvar->set->rot_hor < 0)
			mlxvar->set->rot_hor = _2PI + mlxvar->set->rot_hor;
	}
	if (key == KEY_RIGHT)
	{
		mlxvar->set->rot_hor += dr;
		if (mlxvar->set->rot_hor > _2PI)
			mlxvar->set->rot_hor = mlxvar->set->rot_hor - _2PI;
	}
	if ((key == KEY_UP) && (mlxvar->set->map[(int)(mlxvar->posY + dy)][(int)(mlxvar->posX + dx)] - '1'))
	{
		mlxvar->posX += dx;
		mlxvar->posY += dy;
	}
	if ((key == KEY_DOWN) && (mlxvar->set->map[(int)(mlxvar->posY - dy)][(int)(mlxvar->posX - dx)] - '1'))
	{
		mlxvar->posX -= dx;
		mlxvar->posY -= dy;
	}
	if (update_rays(mlxvar)
	|| update_screen(mlxvar))
		return (clear_mlx(mlxvar));
	mlx_put_image_to_window(mlxvar->id, mlxvar->win, mlxvar->screen.img, 0, 0);
	return (0);
}

int		cub3D(t_set *set, int flags)
{
	t_bool		save;
	t_mlxvar	mlxvar;

	save = false;
	if ((flags == SAVE) || (flags == (SAVE | BONUS)))
		save = true;
	mlxvar.set = set;
	display_map(mlxvar.set->map);
	printf("%f", mlxvar.set->FOV);
	mlxvar.id = NULL;
	mlxvar.win = NULL;
	mlxvar.screen.img = NULL;
	mlxvar.screen.img_data = NULL;
	mlxvar.rays = NULL;
	mlxvar.posX = (double)mlxvar.set->spawn.X + 0.5;
	mlxvar.posY = (double)mlxvar.set->spawn.Y + 0.5;
	if (!(mlxvar.id = mlx_init()) || init_textures(&mlxvar)
	|| !(mlxvar.win = mlx_new_window(mlxvar.id, set->X, set->Y, "Cub3D"))
	|| update_rays(&mlxvar) || update_screen(&mlxvar))
	{
		clear_set(set);
		clear_mlx(&mlxvar);
		return (ft_fputs(2, "Cub3D: Error while initializing window.\n"));
	}
	mlx_put_image_to_window(mlxvar.id, mlxvar.win, mlxvar.screen.img, 0, 0);
	if (save)
		save_screen(&mlxvar.screen);
	mlx_hook(mlxvar.win, KeyPress, KeyPressMask, &updateanddisplay, &mlxvar);
	mlx_loop(mlxvar.id);
	clear_mlx(&mlxvar);
	return (0);
}
