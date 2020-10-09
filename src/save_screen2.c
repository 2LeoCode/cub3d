/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_screen2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 16:30:36 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/09 16:30:36 by lsuardi          ###   ########.fr       */
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
