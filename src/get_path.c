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
		return (ER_WPATH);
	close(fd);
	if (ch == C_NO && !(set->NO = ft_strdup(path)))
		return (ER_DEFLT);
	if (ch == C_SO && !(set->SO = ft_strdup(path)))
		return (ER_DEFLT);
	if (ch == C_WE && !(set->WE = ft_strdup(path)))
		return (ER_DEFLT);
	if (ch == C_EA && !(set->EA = ft_strdup(path)))
		return (ER_DEFLT);
	if (ch == C_S && !(set->S = ft_strdup(path)))
		return (ER_DEFLT);
	return (0);
}

static int	get_path_2(char *line, t_set *set, int ch)
{
	char	*tmp[2];
	int		ret;

	while (ft_isalpha(*line))
		line++;
	while (ft_isspace(*line))
		line++;
	tmp[0] = line;
	while (*line && !ft_isspace(*line))
		line++;
	tmp[1] = line;
	while (ft_isspace(*line))
		line++;
	if (*line)
		return (ER_WPATH);
	*tmp[1] = 0;
	if ((ret = get_path_3(tmp[0], set, ch)) != 0)
		return (ret);
	return (0);
}

int			get_path(char *line, t_set *set, t_bool *check)
{
	int		ch;
	int		ret;

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
		return (ER_UNKNW);
	printf("%d\n", ch);
	if (check[ch])
		return (ER_DOUBL);
	if ((ret = get_path_2(line, set, ch)) != 0)
		return (ret);
	check[ch] = true;
	return (0);
}
