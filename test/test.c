#define _USE_MATH_DEFINES
#include "mlx.h"
#include "mlx_int.h"
#include <X11/Xlib.h>
#include <stdio.h>
#include <math.h>
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif
#define degToRad(angleDegrees) ((angleDegrees) * M_PI / 180.0)

#define KEY_LEFT
#define KEY_RIGHT
#define KEY_UP
#define KEY_DOWN


typedef struct	s_vect
{
	double		x;
	double		y;
	double		z;
}				t_vect;

typedef struct	s_axis
{
	t_vect		x;
	t_vect		y;
	t_vect		z;
}				t_axis;

typedef struct	s_mlxvar
{
	void	*key;
	void	*win;
	int		winX;
	int		winY;
	t_axis	nrm;
	t_axis	prev;
}				t_mlxvar;

double	ft_abs(double nb)
{
	return ((nb < 0.0) ? -nb : nb);
}

void	init_nrm(t_axis *nrm)
{
	nrm->x.x = 1;
	nrm->x.y = 0;
	nrm->x.z = 0;

	nrm->y.x = 0;
	nrm->y.y = 1;
	nrm->y.z = 0;

	nrm->z.x = 0;
	nrm->z.y = 0;
	nrm->z.z = 1;
}

void	print_line(t_mlxvar *mlx, double posX, double posY, unsigned int size, t_vect vect, int color)
{
	int		ix;
	int 	iy;

	ix = 0;
	iy = 0;
	while ((ft_abs(ix) <= ft_abs(size * vect.x)
	|| ft_abs(iy) <= ft_abs(size * vect.y))
	&& (posX + ix < mlx.winX) && (posY + iy < mlx.winY))
	{
		mlx_pixel_put(mlx->key, mlx->win, posX + ix, posY + iy, color);
		ix += vect.x;
		iy += vect.y;
	}
}

int		print_nrm(t_mlxvar *mlx)
{
	static int	init;

	if (init)
		erase_nrm(mlx->prev);
	print_line(mlx, mlx->winX / 2, mlx->winY / 2, 10, mlx->nrm.x, 0xFF0000);
	print_line(mlx, mlx->winX / 2, mlx->winY / 2, 10, mlx->nrm.y, 0x00FF00);
	print_line(mlx, mlx->winX / 2, mlx->winY / 2, 10, mlx->nrm.z, 0x0000FF);
	return (0);
}

int		rotate(int key, t_axis *nrm)
{
	if (key == KEY_LEFT)
		rotate_hor(nrm, -1);
	if (key == KEY_RIGHT)
		rotate_hor(nrm, 1);
	if (key == KEY_UP)
		rotate_vert(nrm, -1);
	if (key == KEY_DOWN)
		rotate_vert(nrm, 1);
	nrm->y.x = nrm->z.y * nrm->x.z - nrm->z.z * nrm->x.y;
	nrm->y.y = nrm->z.z * nrm->x.x - nrm->z.x * nrm->x.z;
	nrm->y.z = nrm->z.x * nrm->x.y - nrm->z.y * nrm->x.x;
	return (0);
}

int		main(void)
{
	t_mlxvar	mlx;

	mlx.winX = 800;
	mlx.winY = 600;
	mlx.key = mlx_init();
	mlx.win = mlx_new_window(mlx.key, winX, winY, "Test");
	init_nrm(&mlx.nrm);
	mlx_expose_hook(mlx.win, &print_nrm, &mlx);
	mlx_hook(mlx.win, KeyPress, KeyPressMask, &rotate, &mlx.nrm);
	mlx_loop(mlx.key);
	return (0);
}