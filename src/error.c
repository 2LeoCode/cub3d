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

char			*error_s(int errnum)
{
	ft_fputs(_stderr, "Error\nCub3D: ");
	ft_fputs(_stderr, strerror(errnum));
	ft_fputc(_stderr, '\n');
	return (NULL);
}

static t_bool	is_warning(int errnum)
{
	int		i;

	i = -1;
	while ((i < ER_COUNT) && (errnum - (i | WARNING)))
		i++;
	return (errnum == (i | WARNING));
}

int				error_wrong_file(char *path)
{
	ft_fputs(_stderr, "Error\nCub3D: Failed to open file '");
	ft_fputs(_stderr, path);
	ft_fputs(_stderr, "'\n");
	return (-1);
}

int				error_wrong_map(int errnum)
{
	ft_fputs(_stderr, (is_warning(errnum) ? "Warning\n" : "Error\n"));
	ft_fputs(_stderr, "Cub3D: ");
	if (errnum == ER_WPATH)
		ft_fputs(_stderr, "No input file or wrong file format \
(has to be .cub)\nUsage: ./Cub3D [--save] [--bonus] [path_to_map.cub]\n");
	else if (errnum == ER_OPENF)
		ft_fputs(_stderr, "Failed to open map file\nUsage: ./Cub3D \
[--save] [--bonus] [path_to_map.cub]\n");
	else if (errnum == ER_MISSI)
		ft_fputs(_stderr, "Missing parameter(s) in map file\n\
Use --help for more information\n");
	else if (errnum == ER_READF)
		ft_fputs(_stderr, "Failed to read map file\n");
	else if (errnum == ER_DOUBL)
		ft_fputs(_stderr, "A parameter is declared 2 times in map file\n");
	else if (errnum == ER_WRRES)
		ft_fputs(_stderr, "Wrong resolution\n\
Use --help for more information\n");
	else if (errnum == (ER_WRRES | WARNING))
		ft_fputs(_stderr, "Too low/high resolution (must be between \
[50 x 50] and [1980 x 1080]), the resolution is set to 800 x 600\n");
	else if (errnum == ER_UNKNW)
		ft_fputs(_stderr, "Unknown parameter in map file\n\
Use --help for more information\n");
	else if (errnum == ER_WRRGB)
		ft_fputs(_stderr, "Wrong RGB input in map file\n\
Use --help for more information\n");
	else if (errnum == ER_WRMAP)
		ft_fputs(_stderr, "Minimap in map file is not valid\n\
Use --help for more information\n");
	else if (errnum == ER_DEFLT)
		ft_fputs(_stderr, strerror(errno));
	else if (errnum == ER_NOSPW)
		ft_fputs(_stderr, "No spawn point set in map file\n
Use --help for more information\n");
	else
		ft_fputs(_stderr, "An unknown error occured\n");
	return (-1);
}
