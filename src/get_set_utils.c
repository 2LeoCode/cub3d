/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 18:24:32 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/10 14:47:58 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

unsigned long	create_color_int(t_rgb color)
{
	return (((color.r & 0xff) << 16) + ((color.g & 0xff) << 8)
	+ (color.b & 0xff));
}

static int		get_single_rgb(char **line, int *col)
{
	while (ft_isspace(**line))
		(*line)++;
	if (**line && !ft_isdigit(**line))
		return (-1);
	*col = ft_atoi(*line);
	while (ft_isdigit(**line))
		(*line)++;
	while (ft_isspace(**line))
		(*line)++;
	return (0);
}

int				get_rgb(char *line, t_set *set, t_bool *check)
{
	t_rgb	tmp;
	int		*col;

	if ((*line == 'f' && check[c_f]) || (*line == 'c' && check[c_c]))
		return (ER_DOUBL);
	if (*line == 'f')
		col = &set->f;
	else if (*line == 'c')
		col = &set->c;
	line++;
	if (!ft_isspace(*line))
		return (ER_UNKNW);
	if (get_single_rgb(&line, &tmp.r) || (*(line++) - ',')
	|| get_single_rgb(&line, &tmp.g) || (*(line++) - ',')
	|| get_single_rgb(&line, &tmp.b) || *line)
		return (ER_WRRGB);
	*col = (int)create_color_int(tmp);
	check[((col == &set->f) ? C_F : C_C)] = true;
	return (0);
}


static int	getres2(char *line, t_set *set, t_bool *check)
{
	if (*line)
		return (ER_WRRES);
	check[C_Y] = true;
	if ((set->x < 50) || (set->y < 50) || (set->x > 1980) || (set->y > 1080))
	{
		error_wrong_map(ER_WRRES | WARNING);
		set->x = 800;
		set->y = 600;
	}
	return (0);
}

int			get_res(char *line, t_set *set, t_bool *check)
{
	if (check[C_X] || check[C_Y])
		return (ER_DOUBL);
	line++;
	if (*line && !ft_isspace(*line))
		return (ER_WRRES);
	while (ft_isspace(*line))
		line++;
	set->x = ft_atoi(line);
	check[C_X] = true;
	while (ft_isdigit(*line))
		line++;
	if (*line && !ft_isspace(*line))
		return (ER_WRRES);
	while (ft_isspace(*line))
		line++;
	set->y = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	while (ft_isspace(*line))
		line++;
	return (getres2(line, set, check));
}
