NAME = cube

MLX_PATH = ./minilibx-linux
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
MLX = $(MLX_PATH)/libmlx.a
CC = cc

SRC = cube.c free.c \
./gnl/map.c ./gnl/get_next_line.c ./gnl/get_next_line_utils.c \
./parser/flood_fill.c ./parser/parser.c ./parser/coordinates.c ./parser/aux_coordinates.c ./parser/utils_parser.c \
./raycast/raycast.c

OBJS = ${SRC:%.c=objects/%.o}

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address -I. -I/usr/include -I$(MLX_PATH)

all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT) -L$(MLX_PATH) -lX11 -lXext -lm -o $(NAME)

$(MLX):
	$(MAKE) -C $(MLX_PATH)

$(LIBFT):
	@make all -sC ./libft

objects/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf objects
	@make clean -sC ./libft
	$(MAKE) -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)
	@make fclean -sC ./libft

re: fclean all

.PHONY: all clean fclean re
