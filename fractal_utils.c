#include "fractol.h"
#include "sss/mlx_explained/minilibx-linux/mlx.h"
#include <X11/X.h>
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

static	void	malloc_error()
{
	perror("error with malloc");
	exit(EXIT_FAILURE);
}
void	fractal_init(t_fractal *fractal)
{
	fractal->mlx_connection = mlx_init();
	if(fractal->mlx_connection == NULL)
	{
		malloc_error();
	}
	fractal->mlx_new_window = mlx_new_window(fractal->mlx_connection, WIDTH, HEIGHT, fractal->name);
	if(fractal->mlx_new_window == NULL)
	{
		mlx_destroy_display(fractal->mlx_connection);
		free(fractal->mlx_connection);
		malloc_error();
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_connection, WIDTH, HEIGHT);
	if(fractal->img.img_ptr == NULL)
	{
		mlx_destroy_window(fractal->mlx_connection, fractal->mlx_new_window);
		mlx_destroy_display(fractal->mlx_connection);
		free(fractal->mlx_connection);
		malloc_error();

	}
	fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.img_ptr, &fractal->img.bpp, &fractal->img.line_length, &fractal->img.endain);
	ft_event_init(fractal);
	ft_data_init(fractal);
}

static	void	ft_mandle_vs_julia(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if(!strncmp(fractal->name, "julia", 5))
	{
		c->x = fractal->julia_x;
		c->y = fractal->julia_y;
	}
	else {
	c->x = z->x;
	c->y = z->y;
	}
}
void	ft_handle_pixels(int x, int y, t_fractal *fractal)
{
	t_complex z;
	t_complex c;
	int			i;
	int			color;

	// 1 * iteration
	i = 0;

	// This is the scale to fit mandel needs
	z.x = (ft_scale(x, -2, +2, 0, WIDTH) * fractal->zoom) + fractal->shift_x;
	z.y	= (ft_scale(y, +2, -2, 0, HEIGHT)* fractal->zoom) + fractal->shift_y;
	// How many times do we need to iterate z^2 + c
	// z = z^2 + c
	ft_mandle_vs_julia(&z, &c, fractal);
	while(i < fractal->iteration)
	{
		
		//actual z^2 + c
		z = ft_sum_complex(ft_square_complex(z), c);
		
		// is the value escaped?
		// if hypothenuse > 2 i assume that point has escaped
		if((z.x * z.x) + (z.y * z.y) > fractal->escape_value)
		{
			//t_image img;
			color = ft_scale(i, COLOR_BLACK, COLOR_WHITE, 0, fractal->iteration);
			
			my_pixel_put(x,y, &fractal->img, color);
			
			return ;
		}
		
		++i;
	}
	
	// if we reach here, it means we are in the madelbrot given the iteration made.
	my_pixel_put(x,y, &fractal->img, PYSCHEDELIC_PURPLE);
}

void	fractal_render(t_fractal *fractal)
{
	int x;
	int y;
	y = -1;
	while(++y < HEIGHT)
	{
		x = -1;
		while(++x < WIDTH)
		{

			ft_handle_pixels(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->mlx_connection, fractal->mlx_new_window, fractal->img.img_ptr, 0, 0);
}

void	ft_data_init(t_fractal *fractal)
{
	fractal->escape_value = 4;// 2 ^ 2
	fractal->iteration  = 42;
	fractal->shift_x = 0;
	fractal->shift_y = 0;
	fractal->zoom  = 1.0;
}

void	my_pixel_put(int x, int y, t_image *img, int color)
{
	int offset;

	offset = (y * img->line_length) + ( x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;

	//  char *dest;
    // dest = img->addr + (y * img->line_length + x * (img->bpp / 8));
    // *(unsigned int *)dest = color;
}

void	ft_event_init(t_fractal *fractal)
{
	mlx_hook(fractal->mlx_new_window, KeyPress, KeyPressMask, ft_key_handle, fractal);
	mlx_hook(fractal->mlx_new_window, ButtonPress, ButtonPressMask, ft_button_handle, fractal);
	mlx_hook(fractal->mlx_new_window, DestroyNotify, StructureNotifyMask, ft_close_handler, fractal);
	mlx_hook(fractal->mlx_new_window, MotionNotify, PointerMotionMask, ft_track_julia, fractal);

}

// ft_key_handle ; the prototype for ketpress is int (*f)(int keycode, void *param);
int	ft_close_handler(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_connection, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_connection, fractal->mlx_new_window);
	mlx_destroy_display(fractal->mlx_connection);
	free(fractal->mlx_connection);
	exit(EXIT_SUCCESS);
	return (0);
}
int	ft_key_handle(int	keysys, t_fractal *fractal)
{
	if(keysys == XK_Escape)
		ft_close_handler(fractal);
	else if(keysys == XK_Left)
		fractal->shift_x += (0.5 * fractal->zoom);
	else if(keysys == XK_Right)
		fractal->shift_x -= (0.5 * fractal->zoom);
	else if(keysys == XK_Up)
		fractal->shift_y += (0.5 * fractal->zoom);
	else if(keysys == XK_Down)
		fractal->shift_y -= (0.5 * fractal->zoom);
	else if(keysys == XK_plus || keysys == 65451)
		fractal->iteration += 10;
	else if(keysys == XK_minus || keysys == 65453)
		fractal->iteration += 10;
	fractal_render(fractal);
	return (0);
}

int	ft_button_handle(int button, int x, int y, t_fractal *fractal)
{
	//zoom in
	if(button == Button5)
	{
		fractal->zoom *= 0.95;
	}
	//zoom out
	else if(button == Button4)
		fractal->zoom *= 1.05;
	fractal_render(fractal);
	return (0);
}

// tracking to chnage julia dynamically

int	ft_track_julia(int x, int y, t_fractal *fractal)
{
	if(!strncmp(fractal->name, "julia", 5))
	{
		fractal->julia_x = (ft_scale(x, -2, +2, 0, WIDTH) * fractal->zoom) + fractal->shift_x;
		fractal->julia_y = (ft_scale(y, +2, -2, 0, HEIGHT) * fractal->zoom) + fractal->shift_y;
		fractal_render(fractal);
	}
	
	return (0);
}