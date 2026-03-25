NAME = so_long

DIRECTORY = ./project

SOURCE = $(DIRECTORY)/src
SO_LONG = $(SOURCE)/so_long
LIBFT = $(SOURCE)/libft
GNL = $(SOURCE)/real_get_next_line
PRINTF = $(SOURCE)/printf_pd

LIBRARY = $(DIRECTORY)/library
SO_LONG_A = $(LIBRARY)/so_long.a
LIBFT_A = $(LIBRARY)/libft.a
GNL_A = $(LIBRARY)/get_next_line.a
PRINTF_A = $(LIBRARY)/printf_pd.a

SO_LONG_SRCS = $(addprefix $(SO_LONG)/, \
so_long.c	check_map.c		error_check.c	find_path.c		find_record.c	\
map.parse.c		play_move.c		set_image.c		so_long_utils1.c	\
)
PRINTF_SRCS = $(addprefix $(PRINTF)/, \
ft_char.c    ft_pointer.c  	ft_unsigned.c  ft_int.c   ft_str.c	\
ft_hex.c	ft_printf.c \
)
GNL_SRCS = $(addprefix $(GNL)/, \
get_next_line.c \
get_next_line_utils.c \
)
LIBFT_SRCS = $(addprefix $(LIBFT)/, \
ft_atoi.c     ft_lstadd_back.c	 ft_memchr.c	  ft_split.c	 ft_strncmp.c	\
ft_bzero.c    ft_lstadd_front.c  ft_memcmp.c	  ft_strchr.c	 ft_strnstr.c	\
ft_calloc.c   ft_lstclear.c	 ft_memcpy.c	  ft_strdup.c	 ft_strrchr.c	\
ft_isalnum.c  ft_lstdelone.c	 ft_memmove.c	  ft_striteri.c  ft_strtrim.c	\
ft_isalpha.c  ft_lstiter.c	 ft_memset.c	  ft_strjoin.c	 ft_substr.c	\
ft_isascii.c  ft_lstlast.c	 ft_putchar_fd.c  ft_strlcat.c	 ft_tolower.c	\
ft_isdigit.c  ft_lstmap.c	 ft_putendl_fd.c  ft_strlcpy.c	 ft_toupper.c	\
ft_isprint.c  ft_lstnew.c	 ft_putnbr_fd.c   ft_strlen.c	 		\
ft_itoa.c     ft_lstsize.c	 ft_putstr_fd.c   ft_strmapi.c			\
)
CC = cc 
CFLAGS = -Wall -Wextra -Werror

MLX_DIR  := $(SO_LONG)/minilibx-linux
MLX_A    := $(MLX_DIR)/libmlx.a
MLX_LIBS := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm


all: $(NAME)

$(NAME): $(SO_LONG_A) $(PRINTF_A) $(LIBFT_A) $(GNL_A) $(MLX_A)
	$(CC) $(CFLAGS) \
		$(SO_LONG_A) $(PRINTF_A) $(LIBFT_A) $(GNL_A) \
		$(MLX_LIBS) -o $@
	
$(PRINTF_A): $(LIBFT_A)
	$(MAKE) -C $(PRINTF)

$(LIBFT_A): $(LIBFT_SRCS)
	$(MAKE) -C $(LIBFT)
	
$(GNL_A): $(GNL_SRCS)
	$(MAKE) -C $(GNL)

$(SO_LONG_A): $(SO_LONG_SRCS)
	$(MAKE) -C $(SO_LONG) 

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(MAKE) -C $(GNL) fclean
	$(MAKE) -C $(SO_LONG) fclean
	$(MAKE) -C $(PRINTF) fclean
	$(MAKE) -C $(LIBFT) fclean
	
fclean: clean
	rm -rf $(NAME)
	
re: fclean all

.PHONY: all clean fclean re bonus
