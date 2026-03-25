NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

LIBFTNAME = libft
LIBFT = $(LIBFTNAME)/libft.a

SRCS =	ft_error_utils.c	\
		ft_error_util2.c	\
		ft_error_handle.c \
		ft_algorithmn_sort.c	\
		ft_algorithmn_help.c	\
		ft_algorithmn_help2.c	\
		push_swap.c \
		ft_command.c \
		ft_command2.c \
		ft_command3.c	\



OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(LIBFT):
	make -C $(LIBFTNAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

clean : 
	$(RM) $(OBJS)
	make clean -C $(LIBFTNAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C $(LIBFTNAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

re : fclean all

.PHONY: all clean fclean re