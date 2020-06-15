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

# define H_NOARG 0
# define H_HELP 1

# define ER_WPATH 0
# define ER_OPENF 1

# define NONE 0
# define SAVE 1
# define BONUS 2

# define ANY 0
# define BEG 1
# define END 2
# define ALL 3

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <mlx.h>
# include <mlx_int.h>

typedef enum	e_bool
{
	false,
	true
}				t_bool;

typedef enum	e_std
{
	_stdin,
	_stdout,
	_stderr
}				t_std;

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

char	*ft_strstr(char *haystack, char *needle);

char	*search_str(char *needle, char **ar, int size, int how);

int		ft_strcmp(char *s1, char *s2);

int		ft_fputc(int fd, char c);
int		ft_fputs(int fd, char *s);
int		ft_putchar(char c);
int		ft_putstr(char *s);

int		error_wrong_file(int errnum);

int		help(void);

int		cub3D(t_set set, int flags);

int		get_set(int fd, t_set *set);

#endif
