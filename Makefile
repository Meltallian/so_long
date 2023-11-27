# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long
LIBFT = libft/libft.a
MLX = minilibx_macos/libmlx.a
SO_LONG_SRC = ber_parse.c main.c
SO_LONG_OBJ = $(SO_LONG_SRC:.c=.o)
#INCLUDES_DIR = -I./includes -I./libft/includes -I./minilibx_macos/includes
#pas necessaire parceque -lft -lmlx dans la ligne cc
# Default rule
all: $(NAME)

# This won't be called if the files don't exist or are not updated
$(SO_LONG_OBJ): %.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES_DIR) -c $< -o $@

$(LIBFT):
	make -C ./libft
$(MLX):
	make -C ./minilibx_macos

$(NAME): $(LIBFT) $(MLX) $(SO_LONG_OBJ)
	$(CC) $(SO_LONG_OBJ) $(LIBFT) $(MLX) -o $(NAME) -L./libft -lft -L./minilibx_macos -lmlx -framework OpenGL -framework AppKit

clean:
	make clean -C ./libft
	make clean -C ./minilibx_macos
	rm -f $(SO_LONG_OBJ)

fclean: clean
	make fclean -C ./libft
	make clean -C ./minilibx_macos
	rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

leaks: $(NAME)
	leaks --atExit -- ./$(NAME)

.PHONY: all clean fclean re run
