/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 23:24:38 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/14 23:24:38 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		help(void)
{
	ft_putstr("Usage: ./Cub3D [options] [map]\n\
The map file must be a valid .cub file\n\n\
Available options:\n  \
-h, --help\t\tShows help message, also ignores any other argument\n\
\t\t\tand does not start the program\n  \
-s, --save\t\tSaves the first rendered image at program start in\n\
\t\t\t<capture> folder\n  \
-b, --bonus\t\tEnables the bonus part.\n\nReturn values:\n  \
0  succes exit\n\
-1 failure exit\n");
	return (0);
}
