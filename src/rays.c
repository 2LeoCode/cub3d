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
	t_point		b;
	t_point		c;
	t_point		length;
	double		d;

	if (!mlxvar->rays && !(mlxvar->rays = malloc(sizeof(t_ray) * mlxvar->set->X)))
		return (-1);
	i = -1;
	r = -(mlxvar->set->FOV / 2);
	while (++i < mlxvar->set->X)
	{
		a = mlxvar->set->rot_hor + r;
		if (a < 0)
			a = 2 * M_PI + ((a > (2 * M_PI)) ? a : -a);
		mlxvar->rays[i].rot = r;
		d = 1 / (tan(a) + 0.0001);
		if (a > M_PI / 2 && a < (3 * M_PI / 2))
			d = -d;
		if (a <= M_PI)
			b.y = (int)mlxvar->posY + 1.0001;
		else if (!a || a == M_PI)
			b.y = mlxvar->posY;
		else
			b.y = (int)mlxvar->posY - 0.0001;
		b.x = mlxvar->posX + ft_dabs(b.y - mlxvar->posY) * d;
		while ((b.x > 0) && (b.y > 0) && (b.x < mlxvar->set->mapX) && (b.y < mlxvar->set->mapY) && (mlxvar->set->map[(int)b.y][(int)b.x] - '1'))
		{
			b.x += d;
			printf("%.10lf %lf %lf\n", d, b.x, b.y);
			if (a < M_PI)
				b.y++;
			else if ((a > M_PI) && (a < M_PI / 2))
				b.y--;
		}
		length.y = sqrt((b.x - mlxvar->posX) * (b.x - mlxvar->posX) + (b.y - mlxvar->posY) * (b.y - mlxvar->posY));
		d = 1 / d;
		if (a <= M_PI / 2)
			c.y = (int)mlxvar->posY + 1.0001;
		else if (a == (M_PI / 2) || a == (3 * M_PI / 2))
			c.y = mlxvar->posY;
		else
			c.y = (int)mlxvar->posY - 0.0001;
		c.x = mlxvar->posY + ft_dabs(c.x - mlxvar->posX) * d;
		while ((c.x > 0) && (c.y > 0) && (c.x < mlxvar->set->mapX) && (c.y < mlxvar->set->mapY) && (mlxvar->set->map[(int)c.y][(int)c.x] - '1'))
		{
			c.y += d;
			if (a < (M_PI / 2) || a > (3 * M_PI / 2))
				c.x++;
			else if (a > (M_PI / 2) && a < (3 * M_PI / 2))
				c.x--;
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
