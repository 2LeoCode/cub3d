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

int		update_sprites(t_mlxvar *mlx)
{
	t_sprite	*tmp;

	tmp = mlx->set->sprites;
	while (!tmp->isLast)
	{
		tmp->size = sqrt((tmp->pos.x - mlx->posX) * (tmp->pos.x - mlx->posX) + (tmp->pos.y - mlx->posY) * (tmp->pos.y - mlx->posY));
		tmp->a = mlx->set->FOV / 2 + acos((tmp->pos.x - mlx->posX) / tmp->size);
		tmp->screenX = mlx->screen.width / 2 + (mlx->screen.width / 2) * a / (mlx->set->FOV / 2);
		tmp++;
	}
	return (0);
}

int		check_visible(t_mlxvar *mlx, double len, int i)
{
	t_sprite	*tmp;

	tmp = mlx->set->sprites;
	while (!tmp->isLast)
	{
		if ((tmp->screenX == i) && (tmp->size < len))
			tmp->inSight = 1;
		tmp++;
	}
	return (0);
}

void	sprite_swap(t_sprite *a, t_sprite *b)
{
	t_sprite	c;

	c.a = a->a;
	c.inSight = a->inSight;
	c.pos.x = a->pos.x;
	c.pos.y = a->pos.y;
	c.screenX = a->screenX;
	c.size = a->size;

	a->a = b->a;
	a->inSight = b->inSight;
	a->pos.x = b->pos.x;
	a->pos.y = b->pos.y;
	a->screenX = b->screenX;
	a->size = b->size;

	b->a = c.a;
	b->inSight = c.inSight;
	b->pos.x = c.pos.x;
	b->pos.y = c.pos.y;
	b->screenX = c.screenX;
	b->size = c.size;
}

void	sort_sprites(t_sprite *sprites)
{
	t_sprite	*head;

	while (!sprites->isLast)
	{
		head = sprites;
		while (!((++head)->isLast))
			if (head->size < sprites->size)
				sprite_swap(head, sprites);
		sprites++;
	}
}

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
	while (++i < mlxvar->set->X)
	{
		a = mlxvar->set->rot_hor + r;
		if (a < 0)
			a = _2PI + a;
		if (a >= _2PI)
			a = a - _2PI;
		mlxvar->rays[i].rot = r;
		t = -1 / (tan(a) + (0.0001 * (!a || a == M_PI)));
		if (a < M_PI)
		{
			b.y = (int)mlxvar->posY + 1;
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
		while (a && (a - M_PI) && (b.x > 0) && (b.y > 0) && (b.x < mlxvar->set->mapX) && (b.y < mlxvar->set->mapY) && (mlxvar->set->map[(int)b.y][(int)b.x] - '1'))
		{
			b.x += d.x;
			b.y += d.y;
		}
		length.y = sqrt((b.x - mlxvar->posX) * (b.x - mlxvar->posX) + (b.y - mlxvar->posY) * (b.y - mlxvar->posY));
		t = -tan(a);
		if (a < PI2 || a > _3PI2)
		{
			c.x = (int)mlxvar->posX + 1;
			d.x = 1;
		}
		else if (a == PI2 || a == _3PI2)
		{
			c.x = mlxvar->posX;
			d.x = 0;
		}
		else
		{
			c.x = (int)mlxvar->posX - 0.0001;
			d.x = -1;
		}
		c.y = mlxvar->posY + (mlxvar->posX - c.x) * t;
		d.y = -d.x * t;
		while ((a - PI2) && (a - _3PI2) && (c.x > 0) && (c.y > 0) && (c.x < mlxvar->set->mapX) && (c.y < mlxvar->set->mapY) && (mlxvar->set->map[(int)c.y][(int)c.x] - '1'))
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
			mlxvar->rays[i].texture = (((a > PI2) && (a < _3PI2)) ? &mlxvar->wallW : &mlxvar->wallE);
			mlxvar->rays[i].col_pos = (double)(c.y - (int)c.y) * mlxvar->rays[i].texture->width;
		}
		r += (mlxvar->set->FOV / mlxvar->set->X);
	}
	update_sprites(mlxvar);
	sort_sprites(mlxvar->set->sprites);
	return (0);
}
