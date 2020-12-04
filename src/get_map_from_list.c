/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_from_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 23:01:32 by lsuardi           #+#    #+#             */
/*   Updated: 2020/12/04 17:44:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int		getmapfromlist2(t_line **lst, t_set *set)
{
	int		i;
	int		j;
	t_line	*tmp;

	i = 0;
	j = -1;
	while (++j < set->mapx)
		set->map[i][j] = ' ';
	set->map[i][j] = 0;
	i += (set->mapy - 1);
	j = -1;
	while (++j < set->mapx)
		set->map[i][j] = ' ';
	set->map[i][j] = 0;
	tmp = *lst;
	i = 1;
	while (tmp)
	{
		get_line(set->map, i, tmp->line, set->mapx);
		tmp = tmp->next;
		i++;
	}
	return (0);
}

int				get_map_from_list(t_line **lst, t_set *set)
{
	int			i;

	set->mapy = get_map_y(*lst);
	if (!(set->map = (char**)malloc(sizeof(char*) * (set->mapy + 1))))
		return (ER_DEFLT);
	set->mapx = get_map_x(*lst);
	i = -1;
	while (++i < set->mapy)
		if (!(set->map[i] = (char*)malloc(sizeof(char) * (set->mapx + 1))))
			return (ER_DEFLT);
	set->map[i] = NULL;
	return (getmapfromlist2(lst, set));
}
