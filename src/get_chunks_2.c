/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_chunks_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:35:56 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/18 22:35:56 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int		get_one_chunk_4(t_chunk *last, char **lines, t_coord *pos)
{
	int		ret;
	int		i;
	int		j;

	j = -1;
	ret = 0;
	while (++j < CHUNK_SIZE)
	{
		i = -1;
		while (++i < CHUNK_SIZE)
			if (!lines[j][i] || ft_isspace(lines[j][i]))
			{
				fill_chunk_end(last->chunk, i, j);
				ret++;
				break ;
			}
			else
				last->chunk[j * CHUNK_SIZE + i] = lines[j][i];
	}
	last->chunk[CHUNK_SIZE * CHUNK_SIZE] = 0;
	return (ret);
}

static t_chunk	*get_one_chunk_3(t_set *set, int x, int y);
{
	t_chunk		*last;

	if (!set->chunks)
	{
		if (!(set->chunks = lst_chunk_new(x, y)))
			return (NULL);
		last = set->chunks;
	}
	else
	{
		if (!(last = lst_chunk_new(x, y)))
		{
			lst_chunk_clr(&set->chunks);
			return (NULL);
		}
		lst_chunk_last(set->chunks)->next = last;
	}
	return (last);
}

static int		get_one_chunk_2(char **lines, t_line **tmp)
{
	int		i;

	i = -1;
	while (++i < CHUNK_SIZE)
	{
		if (!*tmp)
			lines[i] = NULL;
		else
		{
			lines[i] = (*tmp)->line;
			*tmp = (*tmp)->next;
		}	
	}
	if (are_chunk_lines_null(lines))
		return (0);
	return (1);
}

int				get_one_chunk(t_set *set, t_line **map)
{
	char			*lines[CHUNK_SIZE];
	static t_coord	pos;
	t_line			*tmp;
	t_chunk			*last;
	int				count;

	if (!get_one_chunk_2(lines, &tmp))
		return (0);
	if (!(last = get_one_chunk_3(set, pos.X, pos.Y)))
		return (error_wrong_map(ER_DEFLT));
	count = get_one_chunk_4(last, lines, &pos);
	pos.X++;
	if (count == 4)
	{
		pos.Y++;
		pos.X = 0;
		*map = tmp;
	}
	return (1);
}
