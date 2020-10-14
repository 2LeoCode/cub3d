/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_full_wall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 15:40:30 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/13 15:40:30 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_bool	is_map_full_wall(char *line)
{
	int		i;

	i = -1;
	while (line[++i])
		if (!ft_strchr(" 1", line[i]))
			return (false);
	return (true);
}
