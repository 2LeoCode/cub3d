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

void	spListSwap(t_spList *a, t_spList *b)
{
	t_spList	tmp;

	tmp.a = a->a;
	tmp.len = a->len;
	tmp.x = a->x;
	tmp.y = a->y;
	a->a = b->a;
	a->len = b->len;
	a->x = b->x;
	a->y = b->y;
	b->a = tmp.a;
	b->len = tmp.len;
	b->x = tmp->x;
	b->y = tmp->y;
}

void	sortSpList(t_spList **lst)
{
	t_spList	*cur;
	t_spList	*head;

	cur = *lst;
	while (cur)
	{
		head = cur->next;
		while (head)
		{
			if (cur->len < head->len)
				spListSwap(cur, head);
			head = head->next;
		}
		cur = cur->next;
	}
}

void	freeSpList(t_spList **lst)
{
	t_spList	*head;

	while (*lst)
	{
		head = (*lst)->next;
		free(*lst);
		*lst = head;
	}
}

int		freeSpFail(t_spList **lst)
{
	freeSpList(lst);
	return (-1);
}

t_spList	*spListAddFront(int px, int py, t_spList *lst, double x, double y)
{
	t_spList	*tmp;
	t_spList	*check;
	double		a;
	double		deltaX;
	double		deltaY;

	deltaX = x - px;
	deltaY = y - py;
	check = lst;
	while (check)
	{
		if (((int)x == (int)check->x) && ((int)y == (int)check->y))
			return (lst);
		check = check->next;
	}
	if (!(tmp = malloc(sizeof(t_spList))))
		return (NULL);
	tmp->x = x;
	tmp->y = y;
	tmp->len = sqrt(deltaX * deltaX + deltaY * deltaY);
	tmp->a = atan2(deltaY, deltaX);
	tmp->next = lst;
	return (tmp);
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
	t_spList	*spList;

	spList = NULL;
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
			if ((mlxvar->set->map[(int)b.y][(int)b.x] == '2')
			&& !(spList = spListAddFront(mlxvar->posX, mlxvar->posY, spList, (double)((int)b.x + 0.5), (double)((int)b.y + 0.5))))
				return (freeSpFail(&spList));
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
			if ((mlxvar->set->map[(int)c.y][(int)c.x] == '2')
			&& !(spList = spListAddFront(mlxvar->posX, mlxvar->posY, spList, (double)((int)b.x + 0.5), (double)((int)b.y + 0.5))))
				return (freeSpFail(&spList));
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
	sortSpList(&spList);
	return (0);
}
