/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 16:01:49 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/12 21:05:16 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <mlx.h>
# include <mlx_int.h>

typedef struct	s_rgb
{
	int			R;
	int 		G;
	int			B;
}				t_rgb;

typedef struct	s_set
{
	int			X;
	int			Y;
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		*S;
	t_rgb		F;
	t_rgb		C;
}				t_set;

#endif
