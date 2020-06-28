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

typedef struct	s_mlxcu
{
	t_mlxvar	mlx;
	t_coord		pos;
	int			size;
	t_cupos		old;
}				t_mlxcu;


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
	double	pasX = A.X - B.X;
	double	pasY = A.Y - B.Y;
	int		startX;
	int		startY;
	int		j = -1;
	int		i;

	if ((pasX < 0) && (pasY > 0))
	{
		startX = A.X;
		startY = B.Y;
	}
	else if ((pasX >= 0) && (pasY >= 0))
	{
		startX = B.X;
		startY = B.Y;
	}
	else if ((pasX <= 0) && (pasY <= 0))
	{
		startX = A.X;
		startY = A.Y;
	}
	else if ((pasX > 0) && (pasY < 0))
	{
		startX = B.X;
		startY = A.Y;
	}
	if (pasX)
	{
		if (pasY)
		{
			pasY = pasY / pasX;
			pasX = 1.0;
		}
		else
			pasX = 0.0;
	}
	else
		pasY = 0.0;
	printf("pasX %f pasy %f\n", pasX, pasY);
	while (++j <= ABS(A.Y - B.Y))
	{
		i = -1;
		while (++i <= ABS(A.X - B.X))
			if (pasX || pasY || ((int)(i * pasY + (A.Y - startY)) == j))
			{
				printf("hello\n");
				mlx_pixel_put(mlx.key, mlx.win, i + startX, j + startY, 255);
			}
	}
}

void	erline(t_mlxvar mlx, t_coord A, t_coord B, t_coord newA, t_coord newB)
{
	double	pasX = A.X - B.X;
	double	pasY = A.Y - B.Y;
	int		startX;
	int		startY;
	int		j = -1;
	int		i;

	if ((pasX < 0) && (pasY > 0))
	{
		startX = A.X;
		startY = B.Y;
	}
	else if ((pasX >= 0) && (pasY >= 0))
	{
		startX = B.X;
		startY = B.Y;
	}
	else if ((pasX <= 0) && (pasY <= 0))
	{
		startX = A.X;
		startY = A.Y;
	}
	else if ((pasX > 0) && (pasY < 0))
	{
		startX = B.X;
		startY = A.Y;
	}
	if (pasX)
	{
		pasY /= pasX;
		pasX = 1;
	}
	while (++j <= ABS(A.Y - B.Y))
	{
		i = -1;
		while (++i <= ABS(A.X - B.X) && !((A.X == newA.X) && (A.Y == newA.Y) && (B.X == newB.X) && (B.Y == newB.Y)))
			if (!pasX || !pasY || ((int)(i * pasY + (A.Y - startY)) == j))
				mlx_pixel_put(mlx.key, mlx.win, i + startX, j + startY, 0);
	}
}

void	erasecu(t_cupos cubPos, t_cupos newCuPos, t_mlxvar mlx)
{
	erline(mlx, cubPos.A, cubPos.B, newCuPos.A, newCuPos.B);
	erline(mlx, cubPos.B, cubPos.C, newCuPos.B, newCuPos.C);
	erline(mlx, cubPos.C, cubPos.D, newCuPos.C, newCuPos.D);
	erline(mlx, cubPos.D, cubPos.A, newCuPos.D, newCuPos.A);
	erline(mlx, cubPos.E, cubPos.F, newCuPos.E, newCuPos.F);
	erline(mlx, cubPos.F, cubPos.G, newCuPos.F, newCuPos.G);
	erline(mlx, cubPos.G, cubPos.H, newCuPos.G, newCuPos.H);
	erline(mlx, cubPos.H, cubPos.E, newCuPos.H, newCuPos.E);
	erline(mlx, cubPos.A, cubPos.E, newCuPos.A, newCuPos.E);
	erline(mlx, cubPos.B, cubPos.F, newCuPos.B, newCuPos.F);
	erline(mlx, cubPos.C, cubPos.G, newCuPos.C, newCuPos.G);
	erline(mlx, cubPos.D, cubPos.H, newCuPos.D, newCuPos.H);
}

int		putcu(t_mlxcu *cube)
{
	t_cupos		cubPos;
	static int init = 0;

	init_cubpos(cube, &cubPos);
	if (init)
		erasecu(cube->old, cubPos, cube->mlx);
	putline(cube->mlx, cubPos.A, cubPos.B);
	putline(cube->mlx, cubPos.B, cubPos.C);
	putline(cube->mlx, cubPos.C, cubPos.D);
	putline(cube->mlx, cubPos.D, cubPos.A);
	putline(cube->mlx, cubPos.E, cubPos.F);
	putline(cube->mlx, cubPos.F, cubPos.G);
	putline(cube->mlx, cubPos.G, cubPos.H);
	putline(cube->mlx, cubPos.H, cubPos.E);
	putline(cube->mlx, cubPos.A, cubPos.E);
	putline(cube->mlx, cubPos.B, cubPos.F);
	putline(cube->mlx, cubPos.C, cubPos.G);
	putline(cube->mlx, cubPos.D, cubPos.H);
	cube->old = cubPos;
	init = 1;
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
		degrees++;
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
