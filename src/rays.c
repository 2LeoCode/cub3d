/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 21:56:43 by lsuardi           #+#    #+#             */
/*   Updated: 2020/08/20 21:56:43 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_ray	*update_rays(t_mlxvar mlxvar)
{
	t_ray		*tmp;
	int			i;
	double		r;
	t_point		b;
	t_point		c;
	t_point		length;
	double		d;

	if (!(tmp = malloc(sizeof(t_ray) * mlxvar.set->X)))
		return (NULL);
	i = -1;
	r = -(mlxvar.set->FOV / 2);
	while (++i < mlxvar.set->X)
	{
		tmp[i].rot = r;
		d = tan(mlxvar.set->rot_hor + r);
		printf("1\n");
		if ((mlxvar.set->rot_hor + r) > 0 && (mlxvar.set->rot_hor + r) < M_PI)
			b.y = (int)mlxvar.posY + 1.0001;
		else
			b.y = (int)mlxvar.posY - 0.0001;
		b.x = mlxvar.posX + ft_dabs(b.y - mlxvar.posY) * d;
		printf("%lf %lf\n", b.x, b.y);
		while (mlxvar.set->map[(int)b.y][(int)b.x] - '1')
		{
			b.x += d;
			b.y++;
			printf("%lf %lf\n", b.x, b.y);
		}
		printf("3\n");
		length.y = sqrt((b.x - mlxvar.posX) * (b.x - mlxvar.posX) + (b.y - mlxvar.posY) * (b.y - mlxvar.posY));
		d = 1 / d;
		if (((mlxvar.set->rot_hor + r) > (M_PI / 2)) && ((mlxvar.set->rot_hor + r) < (3 * M_PI / 4)))
			c.x = (int)mlxvar.posX + 1.0001;
		else
			c.x = (int)mlxvar.posX - 0.0001;
		c.y = mlxvar.posY + ft_dabs(c.x - mlxvar.posX) * d;
		printf("%lf %lf\n", c.x, c.y);
		while (mlxvar.set->map[(int)c.y][(int)c.x] - '1')
		{
			c.y += d;
			c.x++;
		}
		printf("5\n");
		length.x = sqrt((c.x - mlxvar.posX) * (c.x - mlxvar.posX) + (c.y - mlxvar.posY) * (c.y - mlxvar.posY));
		if (length.y > length.x)
		{
			tmp[i].siz = length.y;
			tmp[i].texture = (((mlxvar.set->rot_hor + r > 0) && (mlxvar.set->rot_hor + r < M_PI)) ? &mlxvar.wallS : &mlxvar.wallN);
			tmp[i].col_pos = (double)(b.x - (int)b.x) * tmp[i].texture->width;
		}
		else
		{
			tmp[i].siz = length.x;
			tmp[i].texture = (((mlxvar.set->rot_hor + r > (M_PI / 2)) && (mlxvar.set->rot_hor + r < (3 * M_PI / 4))) ? &mlxvar.wallW : &mlxvar.wallE);
			tmp[i].col_pos = (double)(c.y - (int)c.y) * tmp[i].texture->width;
		}
		r += (mlxvar.set->FOV / mlxvar.set->X);
	}
	return (tmp);
}