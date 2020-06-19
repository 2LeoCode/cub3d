/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_chunks_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 23:50:49 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/18 23:50:49 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	fill_chunk_end(char *chunk, int startX, int startY)
{
	int		i;

	i = startY * CHUNK_SIZE + startX - 1;
	while (++i < (CHUNK_SIZE * CHUNK_SIZE))
		chunk[i] = ' ';
	chunk[i] = 0;
}

t_bool	are_chunk_lines_null(char **lines)
{
	int		i;

	i = -1;
	while (++i < CHUNK_SIZE)
		if (lines[i])
			return (false);
	return (true);
}
