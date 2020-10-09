/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 16:30:08 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/09 16:30:08 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void		updateName(char *fName, size_t bLen)
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

static char		*getFileName(char *baseName, char *ext)
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

	if (!(fileName = getFileName("screenshot/save", "bmp"))
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
