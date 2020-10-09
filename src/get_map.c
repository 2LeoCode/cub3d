/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 22:39:21 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/19 22:39:21 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int		get_map_y(t_line *lst)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (lst)
	{
		if (!str_isspace(lst->line))
			i = 0;
		else
			i++;
		j++;
		lst = lst->next;
	}
	return ((j - i) + 2);
}

static int		get_map_x(t_line *lst)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (lst)
	{
		j = 0;
		while (ft_isspace(lst->line[j]))
			j++;
		tmp = &lst->line[j];
		j = 0;
		while (!str_isspace(&tmp[j]))
			j++;
		if (i < j)
			i = j;
		lst = lst->next;
	}
	return (i + 2);
}

static void		get_line(char **map, int index, char *line, int size)
{
	int		i;

	i = 0;
	map[index][i] = ' ';
	while (++i < size)
		if (*line)
			map[index][i] = *(line++);
		else
			map[index][i] = ' ';
	map[index][i] = 0;
}

static int		getMapFromList2(t_line **lst, t_set *set)
{
	int		i;
	int		j;
	t_line	*tmp;

	i = 0;
	j = -1;
	while (++j < set->mapX)
		set->map[i][j] = ' ';
	set->map[i][j] = 0;
	i += (set->mapY - 1);
	j = -1;
	while (++j < set->mapX)
		set->map[i][j] = ' ';
	set->map[i][j] = 0;
	tmp = *lst;
	i = 1;
	while (tmp)
	{
		get_line(set->map, i, tmp->line, set->mapX);
		tmp = tmp->next;
		i++;
	}
	return (0);
}

static int		get_map_from_list(t_line **lst, t_set *set)
{
	int			i;

	set->mapY = get_map_y(*lst);
	if (!(set->map = (char**)malloc(sizeof(char*) * (set->mapY + 1))))
		return (ER_DEFLT);
	set->mapX = get_map_x(*lst);
	i = -1;
	while (++i < set->mapY)
		if (!(set->map[i] = (char*)malloc(sizeof(char) * (set->mapX + 1))))
			return (ER_DEFLT);
	set->map[i] = NULL;
	return (getMapFromList2(lst, set));
}

int				getMapToList(int fd, char **line, t_line **lst)
{
	int		ret;

	while (((ret = get_next_line(fd, line)) != -1) && is_map_wall(*line))
		if (lst_line_addback(lst, *line))
		{
			get_next_line_end(fd, line);
			lst_line_clr(lst);
			return (ER_DEFLT);
		}
	return (0);
}

int				get_map(int fd, t_set *set)
{
	t_line	*tmp;
	int		i;
	char	*line;
	int		j;

	i = get_next_line(fd, &line);
	while (i && str_isspace(line))
	{
		free(line);
		i = get_next_line(fd, &line);
	}
	if ((!i || !is_map_wall(line)) || !(tmp = lst_line_new(line)))
	{
		get_next_line_end(fd, &line);
		return ((!i || !is_map_wall(line)) ? ER_WRMAP : ER_DEFLT);
	}
	tmp = lst_line_new(line);
	if (getMapToList(fd, &line, &tmp))
		return (ER_DEFLT);
	if (!(i = get_map_from_list(&tmp, set)) && !(j = check_map(set)))
		return (0);
	clear_set(set);
	lst_line_clr(&tmp);
	return (i ? i : j);
}
