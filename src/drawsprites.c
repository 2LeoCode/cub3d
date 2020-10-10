/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawsprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 23:43:34 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/10 22:26:00 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void		drawCurrentSprite(t_mlxvar *mlx, t_spriteVar *sv)
{
	while (sv->screenC.X < sv->end.X)
	{
		sv->screenC.Y = (mlx->screen.height / 2) - (sv->size / 2);
		sv->end.Y = (((sv->screenC.Y + sv->size) < mlx->screen.height) ?
		(sv->screenC.Y + sv->size) : mlx->screen.height);
		sv->d.Y = -sv->screenC.Y * (sv->screenC.Y < 0);
		sv->screenC.Y += sv->d.Y;
		sv->textC.y = (sv->d.Y / sv->size) * mlx->sprite.width;
		while (sv->screenC.Y < sv->end.Y)
		{
			if (mlx->sprite.img_data[(int)sv->textC.y * mlx->sprite.width
			+ (int)sv->textC.x] && (mlx->rays[sv->screenC.X].siz > sv->lst->len))
				mlx->screen.img_data[sv->screenC.Y * mlx->screen.width + sv->screenC.X]
				= mlx->sprite.img_data
				[(int)sv->textC.y * mlx->sprite.width + (int)sv->textC.x];
			sv->screenC.Y++;
			sv->textC.y += sv->rap.y;
		}
		sv->screenC.X++;
		sv->textC.x += sv->rap.x;
	}
}

int				draw_sprites(t_mlxvar *mlx)
{
	t_spriteVar		sv;

	sv.lst = mlx->spList;
	while (sv.lst)
	{
		sv.a = sv.lst->a - mlx->set->rot_hor;
		if (mlx->set->rot_hor > _3PI2)
			sv.a += _2PI;
		if (sv.a > _3PI2)
			sv.a -= _2PI;
		sv.size = (double)mlx->screen.height / (cos(sv.a) * sv.lst->len);
		sv.screenC.X = ((sv.a + (mlx->set->FOV / 2) / mlx->set->FOV) * mlx->screen.width)
		- (sv.size / 2);
		sv.end.X = (((sv.screenC.X + sv.size) < mlx->screen.width) ?
		(sv.screenC.X + sv.size) : mlx->screen.width);
		sv.d.X = -sv.screenC.X * (sv.screenC.X < 0);
		sv.screenC.X += sv.d.X;
		sv.textC.x = (sv.d.X / sv.size) * mlx->sprite.width;
		sv.rap.x = (1 / sv.size) * mlx->sprite.width;
		sv.rap.y = (1 / sv.size) * mlx->sprite.height;
		drawCurrentSprite(mlx, &sv);
		sv.lst = sv.lst->next;
	}
	freeSpList(&mlx->spList);
	return (0);
}
