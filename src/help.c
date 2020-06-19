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

int		help(int show_msg)
{
	char	*help;

	ft_putstr("Usage: ./Cub3D [options] [map]\n");
	if (show_msg == H_NOARG)
		ft_putstr("Execute « ./Cub3D --help » for more informations\n");
	else
	{
		if (!(help = get_file("data/help.txt")))
			return (-1);
		ft_putstr(help);
		free(help);
	}
	return (0);
}
