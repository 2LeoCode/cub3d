#include "mlx.h"
#include "mlx_int.h"
#include <X11/Xlib.h>
#include <stdio.h>
#define ABS(x) ((x < 0) ? -x : x)

typedef struct		s_vect
{
	double				x[2];
	double				y[2];
	double				z[2];
}					t_vect;

typedef struct		s_mlxvar
{
	void	*key;
	void	*win;
}					t_mlxvar;

void	draw_sqare(t_mlxvar mlx, int x, int y, int size, t_vect nrm)
{
	double	ix = x;
	double	iy = y;

	while ((ABS(ix) < ABS(x + (size * nrm.x[0]))) && (ABS(iy) < ABS(x + (size * nrm.x[1]))))
	{
		mlx_pixel_put(mlx.key, mlx.win, ix, iy, 255);
		ix += (1 / nrm.x[0]);
		iy += (1 / nrm.x[1]);
	}
	ix = x;
	iy = y;
	while ((ABS(ix) < ABS(x + (size * nrm.y[0]))) && (ABS(iy) < ABS(x + (size * nrm.y[1]))))
	{
		mlx_pixel_put(mlx.key, mlx.win, ix, iy, 255);
		ix += (1 / nrm.y[0]);
		iy += (1 / nrm.y[1]);
	}
	ix = x;
	iy = y;
	while ((ABS(ix) < ABS(x + (size * nrm.z[0]))) && (ABS(iy) < ABS(x + (size * nrm.z[1]))))
	{
		mlx_pixel_put(mlx.key, mlx.win, ix, iy, 255);
		ix += (1 / nrm.y[0]);
		iy += (1 / nrm.y[1]);
	}
}

int		main()
{
	t_mlxvar	mlx_var;
	t_vect		nrm;

	nrm.x[0] = 10;
	nrm.x[1] = 0;
	nrm.y[0] = 10;
	nrm.y[1] = 0;
	nrm.z[0] = 5;
	nrm.z[1] = 5;
	mlx_var.key = mlx_init();
	mlx_var.win = mlx_new_window(mlx_var.key, 800, 600, "test");
	draw_square(mlx_var, 400, 300, 5, nrm);
	mlx_loop();
}
