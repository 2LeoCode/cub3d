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

t_spList	*spListAddFront(double px, double py, t_spList *lst, double x, double y)
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
	if (tmp->a < 0)
		tmp->a += _2PI;
	tmp->next = lst;
	return (tmp);
}

void	initRayVert(t_rayVar *ur, t_mlxvar *mlx)
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
		ur->b.y = (int)mlx->posY + 1;
		ur->d.y = 1;
	}
	else if (!ur->a || ur->a == M_PI)
	{
		ur->b.y = mlx->posY;
		ur->d.y = 0;
	}
	else
	{
		ur->b.y = (int)mlx->posY - 0.0001;
		ur->d.y = -1;
	}
	ur->b.x = mlx->posX + (mlx->posY - ur->b.y) * ur->t;
	ur->d.x = -ur->d.y * ur->t;
}

void	initRayHor(t_rayVar *ur, t_mlxvar *mlx)
{
	ur->t = -tan(ur->a);
	if (ur->a < PI2 || ur->a > _3PI2)
	{
		ur->c.x = (int)mlx->posX + 1;
		ur->d.x = 1;
	}
	else if (ur->a == PI2 || ur->a == _3PI2)
	{
		ur->c.x = mlx->posX;
		ur->d.x = 0;
	}
	else
	{
		ur->c.x = (int)mlx->posX - 0.0001;
		ur->d.x = -1;
	}
	ur->c.y = mlx->posY + (mlx->posX - ur->c.x) * ur->t;
	ur->d.y = -ur->d.x * ur->t;
}

void	getTextCoord(t_rayVar *ur, t_mlxvar *mlx)
{
	if (ur->length.y < ur->length.x)
	{
		mlx->rays[ur->i].siz = ur->length.y;
		mlx->rays[ur->i].texture = ((ur->a < M_PI) ? &mlx->wallS : &mlx->wallN);
		mlx->rays[ur->i].col_pos = (double)(ur->b.x - (int)ur->b.x)
		* mlx->rays[ur->i].texture->width;
	}
	else
	{
		mlx->rays[ur->i].siz = ur->length.x;
		mlx->rays[ur->i].texture = (((ur->a > PI2) && (ur->a < _3PI2)) ?
		&mlx->wallW : &mlx->wallE);
		mlx->rays[ur->i].col_pos = (double)(ur->c.y - (int)ur->c.y)
		* mlx->rays[ur->i].texture->width;
	}
}

void	shootRayVert(t_rayVar *ur, t_mlxvar *mlx)
{
	while (ur->a && (ur->a - M_PI) && (ur->b.x > 0) && (ur->b.y > 0)
	 && (ur->b.x < mlx->set->mapX) && (ur->b.y < mlx->set->mapY)
	 && (mlx->set->map[(int)ur->b.y][(int)ur->b.x] - '1'))
	{
		if ((mlx->set->map[(int)ur->b.y][(int)ur->b.x] == '2')
		&& !(mlx->spList = spListAddFront(mlx->posX, mlx->posY, mlx->spList,
		(double)((int)ur->b.x + 0.5), (double)((int)ur->b.y + 0.5))))
			return (freeSpFail(&mlx->spList));
		ur->b.x += ur->d.x;
		ur->b.y += ur->d.y;
	}
	ur->length.y = sqrt((ur->b.x - mlx->posX) * (ur->b.x - mlx->posX)
	+ (ur->b.y - mlx->posY) * (ur->b.y - mlx->posY));
}

void	shootRayHor(t_rayVar *ur, t_mlxvar *mlx)
{
	while ((ur->a - PI2) && (ur->a - _3PI2) && (ur->c.x > 0) && (ur->c.y > 0)
	&& (ur->c.x < mlx->set->mapX) && (ur->c.y < mlx->set->mapY)
	&& (mlx->set->map[(int)ur->c.y][(int)ur->c.x] - '1'))
	{
		if ((mlx->set->map[(int)ur->c.y][(int)ur->c.x] == '2')
		&& !(mlx->spList = spListAddFront(mlx->posX, mlx->posY, mlx->spList,
		(double)((int)ur->c.x + 0.5), (double)((int)ur->c.y + 0.5))))
			return (freeSpFail(&mlx->spList));
		ur->c.y += ur->d.y;
		ur->c.x += ur->d.x;
	}
	ur->length.x = sqrt((ur->c.x - mlx->posX) * (ur->c.x - mlx->posX)
	+ (ur->c.y - mlx->posY) * (ur->c.y - mlx->posY));
}

int		update_rays(t_mlxvar *mlx)
{
	t_rayVar	ur;

	mlx->spList = NULL;
	if (!mlx->rays && !(mlx->rays = malloc(sizeof(t_ray) * mlx->set->X)))
		return (-1);
	ur.i = -1;
	ur.r = -(mlx->set->FOV / 2);
	while (++ur.i < mlx->set->X)
	{
		initRayVert(&ur, mlx);
		shootRayVert(&ur, mlx);
		initRayHor(&ur, mlx);
		shootRayHor(&ur, mlx);
		getTextCoord(&ur, mlx);
		ur.r += (mlx->set->FOV / mlx->set->X);
	}
	sortSpList(&mlx->spList);
	return (0);
}
