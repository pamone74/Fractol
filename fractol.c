//#include "fractol.h"
#include <stdio.h>


typedef struct s_complex{
    double real; // x axis on certesian plane
    double i;    // y axis on certesian plane / imaginary plane
} t_complex;
int main(void)
{
    t_complex z;
    t_complex  c;

    z.real = 0;
    z.i = 0;

    c.real = 0.5;
    c.i    = 0.4;
    for(int i = 0; i < 42; i++)
    {
        //Generalize the formulea
        // z = z ^ 2 + c
        int temp;
        temp = (z.real * z.real) - (z.i * z.i);
        z.i  = 2 * z.real * z.i;
        z.real = temp;

        //adding the c value:
        z.real += c.real;
        z.i += c.i;

        printf("The iteration n -> %d read %f  imaginary %f\n", i, z.real, z.i);
    }
    
    
}