# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long
LIBFT = libft/libft.a
MLX = mlx/libmlx.dylib
SO_LONG_SRC = main.c
SO_LONG_OBJ = $(SO_LONG_SRC:.c=.o)
INCLUDES_DIR = -I./includes -I./libft/includes -I./mlx/includes

# Default rule
all: $(NAME)

# This won't be called if the files don't exist or are not updated
$(SO_LONG_OBJ): %.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES_DIR) -c $< -o $@

$(LIBFT):
	make -C ./libft
$(MLX):
	make -C ./mlx

$(NAME): $(LIBFT) $(MLX) $(SO_LONG_OBJ)
	$(CC) $(SO_LONG_OBJ) $(LIBFT) $(MLX) -o $(NAME) -L./libft -L./mlx -lft -lmlx

clean:
	make clean -C ./libft
	make clean -C ./mlx
	rm -f $(SO_LONG_OBJ)

fclean: clean
	make fclean -C ./libft
	make clean -C ./mlx
	rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

.PHONY: all clean fclean re run
