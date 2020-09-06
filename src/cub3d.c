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

void	save_screen(t_mlximg *screen)
{
	(void)screen;
}

int		update_screen(t_mlxvar *mlxvar)
{
	int		i;
	int		j;
	double	k;
	double	size;

	if (!mlxvar->screen.img || !mlxvar->screen.img_data)
		return (clear_mlx(mlxvar));
	i = -1;
	while (++i < mlxvar->screen.width)
	{
		size = (double)mlxvar->screen.height / (cos(mlxvar->rays[i].rot) * mlxvar->rays[i].siz);
		j = -1;
		while (++j < (int)((mlxvar->screen.height / 2) - (size / 2) - 1))
			mlxvar->screen.img_data[j * mlxvar->screen.width + i] = mlxvar->set->C;
		k = 0;
		printf("1\n");
		while (++j < (mlxvar->screen.height / 2) + (size / 2) - 1)
		{
			mlxvar->screen.img_data[j * mlxvar->screen.width + i] = mlxvar->rays[i].texture->img_data[(int)k * mlxvar->rays[i].texture->width + mlxvar->rays[i].col_pos];
			k += (size / mlxvar->screen.height);
		}
		printf("2\n");
		while (++j < mlxvar->screen.height)
			mlxvar->screen.img_data[j * mlxvar->screen.width + i] = mlxvar->set->F;
	}
	return (0);
}

int		init_textures(t_mlxvar *mlxvar)
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
	mlxvar->screen.img = mlx_new_image(mlxvar->id, mlxvar->set->X, mlxvar->set->Y);
	mlxvar->screen.img_data = (int*)mlx_get_data_addr(mlxvar->screen.img, &mlxvar->screen.bpp, &mlxvar->screen.line_size, &mlxvar->screen.endian);
	mlxvar->screen.width = mlxvar->set->X;
	mlxvar->screen.height = mlxvar->set->Y;
	mlxvar->wallN.img = mlx_xpm_file_to_image(mlxvar->id , mlxvar->set->NO, &mlxvar->wallN.width, &mlxvar->wallN.height);
	mlxvar->wallN.img_data = (int*)mlx_get_data_addr(mlxvar->wallN.img, &mlxvar->wallN.bpp, &mlxvar->wallN.line_size, &mlxvar->wallN.endian);
	mlxvar->wallE.img = mlx_xpm_file_to_image(mlxvar->id , mlxvar->set->EA, &mlxvar->wallE.width, &mlxvar->wallE.height);
	mlxvar->wallE.img_data = (int*)mlx_get_data_addr(mlxvar->wallE.img, &mlxvar->wallE.bpp, &mlxvar->wallE.line_size, &mlxvar->wallE.endian);
	mlxvar->wallS.img = mlx_xpm_file_to_image(mlxvar->id , mlxvar->set->SO, &mlxvar->wallS.width, &mlxvar->wallS.height);
	mlxvar->wallS.img_data = (int*)mlx_get_data_addr(mlxvar->wallS.img, &mlxvar->wallS.bpp, &mlxvar->wallS.line_size, &mlxvar->wallS.endian);
	mlxvar->wallW.img = mlx_xpm_file_to_image(mlxvar->id , mlxvar->set->WE, &mlxvar->wallW.width, &mlxvar->wallW.height);
	mlxvar->wallW.img_data = (int*)mlx_get_data_addr(mlxvar->wallW.img, &mlxvar->wallW.bpp, &mlxvar->wallW.line_size, &mlxvar->wallW.endian);
	mlxvar->sprite.img = mlx_xpm_file_to_image(mlxvar->id , mlxvar->set->S, &mlxvar->sprite.width, &mlxvar->sprite.height);
	mlxvar->sprite.img_data = (int*)mlx_get_data_addr(mlxvar->sprite.img, &mlxvar->sprite.bpp, &mlxvar->sprite.line_size, &mlxvar->sprite.endian);
	if (!mlxvar->wallN.img || !mlxvar->wallN.img_data || !mlxvar->wallE.img
	|| !mlxvar->wallE.img_data || !mlxvar->wallS.img || !mlxvar->wallS.img_data
	|| !mlxvar->wallW.img || !mlxvar->wallW.img_data || !mlxvar->sprite.img
	|| !mlxvar->sprite.img_data	|| !mlxvar->screen.img || !mlxvar->screen.img_data)
		return (-1);
	return (0);
}

int		updateanddisplay(int key, t_mlxvar *mlxvar)
{
	double	dx;
	double	dy;

	dx = (cos(mlxvar->set->rot_hor) / CUBSIZ);
	dy = (sin(mlxvar->set->rot_hor) / CUBSIZ);
	if (key == KEY_LEFT)
	{
		mlxvar->set->rot_hor += M_PI / 180;
		if (mlxvar->set->rot_hor < 0)
			mlxvar->set->rot_hor = 2 * M_PI - mlxvar->set->rot_hor;
	}
	if (key == KEY_RIGHT)
	{
		mlxvar->set->rot_hor -= M_PI / 180;
		if (mlxvar->set->rot_hor > 2 * M_PI)
			mlxvar->set->rot_hor = mlxvar->set->rot_hor - 2 * M_PI;
	}
	if ((key == KEY_UP) && (mlxvar->set->map[(int)(mlxvar->posY + dy)][(int)(mlxvar->posX + dx)] == '0'))
	{
		mlxvar->posX += dx;
		mlxvar->posY += dy;
	}
	if ((key == KEY_DOWN) && (mlxvar->set->map[(int)(mlxvar->posY - dy)][(int)(mlxvar->posX - dx)] == '0'))
	{
		mlxvar->posX -= dx;
		mlxvar->posY -= dy;
	}
	free(mlxvar->rays);
	if (!(mlxvar->rays = update_rays(*mlxvar))
	|| update_screen(mlxvar))
		return (clear_mlx(mlxvar));
	mlx_put_image_to_window(mlxvar->id, mlxvar->win, mlxvar->screen.img, 0, 0);
	return (0);
}

int		cub3D(t_set *set, int flags)
{
	t_bool		save;
	t_mlxvar	mlxvar;

	save = false;
	if ((flags == SAVE) || (flags == (SAVE | BONUS)))
		save = true;
	mlxvar.set = set;
	display_map(mlxvar.set->map);
	mlxvar.id = NULL;
	mlxvar.win = NULL;
	mlxvar.screen.img = NULL;
	mlxvar.screen.img_data = NULL;
	mlxvar.rays = NULL;
	mlxvar.posX = (double)mlxvar.set->spawn.X + 0.5;
	mlxvar.posY = (double)mlxvar.set->spawn.Y + 0.5;
	if (!(mlxvar.id = mlx_init()) || init_textures(&mlxvar)
	|| !(mlxvar.win = mlx_new_window(mlxvar.id, set->X, set->Y, "Cub3D"))
	|| !(mlxvar.rays = update_rays(mlxvar)) || update_screen(&mlxvar))
	{
		clear_set(set);
		clear_mlx(&mlxvar);
		return (ft_fputs(2, "Cub3D: Error while initializing window.\n"));
	}
	mlx_put_image_to_window(mlxvar.id, mlxvar.win, mlxvar.screen.img, 0, 0);
	if (save)
		save_screen(&mlxvar.screen);
	mlx_hook(mlxvar.win, KeyPress, KeyPressMask, &updateanddisplay, &mlxvar);
	mlx_loop(mlxvar.id);
	clear_mlx(&mlxvar);
	return (0);
}
