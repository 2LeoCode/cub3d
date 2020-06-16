/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 00:53:38 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/15 00:53:38 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int		get_res(char *line, t_set *set, t_bool *check)
{
	if (check[C_X] || check[C_Y])
		return (error_wrong_file(ER_DOUBL));
	line++;
	while (ft_isspace(*line))
		line++;
	set->X = ft_atoi(line);
	check[C_X] = true;
	while (ft_isdigit(*line))
		line++;
	while (ft_isspace(*line))
		line++;
	set->Y = ft_atoi(line);
	check[C_Y] = true;
	if (set->X < 50 || set->Y < 50)
		return (error_wrong_file(ER_WRRES));
	if (set->X > 1920)
		set->X = 1920;
	if (set->Y > 1080)
		set->X = 1080;
	return (0);
}

int			get_set(int fd, t_set *set)
{
	(void)fd;
	(void)set
	return (0);
	/*int		i;
	t_bool	check[NB_PARAMS];
	char	*line;
	t_bool	total;

	i = -1;
	total = false;
	while (++i < NB_PARAMS)
		check[i] = 0;
	if ((i = get_next_line(fd, &line) < 0))
		return (-1);
	if (!i)
	{
		free(line);
		return (error_wrong_file(ER_MISSI));
	}
	while (i > 0)
	{
		i = 0;
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == 'R' && get_res(&line[i], set, check)
		|| (line[i] == 'F' || line[i] == 'C' && get_rgb(&line[i], set, check))
		|| get_path(&line[i], set, check))
			return (-1);
		free(line);
		if ((total = is_check(check, NB_PARAMS)) == true)
			break ;
		if ((i = get_next_line(fd, &line) < 0))
			return (error_wrong_file(ER_READF));
	}
	return (total ? get_chunks(fd, set) : error_wrong_file(ER_MISSI));*/
}
