/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 23:40:43 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/10 22:35:24 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdio.h>

void	checkkeys(t_mlxvar *mlxvar, int key, t_dvar d)
{
	mlxvar->set->rot_hor -= (d.r - _2PI * (mlxvar->set->rot_hor - d.r < 0)
	) * (key == KEY_LEFT);
	mlxvar->set->rot_hor += (d.r - _2PI * (mlxvar->set->rot_hor + d.r > _2PI)
	) * (key == KEY_RIGHT);
	if ((key == KEY_S) || (key == KEY_W))
	{
		d.x = (cos(mlxvar->set->rot_hor) / 25);
		d.y = (sin(mlxvar->set->rot_hor) / 25);
	}
	else if ((key == KEY_A) || (key == KEY_D))
	{
		d.x = (cos(mlxvar->set->rot_hor + PI2) / 25);
		d.y = (sin(mlxvar->set->rot_hor + PI2) / 25);
	}
	if (keycond1(mlxvar, key, d))
	{
		mlxvar->posx += d.x;
		mlxvar->posy += d.y;
	}
	else if (keycond2(mlxvar, key, d))
	{
		mlxvar->posx -= d.x;
		mlxvar->posy -= d.y;
	}
}

int		keyispressed(int key, t_mlxvar *mlxvar)
{
	if (key == KEY_ESC)
		return (clear_mlx(mlxvar));
	mlxvar->iskeypressed = 1;
	mlxvar->lastkey = key;
	return (0);
}

int		keyisreleased(int key, t_mlxvar *mlxvar)
{
	(void)key;
	mlxvar->iskeypressed = 0;
	return (0);
}
