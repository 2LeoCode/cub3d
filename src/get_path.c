/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 22:01:56 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/10 14:45:00 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	get_path_3(char *path, t_set *set, int ch)
{
	int		fd;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (ER_WPIMG);
	close(fd);
	if (ch == C_NO && !(set->no = ft_strdup(path)))
		return (ER_DEFLT);
	if (ch == C_SO && !(set->so = ft_strdup(path)))
		return (ER_DEFLT);
	if (ch == C_WE && !(set->we = ft_strdup(path)))
		return (ER_DEFLT);
	if (ch == C_EA && !(set->ea = ft_strdup(path)))
		return (ER_DEFLT);
	if (ch == C_S && !(set->s = ft_strdup(path)))
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
		return (ER_WPIMG);
	*tmp[1] = 0;
	if ((ret = get_path_3(tmp[0], set, ch)) != 0)
		return (ret);
	return (0);
}

int			get_path(char *line, t_set *set, t_bool *check)
{
	int		ch;
	int		ret;

	if (!ft_memcmp(line, "no", 2))
		ch = C_NO;
	else if (!ft_memcmp(line, "so", 2))
		ch = C_SO;
	else if (!ft_memcmp(line, "we", 2))
		ch = C_WE;
	else if (!ft_memcmp(line, "ea", 2))
		ch = C_EA;
	else if (*line == 's' && ft_isspace(*(line + 1)))
		ch = C_S;
	else
		return (ER_UNKNW);
	if (check[ch])
		return (ER_DOUBL);
	if ((ret = get_path_2(line, set, ch)) != 0)
		return (ret);
	check[ch] = true;
	return (0);
}
