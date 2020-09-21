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

/*
const int BYTES_PER_PIXEL = 3; /// red, green, & blue
const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;

void generateBitmapImage(unsigned char* image, int height, int width, char* imageFileName);
unsigned char* createBitmapFileHeader(int height, int stride);
unsigned char* createBitmapInfoHeader(int height, int width);


int main ()
{
    int height = 361;
    int width = 867;
    unsigned char image[height][width][BYTES_PER_PIXEL];
    char* imageFileName = (char*) "bitmapImage.bmp";

    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            image[i][j][2] = (unsigned char) ( i * 255 / height );             ///red
            image[i][j][1] = (unsigned char) ( j * 255 / width );              ///green
            image[i][j][0] = (unsigned char) ( (i+j) * 255 / (height+width) ); ///blue
        }
    }

    generateBitmapImage((unsigned char*) image, height, width, imageFileName);
    printf("Image generated!!");
}


void generateBitmapImage (unsigned char* image, int height, int width, char* imageFileName)
{
    int widthInBytes = width * BYTES_PER_PIXEL;

    unsigned char padding[3] = {0, 0, 0};
    int paddingSize = (4 - (widthInBytes) % 4) % 4;

    int stride = (widthInBytes) + paddingSize;

    FILE* imageFile = fopen(imageFileName, "wb");

    unsigned char* fileHeader = createBitmapFileHeader(height, stride);
    fwrite(fileHeader, 1, FILE_HEADER_SIZE, imageFile);

    unsigned char* infoHeader = createBitmapInfoHeader(height, width);
    fwrite(infoHeader, 1, INFO_HEADER_SIZE, imageFile);

    int i;
    for (i = 0; i < height; i++) {
        fwrite(image + (i*widthInBytes), BYTES_PER_PIXEL, width, imageFile);
        fwrite(padding, 1, paddingSize, imageFile);
    }

    fclose(imageFile);
}

unsigned char* createBitmapFileHeader (int height, int stride)
{
    int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);

    static unsigned char fileHeader[] = {
        0,0,     /// signature
        0,0,0,0, /// image file size in bytes
        0,0,0,0, /// reserved
        0,0,0,0, /// start of pixel array
    };

    fileHeader[ 0] = (unsigned char)('B');
    fileHeader[ 1] = (unsigned char)('M');
    fileHeader[ 2] = (unsigned char)(fileSize      );
    fileHeader[ 3] = (unsigned char)(fileSize >>  8);
    fileHeader[ 4] = (unsigned char)(fileSize >> 16);
    fileHeader[ 5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

    return fileHeader;
}

unsigned char* createBitmapInfoHeader (int height, int width)
{
    static unsigned char infoHeader[] = {
        0,0,0,0, /// header size
        0,0,0,0, /// image width
        0,0,0,0, /// image height
        0,0,     /// number of color planes
        0,0,     /// bits per pixel
        0,0,0,0, /// compression
        0,0,0,0, /// image size
        0,0,0,0, /// horizontal resolution
        0,0,0,0, /// vertical resolution
        0,0,0,0, /// colors in color table
        0,0,0,0, /// important color count
    };

    infoHeader[ 0] = (unsigned char)(INFO_HEADER_SIZE);
    infoHeader[ 4] = (unsigned char)(width      );
    infoHeader[ 5] = (unsigned char)(width >>  8);
    infoHeader[ 6] = (unsigned char)(width >> 16);
    infoHeader[ 7] = (unsigned char)(width >> 24);
    infoHeader[ 8] = (unsigned char)(height      );
    infoHeader[ 9] = (unsigned char)(height >>  8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL*8);

    return infoHeader;
}

*/
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

/*void	draw_sprites(t_mlxvar *mlxvar)
{
	(void)mlxvar;
	int			i;
	int			j;
	double		k;
	double		l;
	double		lineSize;
	t_sprite	*lst;

	lst = mlxvar->sprites;
	while (lst)
	{
		lineSize = (double)mlxvar->screen.height / (cos(lst->rot) * lst->siz);
		l = (lineSize > mlxvar->screen.height) ? 0 : (int)(mlxvar->screen.height / 2) - (lineSize / 2);
		k = (lineSize < mlxvar->screen.height) ? 0 : (((lineSize / 2) - (mlxvar->screen.height / 2)) / lineSize) * mlxvar->sprite.height;
		i = (int)((double)lst->posX - (lineSize / 2) - 2);
		while (++i < (double)lst->posX + (lineSize / 2))
		{
			j = -1;
			while (++j < (((int)lineSize > mlxvar->screen.height) ? mlxvar->screen.height : (int)lineSize))
			{
				if (i > 0 && i < mlxvar->screen.width && mlxvar->sprite.img_data[(int)k * mlxvar->rays[i].texture->width + mlxvar->rays[i].col_pos])
				{
					mlxvar->screen.img_data[(int)((l + j) * mlxvar->screen.width + i)] = mlxvar->sprite.img_data[(int)k * mlxvar->rays[i].texture->width + mlxvar->rays[i].col_pos];
					k += mlxvar->sprite.height / lineSize;
				}
			}
		}
	}
}*/

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

	r = (playerSize / 2);
	i = 0;
	while (i < _2PI)
	{
		if (mlx->set->map[(int)(py + r * sin(i))][(int)(px + r * cos(i))] == '1')
			return (1);
		i += (M_PI / 10);
	}
	return (0);
}

int		draw_sprites(t_mlxvar *mlx)
{
	t_sprite	*tmp;
	double		size;
	t_coord		a;
	t_coord		b;
	t_point		texture;
	t_point		d;

	tmp = mlx->set->sprites;
	while (!tmp->isLast)
	{
		size = (double)mlx->screen.height / (cos(tmp->a) * tmp->size);
		a.X = tmp->screenX - (size / 2) - 1;
		a.Y = (mlx->screen.height / 2) - (size / 2) - 1;
		b.X = tmp->screenX + (size / 2);
		b.Y = (mlx->screen.height / 2) + (size / 2);
		d.x = mlx->sprite.width / size;
		d.y = mlx->sprite.height / size;
		texture.x = 0;
		while (++a.X < b.X)
		{
			if ((a.X >= 0) && (a.X < mlx->screen.width))
			{
				texture.y = 0;
				a.Y = (mlx->screen.height / 2) - (size / 2) - 1;
				b.Y = (mlx->screen.height / 2) + (size / 2);
				while (++a.Y < b.Y)
				{
					if ((a.Y >= 0) && (a.Y < mlx->screen.height) && mlx->sprite.img_data[(int)(texture.y * mlx->sprite.width + texture.x)])
						mlx->screen.img_data[(int)(a.Y * mlx->screen.width + a.X)] = mlx->sprite.img_data[(int)(texture.y * mlx->sprite.width + texture.x)];
					texture.y += d.y;
				}
			}
			texture.x += d.x;
		}
		tmp++;
	}
	return (0);
}

int		updateanddisplay(int key, t_mlxvar *mlxvar)
{
	double	dx;
	double	dy;
	double	dr;
	double	cSize;

	cSize = 0.3;
	dx = (cos(mlxvar->set->rot_hor) / 10) * 4;
	dy = (sin(mlxvar->set->rot_hor) / 10) * 4;
	dr = (M_PI / 180) * 3;
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

int		test(XMotionEvent *event, void *param)
{
	printf("%d %d\n", event->x, event->y);
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
	mlxvar.id = NULL;
	mlxvar.win = NULL;
	mlxvar.screen.img = NULL;
	mlxvar.screen.img_data = NULL;
	mlxvar.rays = NULL;
	mlxvar.posX = (double)mlxvar.set->spawn.X + 0.5;
	mlxvar.posY = (double)mlxvar.set->spawn.Y + 0.5;
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
	mlx_hook(mlxvar.win, KeyPress, KeyPressMask, &updateanddisplay, &mlxvar);
	mlx_hook(mlxvar.win, MotionNotify, PointerMotionMask, &test, (void*)0);
	mlx_loop(mlxvar.id);
	clear_mlx(&mlxvar);
	return (0);
}
