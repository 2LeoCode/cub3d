/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 22:43:31 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/10 21:54:14 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void		clear_set(t_set *set)
{
	int		i;

	i = -1;
	if (set->no)
		free(set->no);
	set->no = NULL;
	if (set->we)
		free(set->we);
	set->we = NULL;
	if (set->ea)
		free(set->ea);
	set->ea = NULL;
	if (set->so)
		free(set->so);
	set->so = NULL;
	if (set->s)
		free(set->s);
	set->s = NULL;
	while (set->map && set->map[++i])
	{
		free(set->map[i]);
		set->map[i] = NULL;
	}
	free(set->map);
	set->map = NULL;
}

void		clear_paths(t_set *set)
{
	free(set->no);
	set->no = NULL;
	free(set->we);
	set->we = NULL;
	free(set->ea);
	set->ea = NULL;
	free(set->so);
	set->so = NULL;
	free(set->s);
	set->s = NULL;
}

int			clear_mlx_err(t_mlxvar *mlx)
{
	clear_mlx(mlx);
	return (-1);
}

static int	clear_mlx2(t_mlxvar *mlx)
{
	if (mlx->walle.img_data)
		free(mlx->walle.img_data);
	mlx->walle.img_data = NULL;
	if (mlx->walls.img)
		mlx_destroy_image(mlx->id, mlx->walls.img);
	mlx->walls.img = NULL;
	if (mlx->walls.img_data)
		free(mlx->walls.img_data);
	mlx->walls.img_data = NULL;
	if (mlx->wallw.img)
		mlx_destroy_image(mlx->id, mlx->wallw.img);
	mlx->wallw.img = NULL;
	if (mlx->wallw.img_data)
		free(mlx->wallw.img_data);
	mlx->wallw.img_data = NULL;
	clear_set(mlx->set);
	exit(exit_success);
	return (0);
}

int			clear_mlx(t_mlxvar *mlx)
{
	if (mlx->win)
		mlx_destroy_window(mlx->id, mlx->win);
	mlx->win = NULL;
	if (mlx->rays)
		free(mlx->rays);
	mlx->rays = NULL;
	if (mlx->screen.img)
		mlx_destroy_image(mlx->id, mlx->screen.img);
	mlx->screen.img = NULL;
	if (mlx->screen.img_data)
		free(mlx->screen.img_data);
	mlx->screen.img_data = NULL;
	if (mlx->walln.img)
		mlx_destroy_image(mlx->id, mlx->walln.img);
	mlx->walln.img = NULL;
	if (mlx->walln.img_data)
		free(mlx->walln.img_data);
	mlx->walln.img_data = NULL;
	if (mlx->walle.img)
		mlx_destroy_image(mlx->id, mlx->walle.img);
	mlx->walle.img = NULL;]
	return (clear_mlx2(mlx));
}
