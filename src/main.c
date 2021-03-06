/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 21:54:36 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/10 21:55:40 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static t_bool	arg_save(int ac, char **av)
{
	if (search_str("-save", av, ac, ALL)
	|| search_str("--save", av, ac, ALL)
	|| search_str("-s", av, ac, ALL))
		return (true);
	return (false);
}

static t_bool	arg_bonus(int ac, char **av)
{
	if (search_str("--bonus", av, ac, ALL)
	|| search_str("-b", av, ac, ALL))
		return (true);
	return (false);
}

double			arg_fov(int ac, char **av)
{
	while (ac--)
	{
		av++;
		if (!ft_strcmp(*(av - 1), "--fov"))
		{
			if (!ac || !str_isdigit(*av))
				return (-1);
			return (ft_atoi(*av) * M_PI / 180);
		}
	}
	return (1.0472);
}

int				main(int ac, char **av)
{
	int		ret;
	t_set	settings;

	init_set(&settings);
	if ((ret = getsettings(ac, av, &settings)))
		return (error_wrong_map(ret));
	if ((settings.fov = arg_fov(ac - 1, av + 1)) < 0)
		return (error_wrong_map(ER_DEFLT));
	if (arg_save(ac - 1, av + 1))
	{
		if (arg_bonus(ac - 1, av + 1))
			return (cub3d(&settings, SAVE | BONUS));
		return (cub3d(&settings, SAVE));
	}
	if (arg_bonus(ac - 1, av + 1))
		return (cub3d(&settings, BONUS));
	return (cub3d(&settings, NONE));
}
