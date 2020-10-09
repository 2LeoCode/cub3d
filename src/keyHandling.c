/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyHandling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 23:40:43 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/09 23:40:43 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		isCollide(t_mlxvar *mlx, double px, double py)
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

void	checkKeys(t_mlxvar *mlxvar, int key, t_dVar d)
{
	mlxvar->set->rot_hor -= (d.r - _2PI * (mlxvar->set->rot_hor - d.r < 0)) * (key == KEY_LEFT);
	mlxvar->set->rot_hor += (d.r - _2PI * (mlxvar->set->rot_hor + d.r > _2PI)) * (key == KEY_RIGHT);
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
	if (((key == KEY_W) || (key == KEY_D)) && !isCollide(mlxvar, mlxvar->posX + d.x, mlxvar->posY + d.y))
	{
		mlxvar->posX += d.x;
		mlxvar->posY += d.y;
	}
	if (((key == KEY_S) || (key == KEY_A)) && !isCollide(mlxvar, mlxvar->posX - d.x, mlxvar->posY - d.y))
	{
		mlxvar->posX -= d.x;
		mlxvar->posY -= d.y;
	}
}

int		keyIsPressed(int key, t_mlxvar *mlxvar)
{
	if (key == KEY_ESC)
		return (clear_mlx(mlxvar));
	mlxvar->isKeyPressed = 1;
	mlxvar->lastKey = key;
	return (0);
}

int		keyIsReleased(int key, t_mlxvar *mlxvar)
{
	(void)key;
	mlxvar->isKeyPressed = 0;
	return (0);
}
