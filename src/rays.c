/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 21:56:43 by lsuardi           #+#    #+#             */
/*   Updated: 2020/08/20 21:56:43 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_ray	*update_rays(t_mlxvar mlxvar)
{
	t_ray	*tmp;
	int		i;
	int		r;
	int		bx;
	int		by;
	int		dx;
	int		dy;

	tmp = mlxvar.rays;
	if (!tmp && !(tmp = malloc(sizeof(t_ray) * mlxvar.set->X)))
		return (NULL);
	i = -1;
	r = mlxvar.set->rot_hor - (mlxvar.set->FOV / 2);
	while (++i < mlxvar.set->X)
	{
		tmp[i].rot = r;
		dx = cos(r) / 50;
		dy = sin(r) / 50;
		bx = mlxvar.posX;
		by = mlxvar.posY;
		printf("1\n");
		while (by > 0 && bx > 0 && mlxvar.set->map[(int)by] && mlxvar.set->map[(int)by][(int)bx] == '0')
		{
			bx += dx;
			by += dy;
		}
		printf("2\n");
		tmp[i].siz = sqrt((bx - mlxvar.posX) * (bx - mlxvar.posX) + (by - mlxvar.posY) * (by - mlxvar.posY));
		if (mlxvar.set->map[(int)by][(int)(bx - dx)] == '0')
		{
			tmp[i].texture = (((r > M_PI) && (r < 3 * M_PI / 4)) ? &mlxvar.wallW : &mlxvar.wallE);
			tmp[i].col_pos = (by - (int)by) * tmp[i].texture->width;
		}
		else if (mlxvar.set->map[(int)(by - dy)][(int)bx] == '0')
		{
			tmp[i].texture = ((r < 2 * M_PI) ? &mlxvar.wallN : &mlxvar.wallS);
			tmp[i].col_pos = (bx - (int)bx) * tmp[i].texture->width;
		}
		r += (mlxvar.set->FOV / mlxvar.set->X);
	}
	return (tmp);
}