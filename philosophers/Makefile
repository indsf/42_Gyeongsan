NAME = philo

DIRECTORY = ./project

SOURCE = $(DIRECTORY)/srcs

PHILOSOPHERS = $(SOURCE)/philo

LIBRARY = $(DIRECTORY)/library

PHILOSOPHERS_A = $(LIBRARY)/philosophers.a

CC = cc -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(PHILOSOPHERS_A)
	@$(CC) $^ -o $@
	
$(PHILOSOPHERS_A): $(PHILOSOPHERS)
	@$(MAKE) -C $(PHILOSOPHERS) -s

clean:
	@$(MAKE) -C $(PHILOSOPHERS) fclean -s
	
fclean: clean
	@rm -rf $(NAME)

	
re: fclean all

.PHONY: all clean fclean re bonus
