#define _USE_MATH_DEFINES
#include "mlx.h"
#include "mlx_int.h"
#include <X11/Xlib.h>
#include <stdio.h>
#include <math.h>
#define ABS(X) ((X < 0) ? -X : X)
#define SQ(X) (X * X)
#define degToRad(angleDegrees) ((angleDegrees) * M_PI / 180.0)

typedef struct	s_coord
{
	double		X;
	double		Y;
}				t_coord;

typedef struct	s_ccoord
{
	double		X;
	double		Y;
	double		Z;
}				t_ccoord;

typedef struct	s_mlxvar
{
	void		*key;
	void		*win;
	t_ccoord	nrm_x;
	t_ccoord	nrm_y;
	t_ccoord	nrm_z;
	t_ccoord	nrm_x0;
	t_ccoord	nrm_y0;
	t_ccoord	nrm_z0;
	t_coord		res;
}				t_mlxvar;

typedef struct	s_mlxcu
{
	t_mlxvar	mlx;
	t_coord		pos;
	int			size;
}				t_mlxcu;

typedef struct	s_cupos
{
	t_coord A;
	t_coord B;
	t_coord C;
	t_coord D;
	t_coord E;
	t_coord F;
	t_coord G;
	t_coord H;
}				t_cupos;

void	init_nrm(t_mlxvar *mlx)
{
	mlx->nrm_x0.X = 1;
	mlx->nrm_x0.Y = 0;
	mlx->nrm_x0.Z = 0;
	mlx->nrm_y0.X = 0;
	mlx->nrm_y0.Y = 1;
	mlx->nrm_y0.Z = 0;
	mlx->nrm_z0.X = 0;
	mlx->nrm_z0.Y = 0;
	mlx->nrm_z0.Z = 1;
	mlx->nrm_x = mlx->nrm_x0;
	mlx->nrm_y = mlx->nrm_y0;
	mlx->nrm_z = mlx->nrm_z0;
}

t_mlxcu	init_cu(int size, int posX, int posY, t_mlxvar mlx)
{
	t_mlxcu	tmp;

	tmp.mlx = mlx;
	tmp.size = size;
	tmp.pos.X = posX;
	tmp.pos.Y = posY;
	return (tmp);
}

void	init_cubpos(t_mlxcu *cube, t_cupos *pos)
{
	pos->A.X = cube->pos.X;
	pos->A.Y = cube->pos.Y;
	pos->B.X = pos->A.X + (cube->size * cube->mlx.nrm_x.X);
	pos->B.Y = pos->A.Y + (cube->size * cube->mlx.nrm_x.Y);
	pos->C.X = pos->B.X + (cube->size * cube->mlx.nrm_y.X);
	pos->C.Y = pos->B.Y + (cube->size * cube->mlx.nrm_y.Y);
	pos->D.X = pos->C.X - (cube->size * cube->mlx.nrm_x.X);
	pos->D.Y = pos->C.Y - (cube->size * cube->mlx.nrm_x.Y);
	pos->E.X = cube->pos.X + (cube->size * cube->mlx.nrm_z.X);
	pos->E.Y = cube->pos.Y + (cube->size * cube->mlx.nrm_z.Y);
	pos->F.X = pos->E.X + (cube->size * cube->mlx.nrm_x.X);
	pos->F.Y = pos->E.Y + (cube->size * cube->mlx.nrm_x.Y);
	pos->G.X = pos->F.X + (cube->size * cube->mlx.nrm_y.X);
	pos->G.Y = pos->F.Y + (cube->size * cube->mlx.nrm_y.Y);
	pos->H.X = pos->G.X - (cube->size * cube->mlx.nrm_x.X);
	pos->H.Y = pos->G.Y - (cube->size * cube->mlx.nrm_x.Y);
}

void	putline(t_mlxvar mlx, t_coord A, t_coord B)
{
	double	pasX = B.X - A.X;
	double	pasY = B.Y - A.Y;

	while ((ABS(pasX) > 1) || (ABS(pasY) > 1))
	{
		pasX /= 2;
		pasY /= 2;
	}
	while (((int)A.X - (int)B.X) || ((int)A.Y - (int)B.Y))
	{
		mlx_pixel_put(mlx.key, mlx.win, A.X, A.Y, 255);
		A.X += pasX;
		A.Y += pasY;
		printf("%f %f %f %f\n", A.X, A.Y, B.X, B.Y);
	}
}

int		is_in_line(int x, int y, t_coord A, t_coord B)
{
	if (!(B.X - A.X) && !(B.Y - A.Y))
		return ((x == B.X) && (y == B.Y));
	else if (!(B.X - A.X) || !(B.Y - A.Y))
		return (0);
	return ((int)((B.X - A.X) * (y - A.Y)) == (int)((x - A.X) * (B.Y - A.Y)));
}

int		is_in_lines(int x, int y, t_cupos cube)
{
	return (is_in_line(x, y, cube.A, cube.B)
	|| is_in_line(x, y, cube.B, cube.C)
	|| is_in_line(x, y, cube.C, cube.D)
	|| is_in_line(x, y, cube.D, cube.A)
	|| is_in_line(x, y, cube.A, cube.E)
	|| is_in_line(x, y, cube.E, cube.F)
	|| is_in_line(x, y, cube.F, cube.G)
	|| is_in_line(x, y, cube.G, cube.H)
	|| is_in_line(x, y, cube.H, cube.E));
}

int		putcu(t_mlxcu *cube)
{
	t_cupos		cubPos;
	int i;
	int j = -1;

	init_cubpos(cube, &cubPos);
	while (++j < cube->mlx.res.Y)
	{
		i = -1;
		while (++i < cube->mlx.res.X)
		{
			if (is_in_lines(i, j, cubPos))
				mlx_pixel_put(cube->mlx.key, cube->mlx.win, i, j, 255);
			else
				mlx_pixel_put(cube->mlx.key, cube->mlx.win, i, j, 0);
		}
	}
	return (0);
}

void	mlx_clear(t_mlxvar mlx)
{
	int i;
	int j = -1;

	while (++j < mlx.res.Y)
	{
		i = -1;
		while (++i < mlx.res.X)
			mlx_pixel_put(mlx.key, mlx.win, i, j, 0);
	}
}

int		rotate_y(int key, t_mlxcu *cube)
{
	static int degrees = 1;

	if (key == 65361)
	{
		cube->mlx.nrm_z.X = sqrt(SQ(cube->mlx.nrm_z0.Z) + SQ(cube->mlx.nrm_z0.X)) * sin(degToRad(degrees));
		cube->mlx.nrm_z.Z = sqrt(SQ(cube->mlx.nrm_z0.Z) + SQ(cube->mlx.nrm_z0.X)) * cos(degToRad(degrees));
		cube->mlx.nrm_x.X = sqrt(SQ(cube->mlx.nrm_x0.Z) + SQ(cube->mlx.nrm_x0.X)) * cos(degToRad(degrees));
		cube->mlx.nrm_x.Z = sqrt(SQ(cube->mlx.nrm_x0.Z) + SQ(cube->mlx.nrm_x0.X)) * sin(degToRad(degrees));
		degrees += 1;
		printf("x %f %f\nz %f %f\n", cube->mlx.nrm_x.X, cube->mlx.nrm_x.Z, cube->mlx.nrm_z.X, cube->mlx.nrm_z.Z);
		putcu(cube);
	}
	return (0);
}

int		main(void)
{
	t_mlxvar	mlx;
	t_mlxcu		cube;
	
	mlx.key = mlx_init();
	mlx.res.X = 800;
	mlx.res.Y = 600;
	mlx.win = mlx_new_window(mlx.key, mlx.res.X, mlx.res.Y, "square");
	init_nrm(&mlx);
	cube = init_cu(50, 100, 100, mlx);
	putcu(&cube);
	mlx_hook(mlx.win, KeyPress, KeyPressMask, &rotate_y, &cube);
	mlx_loop(mlx.key);
	return (0);
}
