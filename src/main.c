/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 21:54:36 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/14 21:54:36 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void		init_set(t_set *set)
{
	set->map = NULL;
	set->NO = NULL;
	set->SO = NULL;
	set->WE = NULL;
	set->EA = NULL;
	set->S = NULL;
}

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

static t_bool	arg_help(int ac, char **av)
{
	if (search_str("--help", av, ac, ALL)
	|| search_str("-h", av, ac, ALL))
		return (true);
	return (false);
}

double			arg_fov(int ac, char **av)
{
	char	*tmp;

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
	return (M_PI / 4);
}

int				main(int ac, char **av)
{
	char	*path;
	int		fd;
	int		ret;
	t_set	settings;

	init_set(&settings);
	if ((ac < 2) || arg_help(ac - 1, av + 1))
		return (help((ac < 2) ? H_NOARG : H_HELP));
	if (!(path = search_str(".cub", av + 1, ac - 1, END)))
		return (error_wrong_map(ER_WPATH));
	if ((fd = open(path, O_RDONLY)) < 0)
		return (error_wrong_map(ER_OPENF));
	if ((ret = get_set(fd, &settings)) - 0)
	{
		clear_set(&settings);
		return (error_wrong_map(ret));
	}
	if (print_wrong(path, ac - 1, av + 1))
		return (-1);
	if (arg_save(ac - 1, av + 1))
	{
		if (arg_bonus(ac - 1, av + 1))
			return (cub3D(&settings, SAVE | BONUS));
		return (cub3D(&settings, SAVE));
	}
	settings.FOV = arg_fov(ac - 1, av + 1);
	if (arg_bonus(ac - 1, av + 1))
		return (cub3D(&settings, BONUS));
	return (cub3D(&settings, NONE));
}
