NAME = ../../library/get_next_line.a
DIR = ../../library
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I ../../includes

RM = rm -rf

AR		= ar
ARFLAGS       = crs

SRCS =	get_next_line.c get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@mkdir -p $(DIR)
	$(AR) $(ARFLAGS) $@ $^

clean : 
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

re : fclean all

.PHONY: all clean fclean re
