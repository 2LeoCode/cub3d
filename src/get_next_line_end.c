/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_end.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 23:24:19 by lsuardi           #+#    #+#             */
/*   Updated: 2020/12/04 18:14:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	get_next_line_end(int fd, char **line)
{
	int		ret;

	ret = 1;
	while (ret)
	{
		free(*line);
		ret = get_next_line(fd, line);
	}
	close(fd);
	free(*line);
	*line = NULL;
}
