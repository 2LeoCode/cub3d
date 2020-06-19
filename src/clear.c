/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 22:43:31 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/16 22:43:31 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static char		*index_to_s(int index, t_set *set)
{
	if (index == C_NO)
		return (set->NO);
	if (index == C_SO)
		return (set->SO);
	if (index == C_WE)
		return (set->WE);
	if (index == C_EA)
		return (set->EA);
	if (index == C_S)
		return (set->S);
	return (NULL);
}

void			clear_set(t_set *set, t_bool *active)
{
	int		i;
	char	*to_free;

	i = -1;
	while (++i < NB_PARAMS)
		if (active[i] && ((to_free = index_to_s(i, set)) != NULL))
		{
			free(to_free);
			to_free = NULL;
		}
}
