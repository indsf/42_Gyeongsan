NAME = ../../library/so_long.a
DIR = ../../library
CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR ?= ./minilibx-linux
INCLUDES = -I ../../includes -I $(MLX_DIR)

RM = rm -rf

AR		= ar
ARFLAGS       = crs

SRCS =	so_long.c	\
		play_move.c	\
		set_image.c	\
		so_long_utils1.c	\
		map.parse.c	\
		check_map.c	\
		find_record.c	\
		find_path.c	\
		error_check.c	\
		

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@mkdir -p $(DIR)
	$(AR) $(ARFLAGS) $@ $^

$(MLX):
	make -C $(MLX_DIR)

clean : 
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

re : fclean all

.PHONY: all clean fclean re
