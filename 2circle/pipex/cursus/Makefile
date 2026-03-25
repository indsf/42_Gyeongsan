NAME = pipex

DIRECTORY = ./project

SOURCE = $(DIRECTORY)/src
PIPEX = $(SOURCE)/pipex
PIPEX_BONUS = $(SOURCE)/pipex_bonus
LIBFT = $(SOURCE)/libft
GNL = $(SOURCE)/real_get_next_line

LIBRARY = $(DIRECTORY)/library
PIPEX_A = $(LIBRARY)/pipex.a
PIPEX_BONUS_A = $(LIBRARY)/pipex_bonus.a
LIBFT_A = $(LIBRARY)/libft.a
GNL_A = $(LIBRARY)/get_next_line.a

PIPEX_SRCS = $(addprefix $(PIPEX)/, \
ft_pipex.c	\
ft_pipex_utils.c \
ft_pipex_error.c \
ft_proccess.c	\
)
PIPEX_BONUS_SRCS = $(addprefix $(PIPEX_BONUS)/, \
ft_heredoc_bonus.c \
ft_pipex_bonus.c \
ft_pipex_error_bonus.c \
ft_pipex_utils_bonus.c \
ft_process_bonus.c \
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
CC = cc -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(PIPEX_A) $(LIBFT_A)
	$(CC) $^ -o $@
	
$(PIPEX_A): $(PIPEX_SRCS)
	$(MAKE) -C $(PIPEX)

$(LIBFT_A): $(LIBFT_SRCS)
	$(MAKE) -C $(LIBFT)
	
$(GNL_A): $(GNL_SRCS)
	$(MAKE) -C $(GNL)

$(PIPEX_BONUS_A): $(PIPEX_BONUS_SRCS)
	$(MAKE) -C $(PIPEX_BONUS)
	
bonus: .depend

.depend: $(PIPEX_BONUS_A) $(LIBFT_A) $(GNL_A)
	$(CC) $^ -o $(NAME)
	@touch .depend

clean:
	$(MAKE) -C $(GNL) fclean
	$(MAKE) -C $(PIPEX_BONUS) fclean
	$(MAKE) -C $(PIPEX) fclean
	$(MAKE) -C $(LIBFT) fclean
	
fclean: clean
	rm -rf $(NAME)
	@rm -rf .depend
	
re: fclean all

.PHONY: all clean fclean re bonus
