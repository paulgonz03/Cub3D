NAME = cube
CC = cc
CCFLAGS = -Wall -Wextra -Werror

SRC = cube.c ./gnl/map.c ./gnl/get_next_line.c ./gnl/get_next_line_utils.c ./parser/parser.c ./parser/coordinates.c ./parser/aux_coordinates.c ./parser/utils_parser.c\

OBJS = ${SRC:%.c=objects/%.o}

INCLUDES = -I. -Ilibft
LIBFTA = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C libft
	@$(CC) $(CCFLAGS) $(OBJS) $(LIBFTA) -lreadline -lhistory -o $(NAME)

objects/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) -rf objects
	@$(MAKE) -C libft clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re