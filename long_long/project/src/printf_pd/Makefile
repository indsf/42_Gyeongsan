NAME	      = ../../library/printf_pd.a
DIR = ../../library
CC		= cc
CFLAG	      = -Wall -Wextra -Werror
RM		= rm -f
AR		= ar
ARFLAGS       = crs
INCLUDES	= -I ../../includes

SRCS = 	ft_printf.c \
		ft_pointer.c \
		ft_unsigned.c \
		ft_str.c \
		ft_int.c \
		ft_char.c \
		ft_hex.c \

OBJS	= $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BN:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAG) $(INCLUDES) -c $< -o $@

clean :
	$(RM) $(RMFLAG) $(OBJS) $(OBJS_BONUS)

fclean : clean
	$(RM) $(RMFLAG) $(NAME)

re : fclean all

$(NAME) : $(OBJS)
	@mkdir -p $(DIR)
	$(AR) $(ARFLAGS) $@ $^

bonus : $(NAME)

.PHONY : all clean fclean re
