/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 00:53:38 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/15 00:53:38 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static t_bool	is_check(t_bool *check)
{
	int		i;

	i = -1;
	while (++i < NB_PARAMS)
		if (!check[i])
			return (false);
	return (true);
}

int			getSet2(int fd, t_getSetVar *v, t_set *set)
{
	while (!v->total)
	{
		v->i = 0;
		while (ft_isspace(v->line[v->i]))
			v->i++;
		if (((v->line[v->i] == 'R') && (v->i = get_res(&line[v->i], set, v->check)))
		|| ((v->line[v->i] && ft_strchr("FC", v->line[v->i]))
		&& (v->i = get_rgb(&v->line[v->i], set, v->check)))
		|| (!ft_strchr("RFC", v->line[v->i])
		&& (v->i = get_path(&v->line[v->i], set, v->check))))
			return (v->i);
		free(v->line);
		if (!(v->total = is_check(v->check))
		&& ((v->i = get_next_line(fd, &v->line)) < 0))
			return (ER_READF);
		if (!v->total && !v->i)
			return (ER_WRMAP);
	}
	return (0);
}

int			get_set(int fd, t_set *set)
{
	t_getSetVar		v;

	v.i = -1;
	v.total = false;
	while (++v.i < NB_PARAMS)
		v.check[v.i] = 0;
	if ((v.i = get_next_line(fd, &v.line)) < 0)
		return (ER_READF);
	if (v.i = getSet2(fd, &v, set))
		return (v.i);
	return (get_map(fd, set));
}

int			getSettings(int ac, char **av, t_set *settings)
{
	int		fd;
	int		ret;
	char	*path;

	if ((ac < 2) || arg_help(ac - 1, av + 1))
		return (help((ac < 2) ? H_NOARG : H_HELP));
	if (!(path = search_str(".cub", av + 1, ac - 1, END)))
		return (error_wrong_map(ER_WPATH));
	if ((fd = open(path, O_RDONLY)) < 0)
		return (error_wrong_map(ER_OPENF));
	if ((ret = get_set(fd, &settings)) - 0)
	{
		clear_set(&settings);
		return (ret);
	}
	if (print_wrong(path, ac - 1, av + 1))
		return (ER_DEFLT);
}

void		init_set(t_set *set)
{
	set->map = NULL;
	set->NO = NULL;
	set->SO = NULL;
	set->WE = NULL;
	set->EA = NULL;
	set->S = NULL;
}
