/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 00:22:47 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/15 00:22:47 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


int		cub3D(t_set *set, int flags)
{
	t_bool		save;
	t_mlxvar	mlxvar;
	int			check;

	save = false;
	if ((flags == SAVE) || (flags == (SAVE | BONUS)))
		save = true;
	(void)save;
	(void)mlxvar;
	(void)check;
	display_map(set->map);
	return (0);
}
