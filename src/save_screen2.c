/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_screen2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 16:30:36 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/10 22:57:56 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

unsigned char	*getchararray(t_mlximg *screen)
{
	unsigned char	*img;
	int				size;
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

t_bih			createbitmapinfoheader(t_mlximg *screen)
{
	t_bih	infoheader;
	int		ppm;

	ppm = 200 * 39.375;
	infoheader.size_header = 40;
	infoheader.width = screen->width;
	infoheader.height = screen->height;
	infoheader.planes = 1;
	infoheader.bit_count = 24;
	infoheader.compression = 0;
	infoheader.image_size = infoheader.width * infoheader.height;
	infoheader.ppm_x = ppm;
	infoheader.ppm_y = ppm;
	infoheader.clr_used = 0;
	infoheader.clr_important = 0;
	return (infoheader);
}

t_bfh			createbitmapfileheader(t_mlximg *screen)
{
	t_bfh	fileheader;

	fileheader.bitmap_type[0] = 'B';
	fileheader.bitmap_type[1] = 'M';
	fileheader.file_size = 54 + 3 * screen->width * screen->height;
	fileheader.reserved1 = 0;
	fileheader.reserved2 = 0;
	fileheader.offset_bits = 0;
	return (fileheader);
}
