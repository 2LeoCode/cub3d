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

void	drawCols(t_mlxvar *mlxvar, t_updateVar *up)
{
	while (++up->j < (((int)up->size > mlxvar->screen.height) ? mlxvar->screen.height
	: (int)up->size))
	{
		mlxvar->screen.img_data[(up->l + up->j) * mlxvar->screen.width + up->i]
		= mlxvar->rays[up->i].texture->img_data
		[(int)up->k * mlxvar->rays[up->i].texture->width + mlxvar->rays[up->i].col_pos];
		up->k += mlxvar->rays[up->i].texture->height / up->size;
	}
}

int		update_screen(t_mlxvar *mlxvar)
{
	t_updateVar		up;
	
	if (!mlxvar->screen.img || !mlxvar->screen.img_data)
		return (clear_mlx(mlxvar));
	up.i = mlxvar->screen.width;
	while (--up.i >= 0)
	{
		up.size = (double)mlxvar->screen.height
		/ (cos(mlxvar->rays[up.i].rot) * mlxvar->rays[up.i].siz);
		up.j = -1;
		while (++up.j < (int)(mlxvar->screen.height / 2))
			mlxvar->screen.img_data[up.j * mlxvar->screen.width + up.i] = mlxvar->set->C;
		while (++up.j < mlxvar->screen.height)
			mlxvar->screen.img_data[up.j * mlxvar->screen.width + up.i] = mlxvar->set->F;
		up.j = -1;
		up.l = ((up.size > mlxvar->screen.height) ?
		0 : ((int)(mlxvar->screen.height / 2) - (up.size / 2)));
		up.k = (up.size < mlxvar->screen.height) ? 0 : ((((up.size / 2)
		- (mlxvar->screen.height / 2)) / up.size) * mlxvar->rays[up.i].texture->height);
		drawCols(mlxvar, &up);
	}
	return (0);
}

int		updateanddisplay(t_mlxvar *mlxvar)
{
	int			key;
	double		cSize;
	t_dVar		d;

	if (!mlxvar->isKeyPressed)
		return (0);
	key = mlxvar->lastKey;
	cSize = 0.3;
	d.r = (M_PI / 180);
	checkKeys(mlxvar, key, d, cSize);
	if (update_rays(mlxvar)
	|| update_screen(mlxvar) || draw_sprites(mlxvar))
		return (clear_mlx_err(mlxvar));
	mlx_put_image_to_window(mlxvar->id, mlxvar->win, mlxvar->screen.img, 0, 0);
	return (0);
}

int		cub3D(t_set *set, int flags)
{
	t_bool		save;
	t_mlxvar	mlxvar;

	mlxvar = initMlx(set, flags, &save);
	if (!(mlxvar.id = mlx_init()) || init_textures(&mlxvar)
	|| !(mlxvar.win = mlx_new_window(mlxvar.id, set->X, set->Y, "Cub3D"))
	|| update_rays(&mlxvar) || update_screen(&mlxvar) || draw_sprites(&mlxvar))
	{
		clear_mlx_err(&mlxvar);
		return (ft_fputs(2, "Cub3D: Error while initializing window.\n"));
	}
	mlx_put_image_to_window(mlxvar.id, mlxvar.win, mlxvar.screen.img, 0, 0);
	if (save)
		save_screen(&mlxvar.screen);
	mlx_loop_hook(mlxvar.id, &updateanddisplay, &mlxvar);
	mlx_hook(mlxvar.win, KeyPress, KeyPressMask, &keyIsPressed, &mlxvar);
	mlx_hook(mlxvar.win, KeyRelease, KeyReleaseMask, &keyIsReleased, &mlxvar);
	mlx_hook(mlxvar.win, DestroyNotify, StructureNotifyMask, &clear_mlx, &mlxvar);
	mlx_loop(mlxvar.id);
	return (clear_mlx(&mlxvar));
}
