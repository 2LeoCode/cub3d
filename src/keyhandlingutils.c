/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandlingutils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 15:26:42 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/10 22:11:12 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	iscollide(t_mlxvar *mlx, double px, double py)
{
	double	i;
	double	y;
	double	x;

	i = 0;
	while (i < _2PI)
	{
		y = py + sin(i) / 4;
		x = px + cos(i) / 4;
		if (mlx->set->map[(int)y][(int)x] == '1'
		|| mlx->set->map[(int)y][(int)x] == '2')
			return (1);
		i += (M_PI / 10);
	}
	return (0);
}

int			keycond1(t_mlxvar *mlxvar, int key, t_dvar d)
{
	return (((key == KEY_W) || (key == KEY_A))
	&& !iscollide(mlxvar, mlxvar->posx + d.x, mlxvar->posy + d.y));
}

int			keycond2(t_mlxvar *mlxvar, int key, t_dvar d)
{
	return (((key == KEY_S) || (key == KEY_A))
	&& !iscollide(mlxvar, mlxvar->posx - d.x, mlxvar->posy - d.y));
}
