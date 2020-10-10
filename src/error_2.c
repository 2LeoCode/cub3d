/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 23:06:09 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/10 15:21:31 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_bool	print_wrong(char *map_path, int ac, char **av)
{
	t_bool	wrong;
	int		i;

	i = -1;
	wrong = false;
	while (++i < ac)
		if (ft_strcmp(map_path, av[i]) && ft_strcmp("-save", av[i])
		&& ft_strcmp("--save", av[i]) && ft_strcmp("-s", av[i])
		&& ft_strcmp("--bonus", av[i]) && ft_strcmp("-b", av[i])
		&& ft_strcmp("--help", av[i]) && ft_strcmp("-h", av[i])
		&& ft_strcmp("--fov", av[i]))
		{
			if (i > 0 && !ft_strcmp("--fov", av[i - 1]))
				continue ;
			wrong = true;
			ft_fputs(_stderr, "cub3d: invalid option -- '");
			while (*av[i] == '-')
				av[i]++;
			ft_fputs(_stderr, av[i]);
			ft_fputs(_stderr, "'\n");
		}
	if (wrong)
		ft_fputs(_stderr, "use --help for help\n");
	return (wrong);
}
