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

int		cub3D(t_set *set, int flags)
{
	(void)flags;
	/*t_bool	save;
	void	*key;
	void	*init;
	int		check;

	save = false;
	if ((flags == SAVE) || (flags == SAVE | BONUS))
		save = true;
	if (((flags == BONUS) || (flags == SAVE | BONUS)))
	{
		if ((check = check_set_bonus(&set)) != 0)
			return (error_wrong_map(check));
		return (cub3D_bonus(set, save));
	}
	if (!(key = mlx_init()))
		return (error_mlx(ER_DEFLT));
	if (!(init = mlx_new_window(key, set->X, set->Y, "Cub3D")))
		return (error_mlx(ER_DEFLT));
	*/
	clear_set(set);
	return (0);
}
