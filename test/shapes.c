#define _USE_MATH_DEFINES
#include "mlx.h"
#include "mlx_int.h"
#include <X11/Xlib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif
#define degToRad(angleDegrees) ((angleDegrees) * M_PI / 180.0)

#define KEY_LEFT
#define KEY_RIGHT
#define KEY_UP
#define KEY_DOWN

typedef struct			s_coord
{
	double				x;
	double				y;
}						t_coord;

typedef struct			s_coord_3
{
	double				x;
	double				y;
	double				z;
}						t_coord_3;

typedef struct			s_screen_coord
{
	t_coord				x;
	t_coord				y;
	t_coord				z;
}						t_screen_coord;

typedef struct			s_triangle
{
	t_coord_3			A;
	t_coord_3			B;
	t_coord_3			C;
}						t_triangle;

typedef struct			s_screen_triangle
{
	t_screen_coord		x;
	t_screen_coord		y;
	t_screen_coord		z;
}						t_screen_triangle;

typedef struct			s_quad
{
	t_triangle			top;
	t_triangle			bot;

	t_screen_triangle	stop;
	t_screen_triangle	sbot;

}						t_quad;

typedef struct			s_cube
{
	t_quad				no;
	t_quad				ea;
	t_quad				so;
	t_quad				we;
	t_quad				top;
	t_quad				bot;
}						t_cube;

typedef struct	s_rgb
{
	int		R;
	int		G;
	int		B;
}				t_rgb;

typedef struct	s_mlxvar
{
	void				*id;
	void				*win;

	char				**map;
	int					mapX;
	int					mapY;
	int					winX;
	int					winY;
	double				px;
	double				py;
	double				rot;
	int					FOV;
	t_rgb				color_2d_wall;
	t_rgb				color_2d_floor;
	t_rgb				color_2d_player;
	int					box_size_x;
	int					box_size_y;
}				t_mlxvar;

size_t			ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

unsigned long	create_color_int(t_rgb color)
{
	return (((color.R & 0xff) << 16) + ((color.G & 0xff) << 8)
	+ (color.B & 0xff));
}

int				ft_round(double nb)
{
	int 	strict = (int)nb;

	if ((nb - (double)strict) > 0.5)
		return (strict + 1);
	return (strict);
}

void			draw_box(t_mlxvar *mlx_var, int x, int y, unsigned long color)
{
	int		i;
	int		j;

	j = -1;
	while (++j < mlx_var->box_size_y)
	{
		i = -1;
		while (++i < mlx_var->box_size_x)
			if (i == 0 || j == 0 || i == (mlx_var->box_size_x - 1) || j == (mlx_var->box_size_y - 1))
				mlx_pixel_put(mlx_var->id, mlx_var->win, x + i, y + j, 0);
			else
				mlx_pixel_put(mlx_var->id, mlx_var->win, x + i, y + j, (int)color);
	}
}

void			draw2d_player(t_mlxvar *mlx_var)
{
	int		i;
	int		j;
	unsigned long color;

	color = create_color_int(mlx_var->color_2d_player);
	j = -1;
	printf("in2\n");
	while (++j < 5)
	{
		i = -1;
		while (++i < 5)
			mlx_pixel_put(mlx_var->id, mlx_var->win, (mlx_var->px * mlx_var->box_size_x) - 2 + i, (mlx_var->py * mlx_var->box_size_y) - 2 + j, (int)color);
	}
	printf("out2\n");
}

int				draw2d_map(t_mlxvar *mlx_var)
{
	int		i;
	int		j;

	mlx_var->box_size_x = ft_round(mlx_var->winX / (double)mlx_var->mapX);
	mlx_var->box_size_y = ft_round(mlx_var->winY / (double)mlx_var->mapY);
	j = -1;
	printf ("in1\n");
	while (++j < (int)mlx_var->mapY)
	{
		i = -1;
		while (++i < (int)mlx_var->mapX)
			if (mlx_var->map[j][i] == '1')
			{
				draw_box(mlx_var, i * mlx_var->box_size_x, j * mlx_var->box_size_y, create_color_int(mlx_var->color_2d_wall));
			}
			else if (mlx_var->map[j][i] == '0')
			{
				draw_box(mlx_var, i * mlx_var->box_size_x, j * mlx_var->box_size_y, create_color_int(mlx_var->color_2d_floor));
			}
	}
	printf ("out1\n");
	draw2d_player(mlx_var);
	return (0);
}

char			*ft_strcpy(char *d, char *s)
{
	int		i;

	i = -1;
	while (s[++i])
		d[i] = s[i];
	d[i] = 0;
	return (d);
}

char			*ft_strdup(char *s)
{
	char	*n;

	if (!(n = (char*)malloc(sizeof(char) * ft_strlen(s))))
		return (NULL);
	return (ft_strcpy(n, s));
}

int				process_key(int key, t_mlxvar *mlx_var)
{
	printf("%d\n", key);
	return (0);
}

int				main(void)
{
	t_mlxvar	mlx_var;
	int			i;

	mlx_var.id = mlx_init();

	mlx_var.winX = 500;
	mlx_var.winY = 500;

	mlx_var.color_2d_floor.R = 180;
	mlx_var.color_2d_floor.G = 180;
	mlx_var.color_2d_floor.B = 180;

	mlx_var.color_2d_wall.R = 255;
	mlx_var.color_2d_wall.G = 255;
	mlx_var.color_2d_wall.B = 255;

	mlx_var.color_2d_player.R = 255;
	mlx_var.color_2d_player.G = 255;
	mlx_var.color_2d_player.B = 0;
	
	mlx_var.mapX = 8;
	mlx_var.mapY = 8;

	mlx_var.px = 2.5;
	mlx_var.py = 2.5;
	mlx_var.rot = 0;

	mlx_var.map = (char**)malloc(sizeof(char*) * (mlx_var.mapX + 1));
	i = -1;
	mlx_var.map[0] = ft_strdup("11111111");
	mlx_var.map[1] = ft_strdup("10000101");
	mlx_var.map[2] = ft_strdup("11000101");
	mlx_var.map[3] = ft_strdup("10000001");
	mlx_var.map[4] = ft_strdup("10011001");
	mlx_var.map[5] = ft_strdup("10010001");
	mlx_var.map[6] = ft_strdup("10010011");
	mlx_var.map[7] = ft_strdup("11111111");
	mlx_var.map[8] = NULL;
	mlx_var.win = mlx_new_window(mlx_var.id, mlx_var.winX * 2, mlx_var.winY, "Ray-casting");
	draw2d_map(&mlx_var);
	mlx_loop_hook(mlx_var.win, &draw2d_map, &mlx_var);
	mlx_hook(mlx_var.win, KeyPress, KeyPressMask, &process_key, &mlx_var);
	mlx_loop(mlx_var.id);
	return (0);
}
