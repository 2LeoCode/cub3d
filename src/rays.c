/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 21:56:43 by lsuardi           #+#    #+#             */
/*   Updated: 2020/08/20 21:56:43 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		update_rays(t_mlxvar *mlxvar)
{
	int			i;
	double		r;
	double		a;
	double		t;
	t_point		b;
	t_point		c;
	t_point		length;
	t_point		d;

	if (!mlxvar->rays && !(mlxvar->rays = malloc(sizeof(t_ray) * mlxvar->set->X)))
		return (-1);
	i = -1;
	r = -(mlxvar->set->FOV / 2);
	printf(mlxvar->set->rot_hor);
	while (++i < mlxvar->set->X)
	{
		a = mlxvar->set->rot_hor + r;
		if (a < 0)
			a = 2 * M_PI + a;
		if (a >= (2 * M_PI))
			a = 2 * M_PI - a;
		mlxvar->rays[i].rot = r;
		t = -1 / (tan(a) + (0.0001 * (!a || a == M_PI)));
		if (a < M_PI)
		{
			b.y = (int)mlxvar->posX + 1.0001;
			d.y = 1;
		}
		else if (!a || a == M_PI)
		{
			b.y = mlxvar->posY;
			d.y = 0;
		}
		else
		{
			b.y = (int)mlxvar->posY - 0.0001;
			d.y = -1;
		}
		b.x = mlxvar->posX + (mlxvar->posY - b.y) * t;
		d.x = -d.y * t;
		while ((b.x > 0) && (b.y > 0) && (b.x < mlxvar->set->mapX) && (b.y < mlxvar->set->mapY) && (mlxvar->set->map[(int)b.y][(int)b.x] - '1'))
		{
			b.x += d.x;
			b.y += d.y;
		}
		length.y = sqrt((b.x - mlxvar->posX) * (b.x - mlxvar->posX) + (b.y - mlxvar->posY) * (b.y - mlxvar->posY));
		t = -tan(a);
		if (a < (M_PI / 2) || a > (3 * M_PI / 2))
		{
			c.x = (int)mlxvar->posX + 1.0001;
			d.x = 1;
		}
		else if (a == (M_PI / 2) || a == (3 * M_PI / 2))
		{
			c.x = mlxvar->posY;
			d.x = 0;
		}
		else
		{
			c.x = (int)mlxvar->posX - 0.0001;
			d.x = -1;
		}
		c.y = mlxvar->posY + (mlxvar->posX - c.x) * t;
		d.y = -d.x * t;
		while ((c.x > 0) && (c.y > 0) && (c.x < mlxvar->set->mapX) && (c.y < mlxvar->set->mapY) && (mlxvar->set->map[(int)c.y][(int)c.x] - '1'))
		{
			c.y += d.y;
			c.x += d.x;
		}
		length.x = sqrt((c.x - mlxvar->posX) * (c.x - mlxvar->posX) + (c.y - mlxvar->posY) * (c.y - mlxvar->posY));
		if (length.y < length.x)
		{
			mlxvar->rays[i].siz = length.y;
			mlxvar->rays[i].texture = ((a < M_PI) ? &mlxvar->wallS : &mlxvar->wallN);
			mlxvar->rays[i].col_pos = (double)(b.x - (int)b.x) * mlxvar->rays[i].texture->width;
		}
		else
		{
			mlxvar->rays[i].siz = length.x;
			mlxvar->rays[i].texture = (((a > (M_PI / 2)) && (a < (3 * M_PI / 4))) ? &mlxvar->wallW : &mlxvar->wallE);
			mlxvar->rays[i].col_pos = (double)(c.y - (int)c.y) * mlxvar->rays[i].texture->width;
		}
		r += (mlxvar->set->FOV / mlxvar->set->X);
	}
	return (0);
}
