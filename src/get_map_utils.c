/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 23:22:59 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/20 23:22:59 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_bool			is_map_wall(char *line)
{
	while (ft_isspace(*line))
		line++;
	if (*line - '1')
		return (false);
	while (*line)
	{
		if (*line - '1')
			return (false);
		while (*line && *(line + 1) && ft_strchr(MAP_CHRST, *(line + 1)))
			line++;
		if (*line - '1')
			return (false);
		line++;
		while (ft_isspace(*line))
			line++;
	}
	return (true);
}


static t_bool	check_case(char **map, int y, int x)
{
	int		i;
	int		j;

	i = (y - 2);
	while (++i < (y + 2))
	{
		j = x - 2;
		while (++j < (x + 2))
		{
			if (map[i][j] == ' ')
				return (false);
		}
	}
	return (true);
}

int				check_map(t_set *set)
{
	char	**tmp;
	t_bool	check;
	int		i;
	int		j;

	check = false;
	tmp = set->map;
	i = -1;

	while (tmp[++i])
	{
		j = -1;
		while (tmp[i][++j])
		{
			if (!ft_strchr("NOSE012 ", tmp[i][j])
			|| ((tmp[i][j] == '0') && !check_case(tmp, i, j)))
			{
				clear_set(set);
				return (ER_WRMAP);
			}
			else if (ft_strchr("NOSE", tmp[i][j]))
			{
				check = true;
				set->spawn.X = i;
				set->spawn.Y = j;
				if (tmp[i][j] == 'N')
					set->rot_hor = M_PI / 2;
				if (tmp[i][j] == 'E')
					set->rot_hor = 0;
				if (tmp[i][j] == 'S')
					set->rot_hor = 3 * M_PI / 4;
				if (tmp[i][j] == 'O')
					set->rot_hor = M_PI;
			}
		}
	}
	if (!check)
	{
		clear_set(set);
		return (ER_NOSPW);
	}
	set->rot_vert = 0;
	return (0);
}
