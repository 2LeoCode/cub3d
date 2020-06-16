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

#include <cub3d.h>

char	*error_s(int errnum)
{
	ft_fputs(_stderr, "Error\nCub3D: ");
	ft_fputs(_stderr, strerror(errnum));
	ft_fputc(_stderr, '\n');
	return (NULL);
}

int		error_wrong_map(int errnum)
{
	ft_fputs(_stderr, "Error\n");
	if (errnum == ER_WPATH)
		ft_fputs(_stderr, "No input file or wrong file format (has to be .cub)\nUsage: ./Cub3D [--save] [--bonus] [path_to_map.cub]\n");
	else if (errnum == ER_OPENF)
		ft_fputs(_stderr, "Failed to open map file\nUsage: ./Cub3D [--save] [--bonus] [path_to_map.cub]\n");
	return (-1);
}
