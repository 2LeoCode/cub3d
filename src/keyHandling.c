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

void	checkKeys(t_mlxvar *mlxvar, int key, t_dVar d, int cSize)
{
	mlxvar->set->rot_hor -= (d.r - _2PI * (mlxvar->set->rot_hor - d.r < 0)) * (key == KEY_LEFT);
	mlxvar->set->rot_hor += (d.r - _2PI * (mlxvar->set->rot_hor + d.r > _2PI)) * (key == KEY_RIGHT);
	if ((key == KEY_UP) && !isCollide(mlxvar, mlxvar->posX + d.x, mlxvar->posY + d.y, cSize))
	{
		mlxvar->posX += d.x;
		mlxvar->posY += d.y;
	}
	if ((key == KEY_DOWN) && !isCollide(mlxvar, mlxvar->posX - d.x, mlxvar->posY - d.y, cSize))
	{
		mlxvar->posX -= d.x;
		mlxvar->posY -= d.y;
	}
}

int		keyIsPressed(int key, t_mlxvar *mlxvar)
{
	printf("%d\n", key);
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
