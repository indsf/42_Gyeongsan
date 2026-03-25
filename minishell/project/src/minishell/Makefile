CC = cc -c -Wall -Wextra -Werror -g
NAME = minishell.a

INC = -I ../../includes
LIB = ../../library

SRCS = \
utils/error_handle.c \
utils/env_utils.c \
utils/etc_utils.c \
utils/execve_utils.c \
utils/token_utils.c \
utils/parser_utils.c \
utils/parse_split.c \
utils/env_expand.c \
utils/redir_utils.c \
utils/export_cmd_splited.c \
execution/builtins/built_in.c \
execution/builtins/echo_execute.c \
execution/builtins/cd_execute.c \
execution/builtins/pwd_execute.c \
execution/builtins/export_execute.c \
execution/builtins/unset_execute.c \
execution/builtins/env_execute.c \
execution/builtins/exit_execute.c \
execution/execute/file_open.c \
execution/execute/excute_process.c \
execution/execute/multi_pipe.c \
execution/execute/multi_fork_execute.c \
execution/execute/single_fork_execute.c \
execution/execute/single_pipe.c \
parsing/lexer/quotes_count_chekr.c \
parsing/lexer/quotes_div_token.c \
parsing/lexer/token_div_pipe.c \
parsing/lexer/replace_token.c \
parsing/lexer/token_div_redirect.c \
parsing/parser/create_parser_div_token.c \
parsing/parser/split_zero_quotes.c \
parsing/parser/parser_check_merge.c \
parsing/parser/parser_check_form.c \
parsing/parser/trim_cmd_isspace.c \
parsing/parser/env_replace.c \
parsing/parser/remove_space_token.c \
parsing/parser/translate_parser.c \
parsing/lexer_n_parser.c \
parsing/open_file/open_heredoc.c \
parsing/open_file/open_redirect.c \
minishell.c \
signal/main_signal.c \
signal/heredoc_signal.c \
signal/reset_signal.c \
signal/execute_signal.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $^ -o $@ $(INC)

$(NAME): $(OBJS)
	@mkdir -p ../../library
	@ar -rcs $(LIB)/$(NAME) $^

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(LIB)/$(NAME)

re: fclean all

.PHONY: all clean fclean re
