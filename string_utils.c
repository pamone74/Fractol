/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 00:42:39 by pamone            #+#    #+#             */
/*   Updated: 2024/01/24 00:44:09 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	ft_strncmp(const char *str1, const char *str2, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (i == len)
		return (0);
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			ft_handle_pixels(x, y, fractal);
	}
	mlx_put_image_to_window(fractal->mlx_init,
		fractal->window, fractal->img.img_ptr, 0, 0);
}

void	ft_data_init(t_fractal *fractal)
{
	fractal->escape_value = 4;
	fractal->iteration = 42;
	fractal->shift_x = 0;
	fractal->shift_y = 0;
	fractal->zoom = 1.0;
}

void	my_pixel_put(int x, int y, t_image *img, int color)
{
	int	offset;

	offset = (y * img->line_length) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

void	ft_pustr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}
