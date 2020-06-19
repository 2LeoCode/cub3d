/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 23:00:48 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/17 23:00:48 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	lst_line_clr(t_line **lst)
{
	t_line	*head;

	while (lst && *lst)
	{
		head = (*lst)->next;
		free((*lst)->line);
		(*lst)->line = NULL;
		(*lst)->next = NULL;
		free(*lst);
		*lst = head;
	}
}

t_line	*lst_line_last(t_line *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

int		lst_line_addback(t_line **lst, char *content)
{
	if (!(lst_line_last(*lst)->next = lst_line_new(content)))
		return (-1);
	return (0);
}

t_line	*lst_line_new(char *content)
{
	t_line	*tmp;

	if (!(tmp = malloc(sizeof(t_line)))
		return (NULL);
	tmp->line = content;
	tmp->next = NULL;
	return (tmp);
}
