/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 21:56:43 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/10 23:17:46 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	gettextcoord(t_rayvar *ur, t_mlxvar *mlx)
{
	if (ur->length.y < ur->length.x)
	{
		mlx->rays[ur->i].siz = ur->length.y;
		mlx->rays[ur->i].texture = ((ur->a < M_PI) ? &mlx->walls : &mlx->walln);
		mlx->rays[ur->i].col_pos = (double)(ur->b.x - (int)ur->b.x
) * mlx->rays[ur->i].texture->width;
	}
	else
	{
		mlx->rays[ur->i].siz = ur->length.x;
		mlx->rays[ur->i].texture = (((ur->a > PI2) && (ur->a < _3PI2)) ?
		&mlx->wallw : &mlx->walle);
		mlx->rays[ur->i].col_pos = (double)(ur->c.y - (int)ur->c.y
) * mlx->rays[ur->i].texture->width;
	}
}

int		shootrayvert(t_rayvar *ur, t_mlxvar *mlx)
{
	while (ur->a && (ur->a - M_PI) && (ur->b.x > 0) && (ur->b.y > 0
) && (ur->b.x < mlx->set->mapx) && (ur->b.y < mlx->set->mapy
) && (mlx->set->map[(int)ur->b.y][(int)ur->b.x] - '1'))
	{
		if ((mlx->set->map[(int)ur->b.y][(int)ur->b.x] == '2')
		&& !(mlx->splist = splistaddfront(mlx, mlx->splist,
		(double)((int)ur->b.x + 0.5), (double)((int)ur->b.y + 0.5))))
			return (-1);
		ur->b.x += ur->d.x;
		ur->b.y += ur->d.y;
	}
	ur->length.y = sqrt((ur->b.x - mlx->posx) * (ur->b.x - mlx->posx
) + (ur->b.y - mlx->posy) * (ur->b.y - mlx->posy));
	return (0);
}

int		shootrayhor(t_rayvar *ur, t_mlxvar *mlx)
{
	while ((ur->a - PI2) && (ur->a - _3PI2) && (ur->c.x > 0) && (ur->c.y > 0)
	&& (ur->c.x < mlx->set->mapx) && (ur->c.y < mlx->set->mapy)
	&& (mlx->set->map[(int)ur->c.y][(int)ur->c.x] - '1'))
	{
		if ((mlx->set->map[(int)ur->c.y][(int)ur->c.x] == '2')
		&& !(mlx->splist = splistaddfront(mlx->posx, mlx->posy, mlx->splist,
		(double)((int)ur->c.x + 0.5), (double)((int)ur->c.y + 0.5))))
			return (-1);
		ur->c.y += ur->d.y;
		ur->c.x += ur->d.x;
	}
	ur->length.x = sqrt((ur->c.x - mlx->posx) * (ur->c.x - mlx->posx
) + (ur->c.y - mlx->posy) * (ur->c.y - mlx->posy));
	return (0);
}

int		update_rays(t_mlxvar *mlx)
{
	t_rayvar	ur;

	mlx->splist = NULL;
	if (!mlx->rays && !(mlx->rays = malloc(sizeof(t_ray) * mlx->set->x)))
		return (-1);
	ur.i = -1;
	ur.r = -(mlx->set->fov / 2);
	while (++ur.i < mlx->set->x)
	{
		initrayvert(&ur, mlx);
		if (shootrayvert(&ur, mlx))
			return (freespfail(&mlx->splist));
		initrayhor(&ur, mlx);
		if (shootrayhor(&ur, mlx))
			return (freespfail(&mlx->splist));
		gettextcoord(&ur, mlx);
		ur.r += (mlx->set->fov / mlx->set->x);
	}
	sortsplist(&mlx->splist);
	return (0);
}
