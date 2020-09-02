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
	t_ray		*tmp;
	int			i;
	double		r;
	double		bx;
	double		by;
	double		dx;
	double		dy;

	if (!(tmp = malloc(sizeof(t_ray) * mlxvar.set->X)))
		return (NULL);
	i = -1;
	r = -(mlxvar.set->FOV / 2);
	while (++i < mlxvar.set->X)
	{
		tmp[i].rot = r;
		dx = cos(mlxvar.set->rot_hor + r) / 1000;
		dy = sin(mlxvar.set->rot_hor + r) / 1000;
		bx = mlxvar.posX;
		by = mlxvar.posY;

		while (mlxvar.set->map[(int)by][(int)bx] - '1')
		{
			bx += dx;
			by += dy;
		}
		tmp[i].siz = sqrt((bx - mlxvar.posX) * (bx - mlxvar.posX) + (by - mlxvar.posY) * (by - mlxvar.posY));
		if ((double)(bx - (int)bx) < 0.001)
		{
			tmp[i].texture = (((mlxvar.set->rot_hor - r > M_PI) && (mlxvar.set->rot_hor - r < 3 * M_PI / 4)) ? &mlxvar.wallW : &mlxvar.wallE);
			tmp[i].col_pos = (by - (int)by) * tmp[i].texture->width;
			printf("VERT: %lf %lf\n", bx, by);
		}
		else
		{
			tmp[i].texture = ((mlxvar.set->rot_hor - r < 2 * M_PI) ? &mlxvar.wallN : &mlxvar.wallS);
			tmp[i].col_pos = (bx - (int)bx) * tmp[i].texture->width;
		}
		r += (mlxvar.set->FOV / mlxvar.set->X);
	}
	return (tmp);
}