#ifndef HEADER_H
#define HEADER_H

typedef struct s_data {
void    *img;
char   *addr;
int     bpp;
int     size_len;
int     endian;

} t_data;

typedef struct s_vars{
    void *mlx;
    void   *wind;
} t_vars;
#endif