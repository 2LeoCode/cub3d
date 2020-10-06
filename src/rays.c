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
	b->x = tmp.x;
	b->y = tmp.y;
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

int		update_rays(t_mlxvar *mlx)
{
	int			i;
	double		r;
	double		a;
	double		t;
	t_point		b;
	t_point		c;
	t_point		length;
	t_point		d;

	mlx->spList = NULL;
	if (!mlx->rays && !(mlx->rays = malloc(sizeof(t_ray) * mlx->set->X)))
		return (-1);
	i = -1;
	r = -(mlx->set->FOV / 2);
	while (++i < mlx->set->X)
	{
		a = mlx->set->rot_hor + r;
		if (a < 0)
			a = _2PI + a;
		if (a >= _2PI)
			a = a - _2PI;
		mlx->rays[i].rot = r;
		t = -1 / (tan(a) + (0.0001 * (!a || a == M_PI)));
		if (a < M_PI)
		{
			b.y = (int)mlx->posY + 1;
			d.y = 1;
		}
		else if (!a || a == M_PI)
		{
			b.y = mlx->posY;
			d.y = 0;
		}
		else
		{
			b.y = (int)mlx->posY - 0.0001;
			d.y = -1;
		}
		b.x = mlx->posX + (mlx->posY - b.y) * t;
		d.x = -d.y * t;
		while (a && (a - M_PI) && (b.x > 0) && (b.y > 0) && (b.x < mlx->set->mapX) && (b.y < mlx->set->mapY) && (mlx->set->map[(int)b.y][(int)b.x] - '1'))
		{
			if ((mlx->set->map[(int)b.y][(int)b.x] == '2')
			&& !(mlx->spList = spListAddFront(mlx->posX, mlx->posY, mlx->spList, (double)((int)b.x + 0.5), (double)((int)b.y + 0.5))))
				return (freeSpFail(&mlx->spList));
			b.x += d.x;
			b.y += d.y;
		}
		length.y = sqrt((b.x - mlx->posX) * (b.x - mlx->posX) + (b.y - mlx->posY) * (b.y - mlx->posY));
		t = -tan(a);
		if (a < PI2 || a > _3PI2)
		{
			c.x = (int)mlx->posX + 1;
			d.x = 1;
		}
		else if (a == PI2 || a == _3PI2)
		{
			c.x = mlx->posX;
			d.x = 0;
		}
		else
		{
			c.x = (int)mlx->posX - 0.0001;
			d.x = -1;
		}
		c.y = mlx->posY + (mlx->posX - c.x) * t;
		d.y = -d.x * t;
		while ((a - PI2) && (a - _3PI2) && (c.x > 0) && (c.y > 0) && (c.x < mlx->set->mapX) && (c.y < mlx->set->mapY) && (mlx->set->map[(int)c.y][(int)c.x] - '1'))
		{
			if ((mlx->set->map[(int)c.y][(int)c.x] == '2')
			&& !(mlx->spList = spListAddFront(mlx->posX, mlx->posY, mlx->spList, (double)((int)b.x + 0.5), (double)((int)b.y + 0.5))))
				return (freeSpFail(&mlx->spList));
			c.y += d.y;
			c.x += d.x;
		}
		length.x = sqrt((c.x - mlx->posX) * (c.x - mlx->posX) + (c.y - mlx->posY) * (c.y - mlx->posY));
		if (length.y < length.x)
		{
			mlx->rays[i].siz = length.y;
			mlx->rays[i].texture = ((a < M_PI) ? &mlx->wallS : &mlx->wallN);
			mlx->rays[i].col_pos = (double)(b.x - (int)b.x) * mlx->rays[i].texture->width;
		}
		else
		{
			mlx->rays[i].siz = length.x;
			mlx->rays[i].texture = (((a > PI2) && (a < _3PI2)) ? &mlx->wallW : &mlx->wallE);
			mlx->rays[i].col_pos = (double)(c.y - (int)c.y) * mlx->rays[i].texture->width;
		}
		r += (mlx->set->FOV / mlx->set->X);
	}
	sortSpList(&mlx->spList);
	return (0);
}
