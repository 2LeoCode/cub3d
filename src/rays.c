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

t_sprite	*raylist_add(int mx, int my, int px, int r, t_sprite *lst)
{
	t_sprite	*tmp;

	if (!(tmp = malloc(sizeof(t_sprite))))
		return (NULL);
	tmp->mapX = mx;
	tmp->mapY = my;
	tmp->posX = px;
	tmp->rot = r;
	tmp->next = lst;
	return (tmp);
}

void		lst_sort_siz(t_sprite **lst)
{
	t_sprite *prev;
	t_sprite *tmp;
	t_sprite *cur;
	t_sprite *head;

	if (!lst || !*lst)
		return ;
	cur = *lst;
	head = cur->next;
	prev = NULL;
	while (cur)
	{
		while (head)
		{
			if (head->siz > cur->siz)
			{
				if (prev)
					prev->next = head;
				tmp = head->next;
				head->next = cur->next;
				cur->next = tmp;
			}
			head = head->next;
		}
		prev = cur;
		cur = cur->next;
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
	raylist_clear(&mlxvar->sprites);
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
			if (mlxvar->set->map[(int)b.y][(int)b.x] == '2')
				if (mlxvar->sprites && ((int)b.y - mlxvar->sprites->mapY) && ((int)b.x - mlxvar->sprites->mapX) && !(mlxvar->sprites = raylist_add(b.x, b.y, i, r, mlxvar->sprites)))
					return (-1);
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
			if (mlxvar->set->map[(int)b.y][(int)b.x] == '2')
				if (mlxvar->sprites && ((int)b.y - mlxvar->sprites->mapY) && ((int)b.x - mlxvar->sprites->mapX) && !(mlxvar->sprites = raylist_add(b.x, b.y, i, mlxvar->sprites)))
					return (-1);
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
	lst_sort_siz(&mlxvar->sprites);
	return (0);
}
