#include <stdint.h>
#include <mlx.h>
#include "header.h"
#include <stdio.h>

void ft_put_pixel(t_data *data, int x, int y, int color)
{
    char *dest;
    dest = data->addr + (y * data->size_len + x * (data->bpp / 8));
    *(unsigned int *)dest = color;
}
void    ft_initialize_screen(t_data img, int width, int length, int color)
{
    int i = 0;
       while (i < width) {
        int j = 0;
        while(j < length)
        {
            ft_put_pixel(&img, i, j, color);
            j++;
        }
    i++;
    }
}
/*
    This function takes two parameters, 1 double opacity which is the transperency of the color
    and the uunsigned int 32 bit for color compatibility
    it will return the  color based on the opacity give.
    This line of code uint8_t alpha = (uint8_t)(opacity * 255.0); is getting the absolute value out of 255
     This part scales the opacity value (which is in the range [0, 1]) to the range [0, 255], as alpha values
     are usually represented as an 8-bit integer ranging from 0 to 255.
    This  return ((color & 0x00FFFFFF )| (alpha << 24)); first mask the original color the combine it with alpha using | 
    after it is being shifted to the MSB. alpha << 24 
    Note:
        The bitwise operator << have hiher precdence than |

*/
uint32_t   ft_add_shade(double opacity, uint32_t color)
{
    if(opacity == 1.0)
        return (color = 0x00000000);
    else if(opacity == 0.0)
        return (color);
    else if(opacity > 0.0 && opacity <= 1.0)
    {
        uint8_t alpha = (uint8_t)(opacity * 255.0);
        return ((color & 0x00FFFFFF )| (alpha << 24));
    }
    else
        return (-1);
}
/*
    This function inverts the given color by use of XOR bitwise operator which retruns true if the operands are different.
    The color is change by subtracting given color intesity from the maximum intensity which is 255;
    for example if i have 0x00FF0000 which is pure red;
        R = 0xFF - 0xFF = 0x00
        G = 0xFF - 0x00 = 0xFF
        B = 0xFF - 0x00 = 0xFF
    and then after getting the opposite of the color 0x00FF0000  we will get 0x0000FFFF which is cyan
*/
uint32_t ft_opposite(uint32_t color)
{
    return(color ^ 0xFFFFFFFF);

}

int ft_close(int keycode, t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->wind);
    return (0);
}
int main(void)
{
    t_data img;
    t_vars mlx;
    mlx.mlx = mlx_init();
    mlx.wind   = mlx_new_window(mlx.mlx, 1200, 800, "So_long");
    img.img = mlx_new_image(mlx.mlx, 500, 500);
    img.addr = mlx_get_data_addr(img.img, &img.bpp,&img.size_len , &img.endian);

    int x = 500;
    int y = 500;
    int i = 0;
    uint32_t color = ft_add_shade(0.5, 0x0000FF00);
    uint32_t opp = ft_opposite(color);
    printf("%X \n", opp);
    while (i < x) {
        int j = 0;
        while(j < y)
        {
            ft_put_pixel(&img, i, j, opp);
            j++;
        }
    i++;
    }
    mlx_put_image_to_window(mlx.mlx, mlx.wind, img.img, 3, 3);
    mlx_hook(mlx.wind, 2, 1L<<0, ft_close, &mlx);
    mlx_loop(mlx.mlx);
}
