/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:29:21 by pamone            #+#    #+#             */
/*   Updated: 2024/01/24 01:47:42 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"
#include <mlx.h>

static	void	malloc_error(void)
{
	perror("error with malloc");
	exit(EXIT_FAILURE);
}

void	fractal_init(t_fractal *fractal)
{
	fractal->mlx_init = mlx_init();
	if (fractal->mlx_init == NULL)
		malloc_error();
	fractal->window = mlx_new_window(fractal->mlx_init, WIDTH,
			HEIGHT, fractal->name);
	if (fractal->window == NULL)
	{
		mlx_destroy_display(fractal->mlx_init);
		free(fractal->mlx_init);
		malloc_error();
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_init, WIDTH, HEIGHT);
	if (fractal->img.img_ptr == NULL)
	{
		mlx_destroy_window(fractal->mlx_init, fractal->window);
		mlx_destroy_display(fractal->mlx_init);
		free(fractal->mlx_init);
		malloc_error();
	}
	fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bpp, &fractal->img.line_length, &fractal->img.endain);
	ft_event_init(fractal);
	ft_data_init(fractal);
}

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

uint32_t	ft_add_shade(double opacity, uint32_t color)
{
	uint8_t	alpha;

	if (opacity == 1.0)
		return (color = 0x00000000);
	else if (opacity == 0.0)
		return (color);
	else if (opacity > 0.0 && opacity <= 1.0)
	{
		alpha = (uint8_t)(opacity * 255.0);
		return ((color & 0x00FFFFFF) | (alpha << 24));
	}
	else
		return (-1);
}

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
