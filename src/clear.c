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

void	clear_set(t_set *set)
{
	int		i;

	i = -1;	
	if (set->NO)
		free(set->NO);
	if (set->WE)
		free(set->WE);
	if (set->EA)
		free(set->EA);
	if (set->SO)
		free(set->SO);
	if (set->S)
		free(set->S);
	while (set->map && set->map[++i])
	{
		free(set->map[i]);
		set->map[i] = NULL;
	}
	free(set->map);
	set->map = NULL;
}
