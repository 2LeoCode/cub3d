/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 21:56:43 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/10 15:30:57 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	splistswap(t_splist *a, t_splist *b)
{
	t_splist	tmp;

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

void	sortsplist(t_splist **lst)
{
	t_splist	*cur;
	t_splist	*head;

	cur = *lst;
	while (cur)
	{
		head = cur->next;
		while (head)
		{
			if (cur->len < head->len)
				splistswap(cur, head);
			head = head->next;
		}
		cur = cur->next;
	}
}

void	freesplist(t_splist **lst)
{
	t_splist	*head;

	while (*lst)
	{
		head = (*lst)->next;
		free(*lst);
		*lst = head;
	}
}

int		freespfail(t_splist **lst)
{
	freesplist(lst);
	return (-1);
}

t_splist	*splistaddfront(double px, double py, t_splist *lst, double x,
double y)
{
	t_splist	*tmp;
	t_splist	*check;
	double		deltax;
	double		deltay;

	deltax = x - px;
	deltay = y - py;
	check = lst;
	while (check)
	{
		if (((int)x == (int)check->x) && ((int)y == (int)check->y))
			return (lst);
		check = check->next;
	}
	if (!(tmp = malloc(sizeof(t_splist))))
		return (NULL);
	tmp->x = x;
	tmp->y = y;
	tmp->len = sqrt(deltax * deltax + deltay * deltay);
	tmp->a = atan2(deltay, deltax);
	if (tmp->a < 0)
		tmp->a += _2PI;
	tmp->next = lst;
	return (tmp);
}

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

void	gettextcoord(t_rayvar *ur, t_mlxvar *mlx)
{
	if (ur->length.y < ur->length.x)
	{
		mlx->rays[ur->i].siz = ur->length.y;
		mlx->rays[ur->i].texture = ((ur->a < M_PI) ? &mlx->walls : &mlx->walln);
		mlx->rays[ur->i].col_pos = (double)(ur->b.x - (int)ur->b.x)
		* mlx->rays[ur->i].texture->width;
	}
	else
	{
		mlx->rays[ur->i].siz = ur->length.x;
		mlx->rays[ur->i].texture = (((ur->a > PI2) && (ur->a < _3PI2)) ?
		&mlx->wallw : &mlx->walle);
		mlx->rays[ur->i].col_pos = (double)(ur->c.y - (int)ur->c.y)
		* mlx->rays[ur->i].texture->width;
	}
}

int		shootrayvert(t_rayvar *ur, t_mlxvar *mlx)
{
	while (ur->a && (ur->a - m_pi) && (ur->b.x > 0) && (ur->b.y > 0)
	 && (ur->b.x < mlx->set->mapx) && (ur->b.y < mlx->set->mapy)
	 && (mlx->set->map[(int)ur->b.y][(int)ur->b.x] - '1'))
	{
		if ((mlx->set->map[(int)ur->b.y][(int)ur->b.x] == '2')
		&& !(mlx->splist = splistaddfront(mlx->posx, mlx->posy, mlx->splist,
		(double)((int)ur->b.x + 0.5), (double)((int)ur->b.y + 0.5))))
			return (-1);
		ur->b.x += ur->d.x;
		ur->b.y += ur->d.y;
	}
	ur->length.y = sqrt((ur->b.x - mlx->posx) * (ur->b.x - mlx->posx)
	+ (ur->b.y - mlx->posy) * (ur->b.y - mlx->posy));
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
	ur->length.x = sqrt((ur->c.x - mlx->posx) * (ur->c.x - mlx->posx)
	+ (ur->c.y - mlx->posy) * (ur->c.y - mlx->posy));
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
