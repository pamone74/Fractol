/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:28:11 by pamone            #+#    #+#             */
/*   Updated: 2024/01/24 01:54:56 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	main(int ac, char *argv[])
{
	t_fractal	fractal;

	if (2 == ac && !ft_strncmp(argv[1], "Mandelbrot", 10)
		|| 4 == ac && !ft_strncmp(argv[1], "Julia", 5))
	{
		fractal.name = argv[1];
		if (!ft_strncmp(fractal.name, "Julia", 5))
		{
			fractal.julia_x = ft_atodbl(argv[2]);
			fractal.julia_y = ft_atodbl(argv[3]);
		}
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_init);
	}
	else
	{
		ft_pustr("The Available Parameters\n 1. ./fractol Mandelbrot\n 2. ./fractol Julia <Point1> <Point2>\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}
