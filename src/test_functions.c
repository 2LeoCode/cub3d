/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 19:15:25 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/19 19:15:25 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	ft_nputstr(char *str, int n)
{
	while (str && *str && n--)
	{
		write(1, str, 1);
		str++;
	}
}

void	display_chunks(t_chunk *chunk)
{
	int		i;
	int		j;
	t_chunk	*tmp;

	i = 0;
	while (chunk)
	{
		j = -1;
		tmp = chunk;
		while (++j < CHUNK_SIZE)
		{
			chunk = tmp;
			while (chunk && (chunk->y == i))
			{
				ft_nputstr(&chunk->chunk[j * CHUNK_SIZE], CHUNK_SIZE);
				chunk = chunk->next;
			}
			ft_putchar('\n');
		}
		i++;
	}
}
