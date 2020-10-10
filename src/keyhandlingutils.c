/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandlingutils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 15:26:42 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/10 15:31:22 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		keycond1(t_mlxvar *mlxvar, int key, t_dvar d)
{
	return (((key == KEY_W) || (key == KEY_A))
	&& !iscollide(mlxvar, mlxvar->posx + d.x, mlxvar->posy + d.y));
}

int		keycond2(t_mlxvar *mlxvar, int key, t_dvar d)
{
	return (((key == KEY_S) || (key == KEY_A))
	&& !iscollide(mlxvar, mlxvar->posx - d.x, mlxvar->posy - d.y));
}
