/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_chunks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 02:56:38 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/17 02:56:38 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	g_prev_len;
static int	g_prev_start;

static int		is_map_wall_2(char *line, int *pos, int len, int is_spawn_set)
{
	int		tmp;

	if (!ft_strchr(MAP_CHRST, line[*pos]))
		return (0);
	if (ft_strchr("NOSE", line[*pos]))
	{
		if (is_spawn_set)
			return (1);
		is_spawn_set = true;
	}
	tmp = *pos;
	while (line[*pos] == '1')
		(*pos)++;
	if (!line[*pos] || ft_isspace(line[*pos]))
	{
		g_prev_len = ((*pos) - 1);
		while (ft_isspace(line[*pos]))
			(*pos)++;
		if (line[*pos] || (g_prev_len > len))
			return (0);
		return (1);
	}
	return (-1);
}

static t_bool	is_map_wall(char *line, int start, int len)
{
	int				i;
	static t_bool	is_spawn_set;
	t_bool			ret;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (((start - ANY_START) && (i < start)) || (line[i] - '1'))
		return (false);
	g_prev_start = i;
	while ((line[i] == '1') && (line[i + 1] == '1'))
		i++;
	if (ft_isspace(line[i + 1]))
	{
		if (i < len)
			return (false);
		g_prev_len = i;
		while (ft_isspace(line[i]))
			i++;
		return (line[i] ? false : true);
	}
	while (++i < len)
		if ((ret = is_map_wall_2(line, &i, len)) + 1)
			return (ret);
}

static int		get_chunks_3(t_set *set, t_line **map)
{
	t_line	*begin;
	int		ret;

	begin = *map;
	ret = 1;
	while (ret)
		if ((ret = get_one_chunk(set, map) < 0))
		{
			lst_line_clr(&begin);
			return (error_wrong_map(ER_DEFLT));
		}
	lst_line_clr(&begin);
	return (0);
}

static int		get_chunks_2(int fd, t_set *set, t_line *map)
{
	int		ret;
	char	*line;

	ret = get_next_line(fd, &line);
	while (is_map_wall(line, g_prev_start, g_prev_len))
	{
		if ((lst_line_addback(&map, line)) < 0)
		{
			get_next_line_end(fd, &line);
			lst_line_clr(&map);
			return (error_wrong_map(ER_DEFLT));
		}
		ret = get_next_line(fd, &line);
	}
	get_next_line_end(fd, &line);
	if ((map == lst_line_last(map))
	|| !is_map_wall(lst_line_last(map)->line, g_prev_start, 0))
		return (error_wrong_map(ER_WRMAP));
	return (get_chunks_3(set, &map));
}

int				get_chunks(int fd, t_set *set)
{
	char	*line;
	int		tmp;
	int		ret;
	t_line	*map;
	t_line	*begin;

	if ((ret = get_next_line(fd, &line) < 0))
		return (error_wrong_map(ER_READF));
	while (ret && str_isspace(line))
	{
		free(line);
		ret = get_next_line(fd, &line);
	}
	if (!(ret = is_map_wall(line, ANY_START, 0)) || !(map = lst_line_new(line)))
	{
		get_next_line_end(fd, &line);
		return (error_wrong_map(ret ? ER_DEFLT : ER_WRMAP));
	}
	free(line);
	line = NULL;
	return (get_chunks_2(fd, set, map));
}
