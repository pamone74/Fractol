/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 00:40:02 by pamone            #+#    #+#             */
/*   Updated: 2024/01/24 00:46:51 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	ft_event_init(t_fractal *fractal)
{
	mlx_hook(fractal->window, KeyPress, KeyPressMask, ft_key_handle, fractal);
	mlx_hook(fractal->window, ButtonPress,
		ButtonPressMask, ft_button_handle, fractal);
	mlx_hook(fractal->window, DestroyNotify,
		StructureNotifyMask, ft_close_handler, fractal);
	mlx_hook(fractal->window, MotionNotify,
		PointerMotionMask, ft_track_julia, fractal);
}

int	ft_close_handler(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_init, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_init, fractal->window);
	mlx_destroy_display(fractal->mlx_init);
	free(fractal->mlx_init);
	exit(EXIT_SUCCESS);
	return (0);
}

int	ft_key_handle(int keysys, t_fractal *fractal)
{
	if (keysys == XK_Escape)
		ft_close_handler(fractal);
	else if (keysys == XK_Left)
		fractal->shift_x += (0.5 * fractal->zoom);
	else if (keysys == XK_Right)
		fractal->shift_x -= (0.5 * fractal->zoom);
	else if (keysys == XK_Up)
		fractal->shift_y += (0.5 * fractal->zoom);
	else if (keysys == XK_Down)
		fractal->shift_y -= (0.5 * fractal->zoom);
	else if (keysys == XK_plus || keysys == 65451)
		fractal->iteration += 10;
	else if (keysys == XK_minus || keysys == 65453)
		fractal->iteration += 10;
	fractal_render(fractal);
	return (0);
}

int	ft_button_handle(int button, int x, int y, t_fractal *fractal)
{
	if (button == Button5)
		fractal->zoom *= 0.95;
	else if (button == Button4)
		fractal->zoom *= 1.05;
	fractal_render(fractal);
	return (0);
}

// tracking to chnage julia dynamically

int	ft_track_julia(int x, int y, t_fractal *fractal)
{
	if (!strncmp(fractal->name, "julia", 5))
	{
		fractal->julia_x = (ft_scale(x, -2, +2,
					WIDTH) * fractal->zoom) + fractal->shift_x;
		fractal->julia_y = (ft_scale(y, +2, -2,
					HEIGHT) * fractal->zoom) + fractal->shift_y;
		fractal_render(fractal);
	}
	return (0);
}
