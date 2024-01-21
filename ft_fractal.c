#include "fractol.h"
int main(int ac, char *argv[])
{
	t_fractal fractal;
    if (2 == ac && !strncmp(argv[1], "mandelbrot", 10) || 4 == ac && !strncmp(argv[1], "julia", 5) )
	{
		fractal.name = argv[1];
		if(!strncmp(fractal.name, "julia", 5))
		{
			fractal.julia_x = atodbl(argv[2]);
			fractal.julia_y = atodbl(argv[3]);
		}
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_connection);
	}else {
		printf("Error\n");
		exit(EXIT_FAILURE);
	}

}
