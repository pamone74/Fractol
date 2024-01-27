NAME = fractol
CC   = cc
CFLAGS = -Wall -Wextra -Werror 
SRC = fractal_utils.c ft_math_utils.c ft_fractal.c string_utils.c event_utils.c
OBJ_SRC  = $(SRC:.c=.o)

all: $(NAME)
%.o: %.c
	$(CC) -c $< -o $@
$(NAME):	$(OBJ_SRC)
			make -C ./mlx
			${CC} ${OBJ_SRC} -L./mlx -lmlx -framework OpenGL -framework AppKit -o ${NAME}
clean:
		rm $(OBJ_SRC)
fclean:
	rm $(NAME)
re: fclean all