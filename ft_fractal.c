/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:28:11 by pamone            #+#    #+#             */
/*   Updated: 2024/01/26 20:24:06 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	main(int ac, char *argv[])
{
	t_fractal	fractal;

	if ((2 == ac && !ft_strncmp(argv[1], "Mandelbrot", 10))
		|| (4 == ac && !ft_strncmp(argv[1], "Julia", 5)))
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
		ft_pustr("Parameters Allowed are;\n");
		ft_pustr("1. ./fractol Mandelbrot\n2. ./fractol Julia <Nm1> <Nm2>\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}
