/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 22:43:31 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/16 22:43:31 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	clear_set(t_set *set)
{
	int		i;

	i = -1;	
	if (set->NO)
		free(set->NO);
	set->NO = NULL;
	if (set->WE)
		free(set->WE);
	set->WE = NULL;
	if (set->EA)
		free(set->EA);
	set->EA = NULL;
	if (set->SO)
		free(set->SO);
	set->SO = NULL;
	if (set->S)
		free(set->S);
	set->S = NULL;
	while (set->map && set->map[++i])
	{
		free(set->map[i]);
		set->map[i] = NULL;
	}
	free(set->map);
	set->map = NULL;
}

void	clear_paths(t_set *set)
{
	free(set->NO);
	set->NO = NULL;
	free(set->WE);
	set->WE = NULL;
	free(set->EA);
	set->EA = NULL;
	free(set->SO);
	set->SO = NULL;
	free(set->S);
	set->S = NULL;
}

void	clear_mlx(t_mlxvar *mlx)
{
	if (mlx->win);
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
	if (mlx->wallN.img)
		mlx_destroy_image(mlx->id, mlx->wallN.img);
	mlx->wallN.img = NULL;
	if (mlx->wallN.img_data)
		free(mlx->wallN.img_data);
	mlx->wallN.img_data = NULL;
	if (mlx->wallE.img)
		mlx_destroy_image(mlx->id, mlx->wallE.img);
	mlx->wallE.img = NULL;
	if (mlx->wallE.img_data)
		free(mlx->wallE.img_data);
	mlx->wallE.img_data = NULL;
	if (mlx->wallS.img)
		mlx_destroy_image(mlx->id, mlx->wallS.img);
	mlx->wallS.img = NULL;
	if (mlx->wallS.img_data)
		free(mlx->wallS.img_data);
	mlx->wallS.img_data = NULL;
	if (mlx->wallW.img)
		mlx_destroy_image(mlx->id, mlx->wallW.img);
	mlx->wallW.img = NULL;
	if (mlx->wallW.img_data)
		free(mlx->wallW.img_data);
	mlx->wallW.img_data = NULL;	
}
