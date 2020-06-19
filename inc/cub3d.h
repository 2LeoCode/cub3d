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

# define ER_DEFLT 0
# define ER_WPATH 1
# define ER_OPENF 2
# define ER_MISSI 3
# define ER_READF 4
# define ER_DOUBL 5
# define ER_WRRES 6
# define ER_UNKNW 7
# define ER_WRRGB 8
# define ER_WRMAP 9
# define ER_COUNT 10
# define WARNING 20

# define NONE 0
# define SAVE 1
# define BONUS 2

# define ANY 0
# define BEG 1
# define END 2
# define ALL 3

# define CHUNK_SIZE 4

# define ANY_START -1
# define MAP_CHRST "012NOSE"

# define NB_PARAMS 9
# define C_X 0
# define C_Y 1
# define C_NO 2
# define C_SO 3
# define C_WE 4
# define C_EA 5
# define C_F 6
# define C_C 7
# define C_S 8

# define BUFFER_GET_FILE 32

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <errno.h>
# include <get_next_line.h>
# include <mlx.h>
# include <mlx_int.h>

typedef enum		e_bool
{
	false,
	true
}					t_bool;

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

typedef struct		s_coord
{
	int				X;
	int				Y;
}					t_coord;

typedef struct		s_line
{
	char			*line;
	struct s_line	*next;
}					t_line;
typedef struct		s_chunk
{
	char			chunk[CHUNK_SIZE * CHUNK_SIZE + 1];
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

t_bool				print_wrong(char *map_path, int ac, char **av);
int					error_wrong_file(char *path);
int					error_wrong_map(int errnum);
char				*error_s(int errnum);

void				clear_set(t_set *set, t_bool *active);

int					help(int show_msg);

int					cub3D(t_set set, int flags);


void				fill_chunk_end(char *chunk, int startX, int startY);
t_bool				are_chunk_lines_null(char **lines);
int					get_one_chunk(t_set *set, t_line **map);
int					get_chunks(int fd, t_set *set);
int					get_path(char *line, t_set *set, t_bool *check);
int					get_set(int fd, t_set *set);

size_t				ft_strlen(char *s);

t_bool				str_isspace(char *s);

t_bool				ft_isdigit(int c);
t_bool				ft_isspace(int c);
t_bool				ft_isalpha(int c);

char				*ft_strchr(char *s, int c);

int					ft_atoi(char *s);

char				*get_file(char *path);
int					file_size(char *path);

char				*ft_strdup(char *s);

t_line				*lst_line_new(char *content);
int					lst_line_addback(t_line **lst, char *content);
t_line				*lst_line_last(t_line *lst);
void				lst_line_clr(t_line **lst);

void				lst_chunk_clr(t_chunk **lst);
t_chunk				*lst_chunk_last(t_chunk *lst);
t_chunk				*lst_chunk_new(int x, int y);

void				get_next_line_end(int fd, char **line);

/*
** test
*/

void				display_chunks(t_chunk *chunk);
#endif
