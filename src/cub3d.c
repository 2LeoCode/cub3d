/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 00:22:47 by lsuardi           #+#    #+#             */
/*   Updated: 2020/12/04 18:29:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	drawcols(t_mlxvar *mlxvar, t_updatevar *up)
{
	while (++up->j < (((int)up->size > mlxvar->screen.height) ?
	mlxvar->screen.height : (int)up->size))
	{
		mlxvar->screen.img_data[(up->l + up->j) * mlxvar->screen.width + up->i
] = mlxvar->rays[up->i].texture->img_data
[(int)up->k * mlxvar->rays[up->i].texture->width + (
mlxvar->rays[up->i].col_pos)];
		up->k += mlxvar->rays[up->i].texture->height / up->size;
	}
}

int		update_screen(t_mlxvar *mlxvar)
{
	t_updatevar		up;

	if (!mlxvar->screen.img || !mlxvar->screen.img_data)
		return (clear_mlx(mlxvar));
	up.i = mlxvar->screen.width;
	while (--up.i >= 0)
	{
		up.size = (double)mlxvar->screen.height / (
		cos(mlxvar->rays[up.i].rot) * mlxvar->rays[up.i].siz);
		up.j = -1;
		while (++up.j < (int)(mlxvar->screen.height / 2))
			mlxvar->screen.img_data[up.j * mlxvar->screen.width + up.i
] = mlxvar->set->c;
		while (++up.j < mlxvar->screen.height)
			mlxvar->screen.img_data[up.j * mlxvar->screen.width + up.i
] = mlxvar->set->f;
		up.j = -1;
		up.l = ((up.size > mlxvar->screen.height) ? 0 : (
		(int)(mlxvar->screen.height / 2) - (up.size / 2)));
		up.k = (up.size < mlxvar->screen.height) ? 0 : ((((up.size / 2
) - (mlxvar->screen.height / 2)) / up.size
) * mlxvar->rays[up.i].texture->height);
		drawcols(mlxvar, &up);
	}
	return (0);
}

int		updateanddisplay(t_mlxvar *mlxvar)
{
	int			key;
	t_dvar		d;

	if (!mlxvar->iskeypressed)
		return (0);
	key = mlxvar->lastkey;
	d.r = (M_PI / 180);
	checkkeys(mlxvar, key, d);
	if (update_rays(mlxvar)
	|| update_screen(mlxvar) || draw_sprites(mlxvar))
		return (clear_mlx_err(mlxvar));
	mlx_put_image_to_window(mlxvar->id, mlxvar->win, mlxvar->screen.img, 0, 0);
	return (0);
}

int		displayscreen(t_mlxvar *mlx)
{
	mlx_put_image_to_window(mlx->id, mlx->win, mlx->screen.img, 0, 0);
	return (0);
}

int		cub3d(t_set *set, int flags)
{
	t_bool		save;
	t_mlxvar	mlxvar;

	mlxvar = initmlx(set, flags, &save);
	if (save)
		exit_save(&mlxvar);
	if (!(mlxvar.id = mlx_init()) || init_textures(&mlxvar)
	|| !(mlxvar.win = mlx_new_window(mlxvar.id, set->x, set->y, "Cub3D"))
	|| update_rays(&mlxvar) || update_screen(&mlxvar) || draw_sprites(&mlxvar))
	{
		return (ft_fputs(2, "Cub3d: Error while initializing window.\n"));
		clear_mlx_err(&mlxvar);
	}
	mlx_put_image_to_window(mlxvar.id, mlxvar.win, mlxvar.screen.img, 0, 0);
	mlx_loop_hook(mlxvar.id, &updateanddisplay, &mlxvar);
	mlx_expose_hook(mlxvar.win, &displayscreen, &mlxvar);
	mlx_hook(mlxvar.win, KeyPress, KeyPressMask, &keyispressed, &mlxvar);
	mlx_hook(mlxvar.win, KeyRelease, KeyReleaseMask, &keyisreleased, &mlxvar);
	mlx_hook(mlxvar.win, DestroyNotify, StructureNotifyMask,
&clear_mlx, &mlxvar);
	mlx_loop(mlxvar.id);
	return (clear_mlx(&mlxvar));
}
