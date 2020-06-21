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

static t_bool	is_check(t_bool *check)
{
	int		i;

	i = -1;
	while (++i < NB_PARAMS)
		if (!check[i])
			return (false);
	return (true);
}

static int	get_res(char *line, t_set *set, t_bool *check)
{
	if (check[C_X] || check[C_Y])
		return (ER_DOUBL);
	line++;
	if (*line && !ft_isspace(*line))
		return (ER_WRRES);
	while (ft_isspace(*line))
		line++;
	set->X = ft_atoi(line);
	check[C_X] = true;
	while (ft_isdigit(*line))
		line++;
	if (*line && !ft_isspace(*line))
		return (ER_WRRES);
	while (ft_isspace(*line))
		line++;
	set->Y = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	while (ft_isspace(*line))
		line++;
	if (*line)
		return (ER_WRRES);
	check[C_Y] = true;
	if ((set->X < 50) || (set->Y < 50) || (set->X > 1980) || (set->Y > 1080))
	{
		error_wrong_map(ER_WRRES | WARNING);
		set->X = 800;
		set->Y = 600;
	}
	return (0);
}

static int	get_single_rgb(char **line, int *col)
{
	while (ft_isspace(**line))
		(*line)++;
	if (**line && !ft_isdigit(**line))
		return (-1);
	*col = ft_atoi(*line);
	while (ft_isdigit(**line))
		(*line)++;
	while (ft_isspace(**line))
		(*line)++;
	return (0);
}

static int	get_rgb(char *line, t_set *set, t_bool *check)
{
	t_rgb	*tmp;

	if ((*line == 'F' && check[C_F]) || (*line == 'C' && check[C_C])) 
		return (ER_DOUBL);
	if (*line == 'F')
		tmp = &set->F;
	else if (*line == 'C')
		tmp = &set->C;
	line++;
	if (!ft_isspace(*line))
		return (ER_UNKNW);
	if (get_single_rgb(&line, &tmp->R) || (*(line++) - ',')
	|| get_single_rgb(&line, &tmp->G) || (*(line++) - ',')
	|| get_single_rgb(&line, &tmp->B) || *line)
		return (ER_WRRGB);
	check[((tmp == &set->F) ? C_F : C_C)] = true;
	return (0);
}

int			get_set(int fd, t_set *set)
{
	int		i;
	t_bool	check[NB_PARAMS];
	char	*line;
	t_bool	total;

	i = -1;
	total = false;
	while (++i < NB_PARAMS)
		check[i] = 0;
	if ((i = get_next_line(fd, &line)) < 0)
		return (-1);
	while (i > 0)
	{
		printf("%s\n", line);
		i = 0;
		while (ft_isspace(line[i]))
			i++;
		if (((line[i] == 'R') && (i = get_res(&line[i], set, check)))
		|| ((ft_strchr("FC", line[i])) && (i = get_rgb(&line[i], set, check)))
		|| (line[i] && (i = get_path(&line[i], set, check))))
			return (i);
		free(line);
		if ((total = is_check(check)) == true)
			break ;
		if ((i = get_next_line(fd, &line) < 0))
			return (ER_READF);
	}
	if (total)
		return (get_map(fd, set));
	clear_set(set);
	return (ER_MISSI);
}
