#define _USE_MATH_DEFINES
#include "mlx.h"
#include <X11/Xlib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif
#define ONE_DEGREE (M_PI / 180)

#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_UP 65362
#define KEY_DOWN 65364

typedef struct	s_img
{
	void	*surface;
	int		*data;
	int		w;
	int		h;

	int		linesiz;
	int		bpp;
	int		endian;
}				t_img;

int		main(void)
{
	t_img	img;
	void	*id;
	void	*win;

	id = mlx_init();
	win = mlx_new_window(id, 500, 500, "test");
	img.surface = mlx_xpm_file_to_image(id, "../assets/2d_floor.xpm", &img.w, &img.h);
	img.data = (int*)mlx_get_data_addr(img.surface, &img.bpp, &img.linesiz, &img.endian);
	mlx_put_image_to_window (id, win, img.surface, 10, 10);
	mlx_loop(id);
	return (0);
}
