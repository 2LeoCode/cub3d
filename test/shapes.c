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
#define ONE_DEGREE 0.0174533
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

typedef struct	s_rgb
{
	int		R;
	int		G;
	int		B;
}				t_rgb;

typedef struct	s_raylist
{
	double				size;
	double				angle;
	struct s_raylist	*next;
}				t_raylist;

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
	double				FOV;
	double				FOV_vert;
	int					color_2d_wall;
	int					color_2d_floor;
	int					color_2d_player;
	int					color_2d_ray;
	int					color_3d_roof;
	int					color_3d_wallV;
	int					color_3d_wallH;
	int					color_3d_floor;
	int					box_size_x;
	int					box_size_y;
	int					box_size_3d;
	t_raylist			*ray_list;
	double				ray_0;
	int					ray_0_startX;
	int					ray_0_startY;
	int					ray_width;
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

void			draw_player(t_mlxvar *mlx_var)
{
	int i;
	int j;

	int	px = ft_round(mlx_var->px * mlx_var->box_size_x);
	int py = ft_round(mlx_var->py * mlx_var->box_size_y);

	j = py - 3;
	while (++j < py + 3)
	{
		i = px - 3;
		while (++i < px + 3)
			mlx_pixel_put(mlx_var->id, mlx_var->win, i, j, mlx_var->color_2d_player);
	}
}

void			draw_box(t_mlxvar *mlx_var, int x, int y, int color)
{
	int				i;
	int				j;

	j = -1;
	while (++j < mlx_var->box_size_y)
	{
		i = -1;
		while (++i < mlx_var->box_size_x)
			if (i == 0 || j == 0 || i == (mlx_var->box_size_x - 1) || j == (mlx_var->box_size_y - 1))
				mlx_pixel_put(mlx_var->id, mlx_var->win, x + i, y + j, 0);
			else
				mlx_pixel_put(mlx_var->id, mlx_var->win, x + i, y + j, color);
	}
}

double			ft_abs(double nb)
{
	return ((nb < 0) ? -nb : nb);
}

int				condition_bot_right(double aX, double aY, double bX, double bY)
{
	return ((aX < bX) || (aY < bY));
}

int				condition_bot_left(double aX, double aY, double bX, double bY)
{
	return ((aX > bX) || (aY < bY));
}

int				condition_top_left(double aX, double aY, double bX, double bY)
{
	return ((aX > bX) || (aY > bY));
}

int				condition_top_right(double aX, double aY, double bX, double bY)
{
	return ((aX < bX) || (aY > bY));
}

void			lst_clr(t_raylist **lst)
{
	t_raylist *head;

	while (*lst)
	{
		head = (*lst)->next;
		free(*lst);
		*lst = head;
	}
	*lst = NULL;
}

t_raylist		*lstpush(double aX, double aY, double bX, double bY, double angle, t_raylist *cur)
{
	t_raylist	*new;

	if (!(new = malloc(sizeof(t_raylist))))
		return (NULL);
	new->size = sqrt((bX - aX) * (bX - aX) + (bY - aY) * (bY - aY));
	new->angle = angle;
	new->next = cur;
	return (new);
}

void			draw_rays(t_mlxvar *mlx_var)
{
	double		posX;
	double		posY;
	double		i;
	double		dX;
	double		dY;
	double		bX;
	double		bY;

	i = 0;
	lst_clr(&mlx_var->ray_list);
	while (i <= mlx_var->FOV)
	{
		posX = mlx_var->px * (double)mlx_var->box_size_x;
		posY = mlx_var->py * (double)mlx_var->box_size_y;
		bX = posX + cos(mlx_var->rot - mlx_var->FOV / 2 + i) * (double)mlx_var->box_size_x;
		bY = posY + sin(mlx_var->rot - mlx_var->FOV / 2 + i) * (double)mlx_var->box_size_y;

		dX = bX - posX;
		dY = bY - posY;
		while ((ft_abs(dX) > 1) || (ft_abs(dY) > 1))
		{
			dX /= 1.1;
			dY /= 1.1;
		}
		bX = posX;
		bY = posY;
		while (mlx_var->map[(int)(posY / mlx_var->box_size_y)][(int)(posX / mlx_var->box_size_x)] == '0')
		{
			mlx_pixel_put(mlx_var->id, mlx_var->win, (int)posX, (int)posY, mlx_var->color_2d_ray);
			posX += dX;
			posY += dY;
		}
		mlx_var->ray_list = lstpush(bX, bY, posX, posY, -mlx_var->FOV / 2 + i, mlx_var->ray_list);
		i += ONE_DEGREE;
	}
	posX = mlx_var->px * (double)mlx_var->box_size_x;
	posY = mlx_var->py * (double)mlx_var->box_size_y;
	bX = posX + cos(mlx_var->rot) * (double)mlx_var->box_size_x;
	bY = posY + sin(mlx_var->rot) * (double)mlx_var->box_size_y;

	dX = bX - posX;
	dY = bY - posY;
	while ((ft_abs(dX) > 1) || (ft_abs(dY) > 1))
	{
		dX /= 1.1;
		dY /= 1.1;
	}
	bX = posX;
	bY = posY;
	while (mlx_var->map[(int)(posY / mlx_var->box_size_y)][(int)(posX / mlx_var->box_size_x)] == '0')
	{
		mlx_pixel_put(mlx_var->id, mlx_var->win, (int)posX, (int)posY, mlx_var->color_2d_ray);
		posX += dX;
		posY += dY;
	}
	mlx_var->ray_0 = sqrt((bX - posX) * (bX - posX) + (bY - posY) * (bY - posY));
}

void			draw3d_rays(t_mlxvar *mlx_var)
{
	int			pX;
	int			pY;
	int			size;
	int			countX;
	t_raylist	*tmp;

	tmp = mlx_var->ray_list;
	pX = mlx_var->winX * 2;
	while (tmp)
	{
		size = mlx_var->winY / (cos(tmp->angle) * (tmp->size / mlx_var->box_size_x));
		countX = pX - (mlx_var->winX / (mlx_var->FOV * 180 / M_PI));
		while (pX > countX)
		{
			pY = -1;
			while (++pY < (mlx_var->winY / 2) - (size / 2) - 1)
				mlx_pixel_put(mlx_var->id, mlx_var->win, pX, pY, mlx_var->color_3d_roof);
			while (++pY < (mlx_var->winY / 2) + (size / 2) - 1)
				mlx_pixel_put(mlx_var->id, mlx_var->win, pX, pY, mlx_var->color_3d_wallH);
			while (++pY < mlx_var->winY)
				mlx_pixel_put(mlx_var->id, mlx_var->win, pX, pY, mlx_var->color_3d_floor);
			pX--;
		}
		tmp = tmp->next;
	}
}

int				draw2d_map(t_mlxvar *mlx_var)
{
	static double	old_px;
	static double	old_py;
	static double	old_rot;
	int				i;
	int				j;

	mlx_var->box_size_x = ft_round(mlx_var->winX / (double)mlx_var->mapX);
	mlx_var->box_size_y = ft_round(mlx_var->winY / (double)mlx_var->mapY);
	j = -1;
	while (++j < (int)mlx_var->mapY)
		if ((!old_px && !old_py && !old_rot) || old_px != mlx_var->px || old_py != mlx_var->py || old_rot != mlx_var->rot)
		{
			i = -1;
			while (++i < (int)mlx_var->mapX)
				if (mlx_var->map[j][i] == '1')
					draw_box(mlx_var, i * mlx_var->box_size_x, j * mlx_var->box_size_y, mlx_var->color_2d_wall);
				else if (mlx_var->map[j][i] == '0')
					draw_box(mlx_var, i * mlx_var->box_size_x, j * mlx_var->box_size_y, mlx_var->color_2d_floor);
			draw_player(mlx_var); 
			draw_rays(mlx_var);
			draw3d_rays(mlx_var);
		}
	old_px = mlx_var->px;
	old_py = mlx_var->py;
	old_rot = mlx_var->rot;
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
	if (key == 65361) //left
	{
		if (mlx_var->rot < 0)
			mlx_var->rot = 2 * M_PI;
		mlx_var->rot -= ONE_DEGREE * 3;
	}
	if (key == 65363) //right
	{
		if (mlx_var->rot > 2 * M_PI)
			mlx_var->rot = 0;
		mlx_var->rot += ONE_DEGREE * 3;
	}
	if (key == 65362
	&& mlx_var->map[(int)(mlx_var->py + (cos(mlx_var->rot) / mlx_var->box_size_y) * 3)]
	[(int)(mlx_var->px + (sin(mlx_var->rot) / mlx_var->box_size_x) * 3)] == '0') //top
	{
		mlx_var->px += (cos(mlx_var->rot) / mlx_var->box_size_x) * 3;
		mlx_var->py += (sin(mlx_var->rot) / mlx_var->box_size_y) * 3;
	}
	if (key == 65364
	&& mlx_var->map[(int)(mlx_var->py - (cos(mlx_var->rot) / mlx_var->box_size_y) * 3)]
	[(int)(mlx_var->px - (sin(mlx_var->rot) / mlx_var->box_size_x) * 3)] == '0') //bot
	{
		mlx_var->px -= (cos(mlx_var->rot) / mlx_var->box_size_x) * 3;
		mlx_var->py -= (sin(mlx_var->rot) / mlx_var->box_size_x) * 3;
	}
	if (mlx_var->rot > 2 * M_PI)
		mlx_var->rot = mlx_var->rot - 2 * M_PI;
	if (mlx_var->rot < 0)
		mlx_var->rot = 2 * M_PI + mlx_var->rot;
	return (0);
}

int				main(void)
{
	t_mlxvar	mlx_var;
	t_rgb		color_2d_floor;
	t_rgb		color_2d_wall;
	t_rgb		color_2d_player;
	t_rgb		color_2d_ray;
	t_rgb		color_3d_wallH;
	t_rgb		color_3d_wallV;
	t_rgb		color_3d_roof;
	t_rgb		color_3d_floor;

	mlx_var.id = mlx_init();

	mlx_var.winX = 200;
	mlx_var.winY = 200;

	color_2d_floor.R = 180;
	color_2d_floor.G = 180;
	color_2d_floor.B = 180;

	color_2d_wall.R = 255;
	color_2d_wall.G = 255;
	color_2d_wall.B = 255;

	color_2d_ray.R = 255;
	color_2d_ray.G = 0;
	color_2d_ray.B = 0;

	color_2d_player.R = 255;
	color_2d_player.G = 255;
	color_2d_player.B = 0;

	color_3d_floor.R = 150;
	color_3d_floor.G = 150;
	color_3d_floor.B = 150;

	color_3d_roof.R = 50;
	color_3d_roof.G = 50;
	color_3d_roof.B = 50;

	color_3d_wallH.R = 200;
	color_3d_wallH.G = 0;
	color_3d_wallH.B = 0;

	color_3d_wallV.R = 100;
	color_3d_wallV.G = 0;
	color_3d_wallV.B = 0;

	mlx_var.color_2d_floor = (int)create_color_int(color_2d_floor);
	mlx_var.color_2d_wall = (int)create_color_int(color_2d_wall);
	mlx_var.color_2d_player = (int)create_color_int(color_2d_player);
	mlx_var.color_2d_ray = (int)create_color_int(color_2d_ray);
	mlx_var.color_3d_floor = (int)create_color_int(color_3d_floor);
	mlx_var.color_3d_roof = (int)create_color_int(color_3d_roof);
	mlx_var.color_3d_wallH = (int)create_color_int(color_3d_wallH);
	mlx_var.color_3d_wallV = (int)create_color_int(color_3d_wallV);
	mlx_var.mapX = 8;
	mlx_var.mapY = 8;
	mlx_var.ray_list = NULL;

	mlx_var.px = 2.5;
	mlx_var.py = 2.5;
	mlx_var.rot = 0;
	mlx_var.FOV = M_PI / 2;
	mlx_var.FOV_vert = 2 * atan(tan(mlx_var.FOV / 2) * (mlx_var.mapX / mlx_var.mapY));
	mlx_var.ray_width = (int)(mlx_var.winX / (mlx_var.FOV * 180 / M_PI));
	mlx_var.map = (char**)malloc(sizeof(char*) * (mlx_var.mapX + 1));
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
	mlx_loop_hook(mlx_var.id, &draw2d_map, &mlx_var);
	mlx_hook(mlx_var.win, KeyPress, KeyPressMask, &process_key, &mlx_var);
	mlx_loop(mlx_var.id);
	return (0);
}
