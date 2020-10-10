/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawsprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 23:43:34 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/10 22:38:02 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void		drawCurrentSprite(t_mlxvar *mlx, t_spritevar *sv)
{
	while (sv->screenc.x < sv->end.x)
	{
		sv->screenc.y = (mlx->screen.height / 2) - (sv->size / 2);
		sv->end.y = (((sv->screenc.y + sv->size) < mlx->screen.height
		) ? (sv->screenc.y + sv->size) : mlx->screen.height);
		sv->d.y = -sv->screenc.y * (sv->screenc.y < 0);
		sv->screenc.y += sv->d.y;
		sv->textc.y = (sv->d.y / sv->size) * mlx->sprite.width;
		while (sv->screenc.y < sv->end.y)
		{
			if (mlx->sprite.img_data[(int)sv->textc.y * mlx->sprite.width
			+ (int)sv->textc.x] && (mlx->rays[sv->screenc.x
			].siz > sv->lst->len))
				mlx->screen.img_data[sv->screenc.y * mlx
				->screen.width + sv->screenc.x] = mlx->sprite.img_data
				[(int)sv->textc.y * mlx->sprite.width + (int)sv->textc.x];
			sv->screenc.y++;
			sv->textc.y += sv->rap.y;
		}
		sv->screenc.x++;
		sv->textc.x += sv->rap.x;
	}
}

int				draw_sprites(t_mlxvar *mlx)
{
	t_spritevar		sv;

	sv.lst = mlx->splist;
	while (sv.lst)
	{
		sv.a = sv.lst->a - mlx->set->rot_hor;
		if (mlx->set->rot_hor > _3PI2)
			sv.a += _2PI;
		if (sv.a > _3PI2)
			sv.a -= _2PI;
		sv.size = (double)mlx->screen.height / (cos(sv.a) * sv.lst->len);
		sv.screenc.x = ((sv.a + (mlx->set->fov / 2) / mlx->set->fov
		) * mlx->screen.width) - (sv.size / 2);
		sv.end.x = (((sv.screenc.x + sv.size) < mlx->screen.width) ?
		(sv.screenc.x + sv.size) : mlx->screen.width);
		sv.d.x = -sv.screenc.x * (sv.screenc.x < 0);
		sv.screenc.x += sv.d.x;
		sv.textc.x = (sv.d.x / sv.size) * mlx->sprite.width;
		sv.rap.x = (1 / sv.size) * mlx->sprite.width;
		sv.rap.y = (1 / sv.size) * mlx->sprite.height;
		drawCurrentSprite(mlx, &sv);
		sv.lst = sv.lst->next;
	}
	freesplist(&mlx->splist);
	return (0);
}
