/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 14:06:54 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/16 14:06:54 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		file_size(char *path)
{
	char 	buf[BUFFER_GET_FILE];
	int		fd;
	int		ret;
	int		i;

	i = 0;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (-1);
	while ((ret = read(fd, &buf, BUFFER_GET_FILE)) > 0)
		i += ret;
	close(fd);
	return ((ret < 0) ? -1 : i);
}

char	*get_file(char *path)
{
	int		len;
	int		fd;
	char	*tmp;

	if (((fd = open(path, O_RDONLY)) < 0) || ((len = file_size(path)) < 0)
	|| !(tmp = (char*)malloc(sizeof(char) * (len + 1))))
		return (error_s(errno));
	read(fd, tmp, len);
	close(fd);
	tmp[len] = 0;
	return (tmp);
}
