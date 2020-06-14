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

static t_bool	print_wrong(char *map_path, int ac, char **av)
{
	t_bool	wrong;
	
	wrong = false;
	while (ac--)
		if (ft_strcmp(map_path, av[ac]) && ft_strcmp("-save", av[ac])
		&& ft_strcmp("--save", av[ac]) && ft_strcmp("-s", av[ac])
		&& ft_strcmp("--bonus", av[ac]) && ft_strcmp("-b", av[ac])
		&& ft_strcmp("--help", av[ac]) && ft_strcmp("-h", av[ac]))
		{
			wrong = true;
			ft_fputs(_stderr, "Cub3D: invalid option -- '");
			while (*av[ac] == '-')
				av[ac]++;
			ft_fputs(_stderr, av[ac]);
			ft_fputs(_stderr, "'\nUse --help for help\n");
		}
	return (wrong);
}

static t_bool	arg_save(int ac, char **av)
{
	if (search_str("-save", av + 1, ac - 1, ALL)
	|| search_str("--save", av + 1, ac - 1, ALL)
	|| search_str("-s", av + 1, ac - 1, ALL))
		return (true);
	return (false);
}

static t_bool	arg_bonus(int ac, char **av)
{
	if (search_str("--bonus", av + 1, ac - 1, ALL)
	|| search_str("-b", av + 1, ac - 1, ALL))
		return (true);
	return (false);
}

static t_bool	arg_help(int ac, char **av)
{
	if (search_str("--help", av + 1, ac - 1, ALL)
	|| search_str("-h", av + 1, ac - 1, ALL))
		return (true);
	return (false);
}

int				main(int ac, char **av)
{
	char	*path;
	int		fd;
	int		ret;
	t_set	settings;

	if ((ac < 2) || !(path = search_str(".cub", av + 1, ac - 1, END)))
		return (error_wrong_file(ER_WPATH));
	if (arg_help(ac - 1, av + 1))
		return (help());
	if ((fd = open(path, O_RDONLY)) < 0))
		return (error_wrong_file(ER_OPENF));
	if ((ret = get_set(fd, &settings)) - 0)
		return (error_wrong_file(ret));
	if (arg_save(ac - 1, av + 1))
	{
		if (arg_bonus(ac - 1, av + 1))
			return (cub3D(settings, SAVE | BONUS));
		return (cub3D(settings, SAVE));
	}
	if (print_wrong(path, ac - 1, av + 1))
		return (-1);
	if (arg_bonus(ac - 1, av + 1))
		return (cub3D(settings, BONUS));
	return (cub3D(settings, NONE));
}
