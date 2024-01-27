/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:28:11 by pamone            #+#    #+#             */
/*   Updated: 2024/01/27 13:30:08 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static	int	ft_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '-' || c == '+' || c == '.')
		return (1);
	return (0);
}

static void	ft_secure_check(char *str)
{
	int	dot;
	int	flag;

	dot = 0;
	flag = 0;
	while (*str)
	{
		if (*str == 46)
			dot++;
		if (*str == '-' || *str == '+')
			flag++;
		if (dot > 1 || !ft_digit(*str) || flag > 1)
		{
			ft_pustr("Invalid Value\n");
			exit(EXIT_FAILURE);
		}
		str ++;
	}
}

static void	ft_parsing(char *argv2, char *argv3, t_fractal *fractal)
{
	if ((ft_atodbl(argv2) > INT_MAX || ft_atodbl(argv2) < INT_MIN))
	{
		ft_pustr("Invalid Range for real : the range is [-2 >= 2]\n");
		exit(EXIT_FAILURE);
	}
	if ((ft_atodbl(argv3) > INT_MAX || ft_atodbl(argv3) < INT_MIN))
	{
		ft_pustr("Invalid Range for Imaginary Plane : Range [-2 >= 2]\n");
		exit(EXIT_FAILURE);
	}
	ft_secure_check(argv2);
	ft_secure_check(argv3);
}

int	main(int ac, char *argv[])
{
	t_fractal	fractal;

	if ((2 == ac && !ft_strncmp(argv[1], "Mandelbrot", 10))
		|| (4 == ac && !ft_strncmp(argv[1], "Julia", 5)))
	{
		fractal.name = argv[1];
		if (!ft_strncmp(fractal.name, "Julia", 5))
		{
			ft_parsing(argv[2], argv[3], &fractal);
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
