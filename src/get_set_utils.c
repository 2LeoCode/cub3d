/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 18:24:32 by lsuardi           #+#    #+#             */
/*   Updated: 2020/08/07 18:24:32 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

unsigned long	create_color_int(t_rgb color)
{
	return (((color.R & 0xff) << 16) + ((color.G & 0xff) << 8)
	+ (color.B & 0xff));
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

	if ((*line == 'F' && check[C_F]) || (*line == 'C' && check[C_C]))
		return (ER_DOUBL);
	if (*line == 'F')
		col = &set->F;
	else if (*line == 'C')
		col = &set->C;
	line++;
	if (!ft_isspace(*line))
		return (ER_UNKNW);
	if (get_single_rgb(&line, &tmp.R) || (*(line++) - ',')
	|| get_single_rgb(&line, &tmp.G) || (*(line++) - ',')
	|| get_single_rgb(&line, &tmp.B) || *line)
		return (ER_WRRGB);
	*col = (int)create_color_int(tmp);
	check[((col == &set->F) ? C_F : C_C)] = true;
	return (0);
}


static int	getRes2(char *line, t_set *set, t_bool *check)
{
	if (*line)
		return (ER_WRRES);
	check[C_Y] = true;
	if ((set->X < 50) || (set->Y < 50) || (set->X > 1980) || (set->Y > 1080))
	{
		error_wrong_map(ER_WRRES | WARNING);
		set->X = 800;
		set->Y = 600;
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
	set->X = ft_atoi(line);
	check[C_X] = true;
	while (ft_isdigit(*line))
		line++;
	if (*line && !ft_isspace(*line))
		return (ER_WRRES);
	while (ft_isspace(*line))
		line++;
	set->Y = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	while (ft_isspace(*line))
		line++;
	return (getRes2(line, set, check));
}
