/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 00:40:02 by pamone            #+#    #+#             */
/*   Updated: 2024/01/27 12:42:58 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"
#include "mlx/mlx.h"

/* 
	This is the even handler init function that uses the hook function provided
	by Minilibx library
	The mlx_hook functions takes four parameters, the win_ptr which is the pointer
	to the window
		x_event which is the type of event for example Keypress Event, Button event 
		etc, the x_mask
		is the even mask for example ButtonPressMask etc Ref: 42 minilibx doc, the 
		function pointer to the
		handler function and the pointer to the struct element that recives the event

		NB All events have their one function prototype signature:
 */
void	ft_event_init(t_fractal *fractal)
{
	mlx_hook(fractal->window, 02,
		1L << 0, ft_key_handle, fractal);
	mlx_hook(fractal->window, 04,
		1L << 1, ft_button_handle, fractal);
	mlx_hook(fractal->window, 17,
		1L << 17, ft_close_handler, fractal);
	mlx_hook(fractal->window, 06,
		1L << 6, ft_track_julia, fractal);
}

int	ft_close_handler(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_init, fractal->img.img_ptr);
	mlx_clear_window(fractal->mlx_init, fractal->window);
	mlx_destroy_window(fractal->mlx_init, fractal->window);
	exit(EXIT_SUCCESS);
	return (0);
}

int	ft_key_handle(int keysys, t_fractal *fractal)
{
	if (keysys == 53)
		ft_close_handler(fractal);
	else if (keysys == 123)
		fractal->shift_x += (0.5 * fractal->zoom);
	else if (keysys == 124)
		fractal->shift_x -= (0.5 * fractal->zoom);
	else if (keysys == 125)
		fractal->shift_y += (0.5 * fractal->zoom);
	else if (keysys == 126)
		fractal->shift_y -= (0.5 * fractal->zoom);
	else if (keysys == 69)
		fractal->iteration += 10;
	else if (keysys == 78)
		fractal->iteration += 10;
	fractal_render(fractal);
	return (0);
}

int	ft_button_handle(int button, int x, int y, t_fractal *fractal)
{
	if (button == 5)
		fractal->zoom *= 0.95;
	else if (button == 4)
		fractal->zoom *= 1.05;
	fractal_render(fractal);
	return (0);
}

// tracking to chnage julia dynamically

int	ft_track_julia(int x, int y, t_fractal *fractal)
{
	if (!strncmp(fractal->name, "Julia", 5))
	{
		fractal->julia_x = (ft_scale(x, -2, +2,
					WIDTH) * fractal->zoom) + fractal->shift_x;
		fractal->julia_y = (ft_scale(y, +2, -2,
					HEIGHT) * fractal->zoom) + fractal->shift_y;
		fractal_render(fractal);
	}
	return (0);
}
