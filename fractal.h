/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 00:25:38 by pamone            #+#    #+#             */
/*   Updated: 2024/01/26 21:16:01 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H
# define WIDTH		1200
# define HEIGHT		1200
// COLORS
# define COLOR_BLACK   0x000000 // RGB(0,0,0)
# define COLOR_BLUE    0x0000FF // 
# define COLOR_RED     0xFF0000
# define COLOR_GREEN   0xEEF5FF
# define COLOR_WHITE   0xFFFFFF
// Pychedelic colors
# define MAGENTA_BUSRT			0xFF00FF // A vibrant magenta
# define LIME_SHOCK				0xCCFF00 // A blinding lime
# define NEON_ORANGE			0xFF6600 // A blazing neom orange
# define PYSCHEDELIC_PURPLE 	0x660066 // A deep purple
# define AQUA_DREAM				0x33CCCC // A bright turquoise 
# define HOT_PINK				0xFF66B2 // hot pink
# define ELECTRIC_BLUE			0x0066FF // Radiant blue
# define LAVA_RED				0xFF3300 // Bright molten red

# include <stdlib.h>
# include <string.h>
# include "./mlx/mlx.h"
# include <math.h>
#include <stdio.h>
# include <stdint.h>
# include <unistd.h>

typedef struct s_image
{
	void	*img_ptr;
	void	*pixels_ptr;
	char	*addr;
	int		bpp;
	int		endain;
	int		line_length;
}			t_image;

typedef struct s_fractal
{
	char	*name;
	void	*mlx_init;
	void	*window;
	t_image	img;
	double	escape_value;
	int		iteration;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
}			t_fractal;

typedef struct s_complex
{
	double	x;
	double	y;
}			t_complex;

void		fractal_init(t_fractal *fractal);
double		ft_scale(double unscaled_num, double new_min,
				double new_max, double old_max);
void		ft_data_init(t_fractal *fractal);
void		my_pixel_put(int x, int y, t_image *img, int color);
void		fractal_render(t_fractal *fractal);
void		ft_handle_pixels(int x, int y, t_fractal *fractal);			
//Math functions
t_complex	ft_sum_complex(t_complex z1, t_complex z2);
t_complex	ft_square_complex(t_complex z);
double		ft_atodbl(char *s);
// Event handling
void		ft_event_init(t_fractal *fractal);
int			ft_close_handler(t_fractal *fractal);
int			ft_key_handle(int keysys, t_fractal *fractal);
int			ft_button_handle(int button, int x, int y, t_fractal *fractal);
int			ft_track_julia(int x, int y, t_fractal *fractal);
// Utils
int			ft_strncmp(const char *str1, const char *str2, size_t len);
void		ft_pustr(char *str);
#endif