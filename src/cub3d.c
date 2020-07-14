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

void	init_nrm(t_mlxvar *cub3d)
{
	cub3d->nrm_X.X = 1;
	cub3d->nrm_X.Y = 0;
	cub3d->nrm_X.Z = 0;
	cub3d->nrm_Y.X = 0;
	cub3d->nrm_Y.Y = 1;
	cub3d->nrm_Y.Z = 0;
	cub3d->nrm_Z.X = 0;
	cub3d->nrm_Z.Y = 0;
	cub3d->nrm_Z.Z = -1;
}

void	refresh_nrm(t_mlxvar *cub3d)
{
	cub3d->look.X = sin(cub3d->set->rot_hor);
	cub3d->look.Y = sin(cub3d->set->rot_vert);
	cub3d->look.Z = look.X * tan((M_PI / 2) - cub3d->set->rot_hor);
}

int		cub3D(t_set *set, int flags)
{
	t_bool		save;
	t_mlxvar	cub3d;
	int			check;

	save = false;
	if ((flags == SAVE) || (flags == SAVE | BONUS))
		save = true;
	if (((flags == BONUS) || (flags == SAVE | BONUS)))
	{
		if ((check = check_set_bonus(&set)) != 0)
			return (error_wrong_map(check));
		return (cub3D_bonus(set, save));
	}
	cub3d.set = set;
	init_nrm(&cub3d)
	refresh_pos(cub3d);
	if (!(cub3d.key = mlx_init()) || !(cub3d.win = mlx_new_window(cub3d.key, set->X, set->Y, "Cub3D")))
		return (error_mlx(ER_DEFLT));
	clear_set(set);
	return (0);
}
