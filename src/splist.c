/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 22:42:41 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/10 22:49:01 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void		splistswap(t_splist *a, t_splist *b)
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

void		sortsplist(t_splist **lst)
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

void		freesplist(t_splist **lst)
{
	t_splist	*head;

	while (*lst)
	{
		head = (*lst)->next;
		free(*lst);
		*lst = head;
	}
}

int			freespfail(t_splist **lst)
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
