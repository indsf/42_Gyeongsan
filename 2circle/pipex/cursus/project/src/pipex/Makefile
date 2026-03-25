NAME = ../../library/pipex.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I ../../includes

RM = rm -rf

AR		= ar
ARFLAGS       = crs

SRCS =	ft_pipex.c	\
	ft_pipex_utils.c \
	ft_pipex_error.c \
	ft_proccess.c	\

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@mkdir -p $(dir $@)
	$(AR) $(ARFLAGS) $@ $^

clean : 
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

re : fclean all

.PHONY: all clean fclean re
