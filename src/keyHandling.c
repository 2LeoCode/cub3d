/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 23:40:43 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/10 15:28:37 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		iscollide(t_mlxvar *mlx, double px, double py)
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

void	checkkeys(t_mlxvar *mlxvar, int key, t_dvar d)
{
	mlxvar->set->rot_hor -= (d.r - _2PI * (mlxvar->set->rot_hor - d.r < 0))
	* (key == KEY_LEFT);
	mlxvar->set->rot_hor += (d.r - _2PI * (mlxvar->set->rot_hor + d.r > _2pi))
	* (key == KEY_RIGHT);
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
	if (keycond2(mlxvar, key, d))
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
