/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inittextures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 23:38:57 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/10 22:09:46 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void		alloctextures(t_mlxvar *mlxvar)
{
	mlxvar->screen.img_data = (int*)mlx_get_data_addr(mlxvar->screen.img,
	&mlxvar->screen.bpp, &mlxvar->screen.line_size, &mlxvar->screen.endian);
	mlxvar->screen.width = mlxvar->set->x;
	mlxvar->screen.height = mlxvar->set->y;
	mlxvar->walln.img = mlx_xpm_file_to_image(mlxvar->id , mlxvar->set->no,
	&mlxvar->walln.width, &mlxvar->walln.height);
	mlxvar->walln.img_data = (int*)mlx_get_data_addr(mlxvar->walln.img,
	&mlxvar->walln.bpp, &mlxvar->walln.line_size, &mlxvar->walln.endian);
	mlxvar->walle.img = mlx_xpm_file_to_image(mlxvar->id , mlxvar->set->ea,
	&mlxvar->walle.width, &mlxvar->walle.height);
	mlxvar->walle.img_data = (int*)mlx_get_data_addr(mlxvar->walle.img,
	&mlxvar->walle.bpp, &mlxvar->walle.line_size, &mlxvar->walle.endian);
	mlxvar->walls.img = mlx_xpm_file_to_image(mlxvar->id , mlxvar->set->so,
	&mlxvar->walls.width, &mlxvar->walls.height);
	mlxvar->walls.img_data = (int*)mlx_get_data_addr(mlxvar->walls.img,
	&mlxvar->walls.bpp, &mlxvar->walls.line_size, &mlxvar->walls.endian);
	mlxvar->wallw.img = mlx_xpm_file_to_image(mlxvar->id , mlxvar->set->we,
	&mlxvar->wallw.width, &mlxvar->wallw.height);
	mlxvar->wallw.img_data = (int*)mlx_get_data_addr(mlxvar->wallw.img,
	&mlxvar->wallw.bpp, &mlxvar->wallw.line_size, &mlxvar->wallw.endian);
	mlxvar->sprite.img = mlx_xpm_file_to_image(mlxvar->id , mlxvar->set->s,
	&mlxvar->sprite.width, &mlxvar->sprite.height);
	mlxvar->sprite.img_data = (int*)mlx_get_data_addr(mlxvar->sprite.img,
	&mlxvar->sprite.bpp, &mlxvar->sprite.line_size, &mlxvar->sprite.endian);
}

int				init_textures(t_mlxvar *mlxvar)
{
	mlxvar->walln.img = NULL;
	mlxvar->walln.img_data = NULL;
	mlxvar->walle.img = NULL;
	mlxvar->walle.img_data = NULL;
	mlxvar->walls.img = NULL;
	mlxvar->walls.img_data = NULL;
	mlxvar->wallw.img = NULL;
	mlxvar->wallw.img_data = NULL;
	mlxvar->sprite.img = NULL;
	mlxvar->sprite.img_data = NULL;
	mlxvar->screen.img = NULL;
	mlxvar->walln.img_data = NULL;
	mlxvar->rays = NULL;
	mlxvar->screen.img = mlx_new_image(
	mlxvar->id, mlxvar->set->x, mlxvar->set->y);
	alloctextures(mlxvar);
	if (!mlxvar->walln.img || !mlxvar->walln.img_data || !mlxvar->walle.img
	|| !mlxvar->walle.img_data || !mlxvar->walls.img || !mlxvar->walls.img_data
	|| !mlxvar->wallw.img || !mlxvar->wallw.img_data || !mlxvar->sprite.img
	|| !mlxvar->sprite.img_data	|| !mlxvar->screen.img
	|| !mlxvar->screen.img_data)
		return (-1);
	return (0);
}

t_mlxvar		initmlx(t_set *set, int flags, t_bool *save)
{
	t_mlxvar	mlxvar;

	*save = false;
	if ((flags == SAVE) || (flags == (SAVE | BONUS)))
		*save = true;
	mlxvar.set = set;
	mlxvar.id = NULL;
	mlxvar.win = NULL;
	mlxvar.screen.img = NULL;
	mlxvar.screen.img_data = NULL;
	mlxvar.rays = NULL;
	mlxvar.posx = (double)mlxvar.set->spawn.x + 0.5;
	mlxvar.posy = (double)mlxvar.set->spawn.y + 0.5;
	mlxvar.lastkey = -1;
	mlxvar.iskeypressed = 0;
	return (mlxvar);
}

