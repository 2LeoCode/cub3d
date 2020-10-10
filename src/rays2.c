/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 22:45:20 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/10 22:46:17 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	initrayvert(t_rayvar *ur, t_mlxvar *mlx)
{
	ur->a = mlx->set->rot_hor + ur->r;
	if (ur->a < 0)
		ur->a = _2PI + ur->a;
	if (ur->a >= _2PI)
		ur->a = ur->a - _2PI;
	mlx->rays[ur->i].rot = ur->r;
	ur->t = -1 / (tan(ur->a) + (0.0001 * (!ur->a || ur->a == M_PI)));
	if (ur->a < M_PI)
	{
		ur->b.y = (int)mlx->posy + 1;
		ur->d.y = 1;
	}
	else if (!ur->a || ur->a == M_PI)
	{
		ur->b.y = mlx->posy;
		ur->d.y = 0;
	}
	else
	{
		ur->b.y = (int)mlx->posy - 0.0001;
		ur->d.y = -1;
	}
	ur->b.x = mlx->posx + (mlx->posy - ur->b.y) * ur->t;
	ur->d.x = -ur->d.y * ur->t;
}

void	initrayhor(t_rayvar *ur, t_mlxvar *mlx)
{
	ur->t = -tan(ur->a);
	if (ur->a < PI2 || ur->a > _3PI2)
	{
		ur->c.x = (int)mlx->posx + 1;
		ur->d.x = 1;
	}
	else if (ur->a == PI2 || ur->a == _3PI2)
	{
		ur->c.x = mlx->posx;
		ur->d.x = 0;
	}
	else
	{
		ur->c.x = (int)mlx->posx - 0.0001;
		ur->d.x = -1;
	}
	ur->c.y = mlx->posy + (mlx->posx - ur->c.x) * ur->t;
	ur->d.y = -ur->d.x * ur->t;
}
