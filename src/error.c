/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 22:36:00 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/14 22:36:00 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int		error_wrong_file(int errnum)
{
	ft_fputs(stderr, "Error\n");
	if (errnum == ER_WPATH)
		ft_fputs(stderr, "No input file or wrong file format (has to be .cub)\nUsage: ./Cub3D [--save] [--bonus] [path_to_map.cub]");
	else if (errnum == ER_OPENF)
		ft_fputs(stderr, "Failed to open map file\nUsage: ./Cub3D [--save] [--bonus] [path_to_map.cub]");
	return (-1);
}
