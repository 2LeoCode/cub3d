/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 22:01:56 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/16 22:01:56 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	get_path_3(char *path, t_set *set, int ch)
{
	int		fd;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (error_wrong_file(path));
	close(fd);
	if (ch == C_NO && !(set->NO = ft_strdup(path)))
		return (error_wrong_map(ER_DEFLT));
	if (ch == C_SO && !(set->SO = ft_strdup(path)))
		return (error_wrong_map(ER_DEFLT));
	if (ch == C_WE && !(set->WE = ft_strdup(path)))
		return (error_wrong_map(ER_DEFLT));
	if (ch == C_EA && !(set->EA = ft_strdup(path)))
		return (error_wrong_map(ER_DEFLT));
	if (ch == C_S && !(set->S = ft_strdup(path)))
		return (error_wrong_map(ER_DEFLT));
	return (0);
}

static int	get_path_2(char *line, t_set *set, int ch)
{
	char	*tmp[2];

	while (ft_isalpha(*line))
		line++;
	while (ft_isspace(*line))
		line++;
	tmp[0] = line;
	while (!ft_isspace(*line))
		line++;
	tmp[1] = line;
	while (ft_isspace(*line))
		line++;
	if (*line)
		return (error_wrong_map(ER_WRPTH));
	*tmp[1] = 0;
	if (get_path_3(tmp[0], set, ch))
		return (-1);
	return (0);
}

int			get_path(char *line, t_set *set, t_bool *check)
{
	int		ch;
	int		fd;

	if (!ft_memcmp(line, "NO", 2))
		ch = C_NO;
	else if (!ft_memcmp(line, "SO", 2))
		ch = C_SO;
	else if (!ft_memcmp(line, "WE", 2))
		ch = C_WE;
	else if (!ft_memcmp(line, "EA", 2))
		ch = C_EA;
	else if (*line == 'S' && ft_isspace(*(line + 1)))
		ch = C_S;
	else
		return (error_wrong_map(ER_UNKNW));
	if (check[ch])
		return (error_wrong_map(ER_DOUBL));
	if (get_path_2(line, set, ch))
		return (-1);
	check[ch] = true;
	return (0);
}
