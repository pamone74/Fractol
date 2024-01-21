#ifndef FT_FRACTAL_H
#define FT_FRACTAL_H
#define WIDTH		800
#define HEIGHT		800
#define ITERATION	42
// COLORS
#define COLOR_BLACK   0x000000 // RGB(0,0,0)
#define COLOR_BLUE    0x0000FF // 
#define COLOR_RED     0xFF0000
#define COLOR_GREEN   0x00FF00
#define COLOR_WHITE   0xFFFFFF
// Pychedelic colors
#define MAGENTA_BUSRT		0xFF00FF // A vibrant magenta
#define LIME_SHOCK			0xCCFF00 // A blinding lime
#define	NEON_ORANGE			0xFF6600 // A blazing neom orange
#define PYSCHEDELIC_PURPLE 	0x660066 // A deep purple
#define AQUA_DREAM			0x33CCCC // A bright turquoise 
#define HOT_PINK			0xFF66B2 // hot pink
#define ELECTRIC_BLUE		0x0066FF // Radiant blue
#define LAVA_RED			0xFF3300 // Bright molten red

#include <stdlib.h>
#include <string.h>
#include <mlx.h>
#include <stdio.h>
#include <math.h>
#include <X11/X.h>
#include <X11/keysym.h>

typedef struct s_image
{
    void	*img_ptr;
    void	*pixels_ptr;
	char	*addr;
    int		bpp;
    int		endain;
    int		line_length;
} t_image;

typedef struct s_fractal
{
	char	*name;
    void	*mlx_connection;
    void	*mlx_new_window;
	t_image	img;
	double	escape_value;
	int		iteration;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;

}       t_fractal;

typedef struct s_complex{
    double x; // x axis on certesian plane
    double y;    // y axis on certesian plane / imaginary plane
} t_complex;



void		fractal_init(t_fractal *fractal);
double		ft_scale(double unscaled_num, double new_min, double new_max, double old_min, double old_max);
t_complex	ft_sum_complex(t_complex z1, t_complex z2);
t_complex	ft_square_complex(t_complex z);
void		ft_data_init(t_fractal *fractal);
void		my_pixel_put(int x, int y, t_image *img, int color);
void		fractal_render(t_fractal *fractal);

// Event handling
void		ft_event_init(t_fractal *fractal);
int			ft_close_handler(t_fractal *fractal);
int			ft_key_handle(int	keysys, t_fractal *fractal);
int			ft_button_handle(int button, int x, int y, t_fractal *fractal);
double		atodbl(char *s);
int			ft_track_julia(int x, int y, t_fractal *fractal);
#endif