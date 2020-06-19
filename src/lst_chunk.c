/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_chunk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 21:52:57 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/18 21:52:57 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_chunk		*lst_chunk_new(int x, int y)
{
	t_chunk		*tmp;

	if (!(tmp = malloc(sizeof(t_chunk))))
		return (NULL);
	tmp->x = x;
	tmp->y = y;
	tmp->next = NULL;
	return (tmp);
}

t_chunk		*lst_chunk_last(t_chunk *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void		lst_chunk_clr(t_chunk **lst)
{
	t_chunk		*head;

	while (lst && *lst)
	{
		head = (*lst)->next;
		(*lst)->next = NULL; 
		free(*lst);
		*lst = head;
	}
}
