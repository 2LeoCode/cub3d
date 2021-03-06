/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 16:01:49 by lsuardi           #+#    #+#             */
/*   Updated: 2020/12/04 18:31:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define H_NOARG 0
# define H_HELP 1

# define ER_DEFLT 50
# define ER_WPATH 1
# define ER_OPENF 2
# define ER_MISSI 3
# define ER_READF 4
# define ER_DOUBL 5
# define ER_WRRES 6
# define ER_UNKNW 7
# define ER_WRRGB 8
# define ER_WRMAP 9
# define ER_NOSPW 10
# define ER_WPIMG 11
# define ER_COUNT 12
# define ER_DBLSP 13
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
# define MAP_CHRST "012NWSE"

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

# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define BUFFER_GET_FILE 32

# define _USE_MATH_DEFINES

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

# define CUBSIZ 10

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define _2PI 6.28318530718
# define PI2 1.57079632679
# define _3PI2 4.71238898038

typedef struct			s_bfh
{
	unsigned char		bitmap_type[2];
	int					file_size;
	short				reserved1;
	short				reserved2;
	unsigned int		offset_bits;
}						t_bfh;

typedef struct			s_bih
{
	unsigned int		size_header;
	unsigned int		width;
	unsigned int		height;
	short				planes;
	short				bit_count;
	unsigned int		compression;
	unsigned int		image_size;
	unsigned int		ppm_x;
	unsigned int		ppm_y;
	unsigned int		clr_used;
	unsigned int		clr_important;
}						t_bih;

typedef struct			s_splist
{
	double				x;
	double				y;
	double				len;
	double				a;
	struct s_splist		*next;
}						t_splist;

typedef struct			s_point
{
	double				x;
	double				y;
}						t_point;

typedef enum			e_bool
{
	false,
	true
}						t_bool;

typedef enum			e_std
{
	_stdin,
	_stdout,
	_stderr
}						t_std;

typedef struct			s_rgb
{
	int					r;
	int					g;
	int					b;
}						t_rgb;

typedef struct			s_coord
{
	int					x;
	int					y;
}						t_coord;

typedef struct			s_line
{
	char				*line;
	struct s_line		*next;
}						t_line;

typedef struct			s_set
{
	int					x;
	int					y;
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	char				*s;
	int					f;
	int					c;
	double				fov;
	t_coord				spawn;
	double				rot_vert;
	double				rot_hor;
	char				**map;
	int					mapx;
	int					mapy;
}						t_set;

typedef struct			s_mlximg
{
	int					bpp;
	int					line_size;
	int					endian;
	void				*img;
	int					*img_data;
	int					width;
	int					height;
}						t_mlximg;

typedef struct			s_ray
{
	double				siz;
	double				rot;
	t_mlximg			*texture;
	int					col_pos;
}						t_ray;

typedef struct			s_mlxvar
{
	void				*id;
	void				*win;
	t_set				*set;
	double				posx;
	double				posy;
	t_mlximg			screen;
	t_mlximg			walln;
	t_mlximg			walle;
	t_mlximg			walls;
	t_mlximg			wallw;
	t_mlximg			sprite;
	t_ray				*rays;
	int					lastkey;
	int					iskeypressed;
	t_splist			*splist;
}						t_mlxvar;

typedef struct			s_updatevar
{
	int					i;
	int					j;
	double				k;
	double				size;
	int					l;
}						t_updatevar;

typedef struct			s_spritevar
{
	double				size;
	double				a;
	t_coord				end;
	t_coord				d;
	t_splist			*lst;
	t_coord				screenc;
	t_point				textc;
	t_point				rap;
}						t_spritevar;

typedef struct			s_dvar
{
	double				x;
	double				y;
	double				r;
}						t_dvar;

typedef struct			s_getsetvar
{
	int					i;
	t_bool				check[NB_PARAMS];
	char				*line;
	t_bool				total;
}						t_getsetvar;

typedef struct			s_rayvar
{
	int					i;
	double				r;
	double				a;
	double				t;
	t_point				b;
	t_point				c;
	t_point				length;
	t_point				d;
}						t_rayvar;

char					*ft_strstr(char *haystack, char *needle);

char					*search_str(char *needle, char **ar, int size, int how);

int						ft_memcmp(void *m1, void *m2, size_t n);
int						ft_strcmp(char *s1, char *s2);

int						ft_fputc(int fd, char c);
int						ft_fputs(int fd, char *s);
int						ft_putchar(char c);
int						ft_putstr(char *s);

t_bool					print_wrong(char *map_path, int ac, char **av);
int						error_wrong_file(char *path);
int						error_wrong_map(int errnum);
char					*error_s(int errnum);

void					clear_set(t_set *set);
void					clear_paths(t_set *set);
int						clear_mlx(t_mlxvar *mlx);
int						clear_mlx_err(t_mlxvar *mlx);

int						help(int show_msg);
t_bool					arg_help(int ac, char **av);

int						cub3d(t_set *set, int flags);

void					fill_chunk_end(char *chunk, int startx, int starty);
t_bool					are_chunk_lines_null(char **lines);
int						get_one_chunk(t_set *set, t_line **map);
int						get_chunks(int fd, t_set *set);
int						get_path(char *line, t_set *set, t_bool *check);
int						get_rgb(char *line, t_set *set, t_bool *check);
int						get_set(int fd, t_set *set);
int						get_res(char *line, t_set *set, t_bool *check);
int						getsettings(int ac, char **av, t_set *settings);
void					init_set(t_set *set);
void					get_line(char **map, int index, char *line, int size);
int						get_map_x(t_line *lst);
int						get_map_y(t_line *lst);
int						get_map_from_list(t_line **lst, t_set *set);
t_bool					is_map_full_wall(char *line);

size_t					ft_strlen(char *s);

t_bool					str_isspace(char *s);
t_bool					str_isdigit(char *s);

t_bool					ft_isdigit(int c);
t_bool					ft_isspace(int c);
t_bool					ft_isalpha(int c);

char					*ft_strchr(char *s, int c);

int						ft_atoi(char *s);

char					*get_file(char *path);
int						file_size(char *path);

char					*ft_strdup(char *s);

t_line					*lst_line_new(char *content);
int						lst_line_addback(t_line **lst, char *content);
t_line					*lst_line_last(t_line *lst);
void					lst_line_clr(t_line **lst);

void					get_next_line_end(int fd, char **line);

t_bool					is_map_wall(char *line);
int						check_map(t_set *set);
int						get_map(int fd, t_set *set);

int						update_screen(t_mlxvar *mlxvar);
int						update_rays(t_mlxvar *mlxvar);
void					initrayvert(t_rayvar *ur, t_mlxvar *mlx);
void					initrayhor(t_rayvar *ur, t_mlxvar *mlx);

void					*ft_memcpy(void *d, void *s, size_t n);
void					*ft_bzero(void *m, size_t n);

void					exit_save(t_mlxvar *mlx);
int						save_screen(t_mlximg *screen);
t_bfh					createbitmapfileheader(t_mlximg *screen);
t_bih					createbitmapinfoheader(t_mlximg *screen);
unsigned char			*getchararray(t_mlximg *screen);

int						init_textures(t_mlxvar *mlxvar);
t_mlxvar				initmlx(t_set *set, int flags, t_bool *save);

void					checkkeys(t_mlxvar *mlxvar, int key, t_dvar d);
int						keyispressed(int key, t_mlxvar *mlxvar);
int						keyisreleased(int key, t_mlxvar *mlxvar);
int						keycond1(t_mlxvar *mlxvar, int key, t_dvar d);
int						keycond2(t_mlxvar *mlxvar, int key, t_dvar d);

int						draw_sprites(t_mlxvar *mlx);
void					splistswap(t_splist *a, t_splist *b);
void					sortsplist(t_splist **lst);
void					freesplist(t_splist **lst);
int						freespfail(t_splist **lst);
t_splist				*splistaddfront(t_mlxvar *mlx, t_splist *lst,
double x, double y);

#endif
