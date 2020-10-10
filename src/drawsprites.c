/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawsprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 23:43:34 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/10 22:27:33 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void		drawCurrentSprite(t_mlxvar *mlx, t_spriteVar *sv)
{
	while (sv->screenC.x < sv->end.x)
	{
		sv->screenC.y = (mlx->screen.height / 2) - (sv->size / 2);
		sv->end.y = (((sv->screenC.y + sv->size) < mlx->screen.height) ?
		(sv->screenC.y + sv->size) : mlx->screen.height);
		sv->d.y = -sv->screenC.y * (sv->screenC.y < 0);
		sv->screenC.y += sv->d.y;
		sv->textC.y = (sv->d.y / sv->size) * mlx->sprite.width;
		while (sv->screenC.y < sv->end.y)
		{
			if (mlx->sprite.img_data[(int)sv->textC.y * mlx->sprite.width
			+ (int)sv->textC.x] && (mlx->rays[sv->screenC.x].siz > sv->lst->len))
				mlx->screen.img_data[sv->screenC.y * mlx->screen.width + sv->screenC.x]
				= mlx->sprite.img_data
				[(int)sv->textC.y * mlx->sprite.width + (int)sv->textC.x];
			sv->screenC.y++;
			sv->textC.y += sv->rap.y;
		}
		sv->screenC.x++;
		sv->textC.x += sv->rap.x;
	}
}

int				draw_sprites(t_mlxvar *mlx)
{
	t_spriteVar		sv;

	sv.lst = mlx->splist;
	while (sv.lst)
	{
		sv.a = sv.lst->a - mlx->set->rot_hor;
		if (mlx->set->rot_hor > _3PI2)
			sv.a += _2PI;
		if (sv.a > _3PI2)
			sv.a -= _2PI;
		sv.size = (double)mlx->screen.height / (cos(sv.a) * sv.lst->len);
		sv.screenC.x = ((sv.a + (mlx->set->fov / 2) / mlx->set->fov) * mlx->screen.width)
		- (sv.size / 2);
		sv.end.x = (((sv.screenC.x + sv.size) < mlx->screen.width) ?
		(sv.screenC.x + sv.size) : mlx->screen.width);
		sv.d.x = -sv.screenC.x * (sv.screenC.x < 0);
		sv.screenC.x += sv.d.x;
		sv.textC.x = (sv.d.x / sv.size) * mlx->sprite.width;
		sv.rap.x = (1 / sv.size) * mlx->sprite.width;
		sv.rap.y = (1 / sv.size) * mlx->sprite.height;
		drawCurrentSprite(mlx, &sv);
		sv.lst = sv.lst->next;
	}
	freesplist(&mlx->splist);
	return (0);
}
