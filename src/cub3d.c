/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 00:22:47 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/15 00:22:47 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


int		cub3D(t_set *set, int flags)
{
	t_bool		save;
	t_mlxvar	mlxvar;

	save = false;
	if ((flags == SAVE) || (flags == (SAVE | BONUS)))
		save = true;
	display_map(set->map);
	mlxvar.mapY = 0;
	while (set->map[mlxvar.mapY])
		mlxvar.mapY++;
	mlxvar.mapY *= 21;
	mlxvar.mapX = ft_strlen(*(set->map)) * 21;
	if (!(mlxvar.id = mlx_init()) || !(mlxvar.win_2d = mlx_new_window(mlxvar.id, mlxvar.mapX, mlxvar.mapY, "Cub3D")))
	{
		clear_set(set);
		return (ft_fputs(2, "Cub3D: Error while initializing window.\n"));
	}
	mlx_loop(mlxvar.id);
	(void)save;
	return (0);
}
