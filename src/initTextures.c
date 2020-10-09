/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initTextures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 23:38:57 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/09 23:38:57 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void		allocTextures(t_mlxvar *mlxvar)
{
	mlxvar->screen.img = mlx_new_image(mlxvar->id, mlxvar->set->X, mlxvar->set->Y);
	mlxvar->screen.img_data = (int*)mlx_get_data_addr(mlxvar->screen.img,
	&mlxvar->screen.bpp, &mlxvar->screen.line_size, &mlxvar->screen.endian);
	mlxvar->screen.width = mlxvar->set->X;
	mlxvar->screen.height = mlxvar->set->Y;
	mlxvar->wallN.img = mlx_xpm_file_to_image(mlxvar->id , mlxvar->set->NO,
	&mlxvar->wallN.width, &mlxvar->wallN.height);
	mlxvar->wallN.img_data = (int*)mlx_get_data_addr(mlxvar->wallN.img,
	&mlxvar->wallN.bpp, &mlxvar->wallN.line_size, &mlxvar->wallN.endian);
	mlxvar->wallE.img = mlx_xpm_file_to_image(mlxvar->id , mlxvar->set->EA,
	&mlxvar->wallE.width, &mlxvar->wallE.height);
	mlxvar->wallE.img_data = (int*)mlx_get_data_addr(mlxvar->wallE.img,
	&mlxvar->wallE.bpp, &mlxvar->wallE.line_size, &mlxvar->wallE.endian);
	mlxvar->wallS.img = mlx_xpm_file_to_image(mlxvar->id , mlxvar->set->SO,
	&mlxvar->wallS.width, &mlxvar->wallS.height);
	mlxvar->wallS.img_data = (int*)mlx_get_data_addr(mlxvar->wallS.img,
	&mlxvar->wallS.bpp, &mlxvar->wallS.line_size, &mlxvar->wallS.endian);
	mlxvar->wallW.img = mlx_xpm_file_to_image(mlxvar->id , mlxvar->set->WE,
	&mlxvar->wallW.width, &mlxvar->wallW.height);
	mlxvar->wallW.img_data = (int*)mlx_get_data_addr(mlxvar->wallW.img,
	&mlxvar->wallW.bpp, &mlxvar->wallW.line_size, &mlxvar->wallW.endian);
	mlxvar->sprite.img = mlx_xpm_file_to_image(mlxvar->id , mlxvar->set->S,
	&mlxvar->sprite.width, &mlxvar->sprite.height);
	mlxvar->sprite.img_data = (int*)mlx_get_data_addr(mlxvar->sprite.img,
	&mlxvar->sprite.bpp, &mlxvar->sprite.line_size, &mlxvar->sprite.endian);
}

int				init_textures(t_mlxvar *mlxvar)
{
	mlxvar->wallN.img = NULL;
	mlxvar->wallN.img_data = NULL;
	mlxvar->wallE.img = NULL;
	mlxvar->wallE.img_data = NULL;
	mlxvar->wallS.img = NULL;
	mlxvar->wallS.img_data = NULL;
	mlxvar->wallW.img = NULL;
	mlxvar->wallW.img_data = NULL;
	mlxvar->sprite.img = NULL;
	mlxvar->sprite.img_data = NULL;
	mlxvar->screen.img = NULL;
	mlxvar->wallN.img_data = NULL;
	mlxvar->rays = NULL;
	allocTextures(mlxvar);
	if (!mlxvar->wallN.img || !mlxvar->wallN.img_data || !mlxvar->wallE.img
	|| !mlxvar->wallE.img_data || !mlxvar->wallS.img || !mlxvar->wallS.img_data
	|| !mlxvar->wallW.img || !mlxvar->wallW.img_data || !mlxvar->sprite.img
	|| !mlxvar->sprite.img_data	|| !mlxvar->screen.img || !mlxvar->screen.img_data)
		return (-1);
	return (0);
}

t_mlxvar		initMlx(t_set *set, int flags, t_bool *save)
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
	mlxvar.posX = (double)mlxvar.set->spawn.X + 0.5;
	mlxvar.posY = (double)mlxvar.set->spawn.Y + 0.5;
	mlxvar.lastKey = -1;
	mlxvar.isKeyPressed = 0;
}

