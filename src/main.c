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
	int		i;

	i = -1;
	wrong = false;
	while (++i < ac)
		if (ft_strcmp(map_path, av[i]) && ft_strcmp("-save", av[i])
		&& ft_strcmp("--save", av[i]) && ft_strcmp("-s", av[i])
		&& ft_strcmp("--bonus", av[i]) && ft_strcmp("-b", av[i])
		&& ft_strcmp("--help", av[i]) && ft_strcmp("-h", av[i]))
		{
			wrong = true;
			ft_fputs(_stderr, "Cub3D: invalid option -- '");
			while (*av[ac] == '-')
				av[ac]++;
			ft_fputs(_stderr, av[i]);
			ft_fputs(_stderr, "'\n");
		}
	if (wrong)
		ft_fputs(_stderr, "Use --help for help\n");
	return (wrong);
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

int				main(int ac, char **av)
{
	char	*path;
	int		fd;
	int		ret;
	t_set	settings;

	if ((ac < 2) || arg_help(ac - 1, av + 1))
		return (help((ac < 2) ? H_NOARG : H_HELP));
	if (!(path = search_str(".cub", av + 1, ac - 1, END)))
		return (error_wrong_map(ER_WPATH));
	if ((fd = open(path, O_RDONLY)) < 0)
		return (error_wrong_map(ER_OPENF));
	if ((ret = get_set(fd, &settings)) - 0)
		return (error_wrong_map(ret));
	if (print_wrong(path, ac - 1, av + 1))
		return (-1);
	if (arg_save(ac - 1, av + 1))
	{
		if (arg_bonus(ac - 1, av + 1))
			return (cub3D(settings, SAVE | BONUS));
		return (cub3D(settings, SAVE));
	}
	if (arg_bonus(ac - 1, av + 1))
		return (cub3D(settings, BONUS));
	return (cub3D(settings, NONE));
}
