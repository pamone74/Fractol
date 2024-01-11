NAME = so_long
CC   = cc
CFLAGS = -Wall -Wextra -Werror 
SRC = main.c
OBJ_SRC  = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c 
	$(CC) -I/usr/local/include -Iminilibx-linux -O3 -c $< -o $@
$(NAME): $(OBJ_SRC)
	$(CC) $(OBJ_SRC) -Lminilibx-linux -lmlx -L/usr/local/lib -Iminilibx-linux -lXext -lX11 -lm -lz -o $(NAME)
clean:
	rm $(OBJ_SRC)
fclean: clean
	rm $(NAME)
re: fclean all