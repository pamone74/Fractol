/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:29:21 by pamone            #+#    #+#             */
/*   Updated: 2024/01/26 23:38:15 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static	void	malloc_error(void)
{
	perror("error with malloc");
	exit(EXIT_FAILURE);
}

/*
    Function: fractal_init

    Description:
    Initializes the fractal by creating a connection to the X window server,
    setting up the window, image, and initializing event handling and data.

    Parameters:
    -> fractal: Pointer to the fractal struct
	Function: mlx_init();
	-> This intializes the fractal by creating the connection to the X window server
	Function: mlx_new_windwow()
	-> Create a new window with specified dimensions and name
	Function: mlx_new_image()
	-> Create a new image associated with the window
    Notes:
    This function assumes the existence of the following constants:
    -> WIDTH: Width of the window
    -> HEIGHT: Height of the window
*/
void	fractal_init(t_fractal *fractal)
{
	fractal->mlx_init = mlx_init();
	if (fractal->mlx_init == NULL)
		malloc_error();
	fractal->window = mlx_new_window(fractal->mlx_init, WIDTH,
			HEIGHT, fractal->name);
	if (fractal->window == NULL)
	{
		free(fractal->mlx_init);
		malloc_error();
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_init, WIDTH, HEIGHT);
	if (fractal->img.img_ptr == NULL)
	{
		mlx_destroy_window(fractal->mlx_init, fractal->window);
		free(fractal->mlx_init);
		malloc_error();
	}
	fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bpp, &fractal->img.line_length, &fractal->img.endain);
	ft_event_init(fractal);
	ft_data_init(fractal);
}

/*
	This function check for the given sets passed as argv[]
	if it is Julia sets, the real and imiginary values will point to the julia cordinates initialized in ft_data_init()
	if it is not Julia, then let the current values for the real and imaginary remains unchanged
*/
void	ft_mandle_vs_julia(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "Julia", 5))
	{
		c->x = fractal->julia_x;
		c->y = fractal->julia_y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
	}
}
/*
	This Function initialzes the values needed to execute the programe effectvely:
	
*/
void	ft_data_init(t_fractal *fractal)
{
	fractal->escape_value = 4;
	fractal->iteration = 50;
	fractal->shift_x = 0;
	fractal->shift_y = 0;
	fractal->zoom = 1.0;
}

/*
	This function takes one 'fractal' parameter which is struct
	The variables:
		z: is the real cordinate
		c: is the imaginary cordinate in complex plane
		i: is for iteration
		color: is for colors:
	The functions:
		ft_scale: This function maps cordinates to the complex plane using scaling and translation
		ft_mandle_vs_julia: This function determis which program to be executed, either Julia ot Mandelbro based o argv[]
		ft_sum_complex: This is the implemetation of the general formula to creating Maldelbrot set f(z) = z^2 + c where z is the
						complex numbers and c is the constant complex number. The complex number are numbers expressed in a t bi where
						a is real  number and i is the imaginary unit that satifies the equation i ^2 = -1;
						
						The Mandelbrot sets is a mathematica set of compes numbers that when iteratively processed according to thr formula
						either remains bounded or escape to infinity. 
						If the magnitude f Z of n iteration, remains bounded for a given c, then c is part of the mandelbro set.
						M={c∈C∣the sequence z,f(z),f(f(z)),… remains bounded}
						where:
							M =  mandelbrot set
							c∈C = sets of complex numbers 
							f(z),f(f(z)) = the sequence ius bounded. This is the condition that satifies the mandelbro set to be bounded
							|  = is read such that
		ft_square_complex: This performs the squaring of the real and imaginary units iteratively
		my_pixel_put:		This function buffers the pixels by puxels then insert it as whole image.
		
							
	
*/
void	ft_handle_pixels(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	uint32_t	color;

	i = 0;
	z.x = (ft_scale(x, -2, +2, WIDTH) * fractal->zoom) + fractal->shift_x;
	z.y = (ft_scale(y, +2, -2, HEIGHT) * fractal->zoom) + fractal->shift_y;
	ft_mandle_vs_julia(&z, &c, fractal);
	while (i < fractal->iteration)
	{
		z = ft_sum_complex(ft_square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > fractal->escape_value)
		{
			if (i > 11)
				color = ft_scale(i, COLOR_BLACK,
						COLOR_WHITE, fractal->iteration);
			else
				color = ELECTRIC_BLUE;
			my_pixel_put(x, y, &fractal->img, color);
			return ;
		}
		++i;
	}
	my_pixel_put(x, y, &fractal->img, PYSCHEDELIC_PURPLE);
}
