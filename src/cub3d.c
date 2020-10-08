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

unsigned char	*getCharArray(t_mlximg *screen)
{
	unsigned char	*img;
	int 			size;
	int				i;

	size = screen->width * screen->height;
	if (!(img = (unsigned char*)malloc(sizeof(unsigned char) * size * 3)))
		return (NULL);
	i = -1;
	while (++i < size)
	{
		img[i * 3] = screen->img_data[i];
		img[i * 3 + 1] = (screen->img_data[i] >> 8);
		img[i * 3 + 2] = (screen->img_data[i] >> 16);
	}
	return (img);
}

t_bih			createBitmapInfoHeader(t_mlximg *screen)
{
	t_bih	infoHeader;
	int		ppm;

	ppm = 200 * 39.375;
	infoHeader.size_header = 40;
	infoHeader.width = screen->width;
	infoHeader.height = screen->height;
	infoHeader.planes = 1;
	infoHeader.bit_count = 24;
	infoHeader.compression = 0;
	infoHeader.image_size = infoHeader.width * infoHeader.height;
	infoHeader.ppm_x = ppm;
	infoHeader.ppm_y = ppm;
	infoHeader.clr_used = 0;
	infoHeader.clr_important = 0;
	return (infoHeader);
}

t_bfh			createBitmapFileHeader(t_mlximg *screen)
{
	t_bfh	fileHeader;

	fileHeader.bitmap_type[0] = 'B';
	fileHeader.bitmap_type[1] = 'M';
	fileHeader.file_size = 54 + 3 * screen->width * screen->height;
	fileHeader.reserved1 = 0;
	fileHeader.reserved2 = 0;
	fileHeader.offset_bits = 0;
	return (fileHeader);
}

void			updateName(char *fName, size_t bLen)
{
	if (fName[bLen + 1] == '9')
	{
		if (fName[bLen] == '9')
			fName[bLen] = '0';
		else
			fName[bLen]++;
		fName[bLen + 1] = '0';
	}
	else
		fName[bLen + 1]++;
}

char			*getFileName(char *baseName, char *ext)
{
	size_t	bLen;
	size_t	eLen;
	char	*fileName;
	int		fdTest;

	bLen = ft_strlen(baseName);
	eLen = ft_strlen(baseName);
	if (!(fileName = malloc(sizeof(char) * (bLen + eLen + 4))))
		return (NULL);
	ft_memcpy(fileName, baseName, bLen);
	ft_memcpy(fileName + bLen, "00.", 3);
	ft_memcpy(fileName + bLen + 3, ext, eLen + 1);
	while ((fdTest = open(fileName, O_RDONLY)) > 0)
	{
		close(fdTest);
		updateName(fileName, bLen);
		if (fileName[bLen] == '0' && fileName[bLen + 1] == '0')
			return (fileName);
	}
	close(fdTest);
	return (fileName);
}

int				save_screen(t_mlximg *screen)
{
	t_bfh			fileHeader;
	t_bih			infoHeader;
	int				fd;
	unsigned char	*img;
	char			*fileName;

	if (!(fileName = getFileName("save", "bmp"))
	|| ((fd = open(fileName, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU)) < 0)
	|| !(img = getCharArray(screen)))
		return (error_wrong_map(ER_DEFLT));
	free(fileName);
	fileHeader = createBitmapFileHeader(screen);
	infoHeader = createBitmapInfoHeader(screen);
	write(fd, &fileHeader, 14);
	write(fd, &infoHeader, 40);
	write(fd, img, screen->width * screen->height * 3);
	free(img);
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

int		isCollide(t_mlxvar *mlx, double px, double py, double playerSize)
{
	double	r;
	double	i;
	double	y;
	double	x;

	r = (playerSize / 2);
	i = 0;
	while (i < _2PI)
	{
		y = py + r * sin(i);
		x = px + r * cos(i);
		if (mlx->set->map[(int)y][(int)x] == '1'
		|| mlx->set->map[(int)y][(int)x] == '2')
			return (1);
		i += (M_PI / 10);
	}
	return (0);
}

int		draw_sprites(t_mlxvar *mlx)
{
	double		size;
	double		a;
	t_coord		end;
	t_coord		d;
	t_spList	*lst;
	t_coord		screenC;
	t_point		textC;
	t_point		rap;

	lst = mlx->spList;
	while (lst)
	{
		a = lst->a - mlx->set->rot_hor;
		if (a < 0)
			a += _2PI;
		size = (double)mlx->screen.height / (cos(a) * lst->len);
		screenC.X = ((a + (mlx->set->FOV / 2) / mlx->set->FOV) * mlx->screen.width) - (size / 2);
		printf("a: %lf, screenX: %d, size: %lf\n", a, screenC.X, size);
		end.X = ((screenC.X + size) < mlx->screen.width) ? (screenC.X + size) : mlx->screen.width;
		d.X = -screenC.X * (screenC.X < 0);
		screenC.X += d.X;
		textC.x = (d.X / size) * mlx->sprite.width;
		rap.x = (1 / size) * mlx->sprite.width;
		rap.y = (1 / size) * mlx->sprite.height;
		while (screenC.X < end.X)
		{
			screenC.Y = (mlx->screen.height / 2) - (size / 2);
			end.Y = ((screenC.Y + size) < mlx->screen.height) ? (screenC.Y + size) : mlx->screen.height;
			d.Y = -screenC.Y * (screenC.Y < 0);
			screenC.Y += d.Y;
			textC.y = (d.Y / size) * mlx->sprite.width;
			while (screenC.Y < end.Y)
			{
				if (mlx->sprite.img_data[(int)textC.y * mlx->sprite.width + (int)textC.x] && (mlx->rays[screenC.X].siz > lst->len))
					mlx->screen.img_data[screenC.Y * mlx->screen.width + screenC.X] = mlx->sprite.img_data[(int)textC.y * mlx->sprite.width + (int)textC.x];
				screenC.Y++;
				textC.y += rap.y;
			}
			screenC.X++;
			textC.x += rap.x;
		}
		lst = lst->next;
	}
	freeSpList(&mlx->spList);
	return (0);
}

int		updateanddisplay(t_mlxvar *mlxvar)
{
	int			key;
	double		dx;
	double		dy;
	double		dr;
	double		cSize;

	if (!mlxvar->isKeyPressed)
		return (0);
	key = mlxvar->lastKey;
	cSize = 0.3;
	dx = (cos(mlxvar->set->rot_hor) / 20);
	dy = (sin(mlxvar->set->rot_hor) / 20);
	dr = (M_PI / 180);
	mlxvar->set->rot_hor -= (dr - _2PI * (mlxvar->set->rot_hor - dr < 0)) * (key == KEY_LEFT);
	mlxvar->set->rot_hor += (dr - _2PI * (mlxvar->set->rot_hor + dr > _2PI)) * (key == KEY_RIGHT);
	if ((key == KEY_UP) && !isCollide(mlxvar, mlxvar->posX + dx, mlxvar->posY + dy, cSize))
	{
		mlxvar->posX += dx;
		mlxvar->posY += dy;
	}
	if ((key == KEY_DOWN) && !isCollide(mlxvar, mlxvar->posX - dx, mlxvar->posY - dy, cSize))
	{
		mlxvar->posX -= dx;
		mlxvar->posY -= dy;
	}
	if (update_rays(mlxvar)
	|| update_screen(mlxvar) || draw_sprites(mlxvar))
		return (clear_mlx(mlxvar));
	mlx_put_image_to_window(mlxvar->id, mlxvar->win, mlxvar->screen.img, 0, 0);
	return (0);
}

int		keyIsPressed(int key, t_mlxvar *mlxvar)
{
	mlxvar->isKeyPressed = 1;
	mlxvar->lastKey = key;
	return (0);
}

int		keyIsReleased(int key, t_mlxvar *mlxvar)
{
	(void)key;
	mlxvar->isKeyPressed = 0;
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
	mlxvar.id = NULL;
	mlxvar.win = NULL;
	mlxvar.screen.img = NULL;
	mlxvar.screen.img_data = NULL;
	mlxvar.rays = NULL;
	mlxvar.posX = (double)mlxvar.set->spawn.X + 0.5;
	mlxvar.posY = (double)mlxvar.set->spawn.Y + 0.5;
	mlxvar.lastKey = -1;
	mlxvar.isKeyPressed = 0;
	if (!(mlxvar.id = mlx_init()) || init_textures(&mlxvar)
	|| !(mlxvar.win = mlx_new_window(mlxvar.id, set->X, set->Y, "Cub3D"))
	|| update_rays(&mlxvar) || update_screen(&mlxvar) || draw_sprites(&mlxvar))
	{
		clear_set(set);
		clear_mlx(&mlxvar);
		return (ft_fputs(2, "Cub3D: Error while initializing window.\n"));
	}
	mlx_put_image_to_window(mlxvar.id, mlxvar.win, mlxvar.screen.img, 0, 0);
	if (save)
		save_screen(&mlxvar.screen);
	mlx_loop_hook(mlxvar.id, &updateanddisplay, &mlxvar);
	mlx_hook(mlxvar.win, KeyPress, KeyPressMask, &keyIsPressed, &mlxvar);
	mlx_hook(mlxvar.win, KeyRelease, KeyReleaseMask, &keyIsReleased, &mlxvar);
	mlx_loop(mlxvar.id);
	clear_mlx(&mlxvar);
	return (0);
}
