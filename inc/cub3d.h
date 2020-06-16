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
# define ER_MISSI 2
# define ER_READF 3
# define ER_DOUBL 4
# define ER_WRRES 5

# define NONE 0
# define SAVE 1
# define BONUS 2

# define ANY 0
# define BEG 1
# define END 2
# define ALL 3

# define CHUNK_SIZE 4

# define NB_PARAMS 8
# define C_X 0
# define C_Y 1
# define C_NO 2
# define C_SO 3
# define C_WE 4
# define C_EA 5
# define C_F 6
# define C_C 7

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <get_next_line.h>
# include <mlx.h>
# include <mlx_int.h>

typedef enum	e_bool
{
	false,
	true
}				t_bool;

typedef enum		e_std
{
	_stdin,
	_stdout,
	_stderr
}					t_std;

typedef struct		s_rgb
{
	int				R;
	int 			G;
	int				B;
}					t_rgb;

typedef struct		s_chunk
{
	char			chunk[(CHUNK_SIZE * CHUNK_SIZE) + 1];
	int				x;
	int				y;
	struct s_chunk	*next;
}					t_chunk;
typedef struct		s_set
{
	int				X;
	int				Y;
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;
	char			*S;
	t_rgb			F;
	t_rgb			C;
	t_chunk			*chunks;
}					t_set;

char				*ft_strstr(char *haystack, char *needle);

char				*search_str(char *needle, char **ar, int size, int how);

int					ft_memcmp(void *m1, void *m2, size_t n);
int					ft_strcmp(char *s1, char *s2);

int					ft_fputc(int fd, char c);
int					ft_fputs(int fd, char *s);
int					ft_putchar(char c);
int					ft_putstr(char *s);

int					error_wrong_file(int errnum);

int					help(int show_msg);

int					cub3D(t_set set, int flags);

int					get_set(int fd, t_set *set);

size_t				ft_strlen(char *s);

t_bool				ft_isdigit(int c);
t_bool				ft_isspace(int c);

char				*ft_strchr(char *s, int c)

int					ft_atoi(char *s);
#endif
