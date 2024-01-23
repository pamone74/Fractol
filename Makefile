NAME = fractol
CC   = cc
CFLAGS = -Wall -Wextra -Werror 
SRC = fractal_utils.c ft_math_utils.c ft_fractal.c string_utils.c event_utils.c
OBJ_SRC  = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c 
	$(CC) -I/usr/local/include -Iminilibx-O3 -c $< -o $@
$(NAME): $(OBJ_SRC)
	$(CC) $(OBJ_SRC) -Lminilibx -lmlx -L/usr/local/lib -Iminilibx -lXext -lX11 -lm -lz -o $(NAME)
clean:
	rm $(OBJ_SRC)
fclean: clean
	rm $(NAME)
re: fclean all