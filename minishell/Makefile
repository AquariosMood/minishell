NAME=minishell
CC=cc
CFLAGS=-Wall -Wextra -Werror -g
HEADER=./includes/minishell.h
INCLUDES=-I./includes

SRCS_BUILTINS := srcs/builtins/echo.c \
				 srcs/builtins/cd.c \
				 srcs/builtins/pwd.c \
				 srcs/builtins/export.c \
				 srcs/builtins/export_utils.c \
				 srcs/builtins/unset.c \
				 srcs/builtins/env.c \
				 srcs/builtins/exit.c

SRCS_UTILS_BUILTINS :=	srcs/builtins/utils_builtins/ft_strlen.c \
						srcs/builtins/utils_builtins/ft_strncmp.c \
						srcs/builtins/utils_builtins/ft_strjoin.c \
						srcs/builtins/utils_builtins/print_error_builtins.c \

SRCS_INIT_ENV := 	srcs/init_env/add_copy_env.c \
					srcs/init_env/check_is_exported.c \
					srcs/init_env/create_copy_env.c \
					srcs/init_env/get_env_name.c \
					srcs/init_env/get_env_value.c \
					srcs/init_env/init_copy_env.c

SRCS_INIT := srcs/init_minishell/init_minishell.c \
			 srcs/init_minishell/init_signal.c

SRCS_COMMAND := srcs/command/execute_command.c \
				srcs/command/add_command.c \
				srcs/command/create_command.c \
				srcs/command/execute_builtins.c \
				srcs/command/create_redirect_in_command.c \

SRCS_UTILS :=	srcs/utils/free_env.c \
				srcs/utils/free_array.c \
				srcs/utils/free_minishell.c \
				srcs/utils/ft_split.c \
				srcs/utils/ft_strndup.c \
				srcs/utils/print_tokens.c \
				srcs/utils/ft_substr.c \
				srcs/utils/convert_token_to_argv.c \
				srcs/utils/convert_token_to_argv_utils.c \
				srcs/utils/convert_token_to_command_utils.c \
				srcs/utils/convert_copy_env_to_env.c \
				srcs/utils/free_token.c \
				srcs/utils/ft_strdup.c \
				srcs/utils/free_command.c \
				srcs/utils/print_env_export.c \
				srcs/utils/free_copy_env.c \
				srcs/utils/ft_strcmp.c \
				srcs/utils/conversion_in_quote.c \
				srcs/utils/print_exit_status.c \
				srcs/utils/print_copy_env.c \
				srcs/utils/is_alpha.c \
				srcs/utils/ft_isalnum.c \
				srcs/utils/check_special_char.c \
				srcs/utils/ft_isdigit.c \
				srcs/utils/free_pipe.c \
				srcs/utils/ft_memcpy.c \
				srcs/utils/ft_memset.c \

SRCS_TOKENIZER := srcs/tokenizer/tokenise.c \
				  srcs/tokenizer/create_token.c \
				  srcs/tokenizer/add_token.c \
				  srcs/tokenizer/token_argument.c \
				  srcs/tokenizer/token_redirect_append.c \
				  srcs/tokenizer/token_redirect_input.c \
				  srcs/tokenizer/token_redirect_output.c \
				  srcs/tokenizer/token_pipe.c \
				  srcs/tokenizer/token_quote.c \
				  srcs/tokenizer/token_quote_utils.c \
				  srcs/tokenizer/token_quote_utils2.c \
				  srcs/tokenizer/token_heredoc.c \
				  srcs/tokenizer/token_command.c \
				  srcs/tokenizer/check_token.c \
				  srcs/tokenizer/check_format_tokens.c \
				  srcs/tokenizer/token_other.c \

SRCS_EXEC :=	srcs/exec/exec.c \
				srcs/exec/exec_utils.c \
				srcs/exec/exec_utils_2.c \
				srcs/exec/get_path.c \
				srcs/exec/pipeline.c \
				srcs/exec/pipeline_utils.c \
				srcs/exec/pipeline_utils2.c \
				srcs/exec/redirect.c \
				srcs/exec/redirect_input.c \
				srcs/exec/redirect_output.c \
				srcs/exec/redirect_utils.c \

SRCS := main.c \
		init_heredoc.c \
		init_heredoc_utils.c \
		init_heredoc_utils_2.c \
		check_isatty.c \
		minishell.c \
		loop_readline.c \
		normalize_commands.c \
		$(SRCS_INIT) \
		$(SRCS_UTILS) \
		$(SRCS_SIGNAL) \
		$(SRCS_COMMAND) \
		$(SRCS_BUILTINS) \
		$(SRCS_INIT_ENV)  \
		$(SRCS_TOKENIZER)  \
		$(SRCS_UTILS_BUILTINS) \
		$(SRCS_EXEC)

OBJ= $(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ) -lreadline

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

run:
	make && clear && ./$(NAME)

debug: $(NAME)
	clear && valgrind --leak-check=full --show-leak-kinds=all --track-fds=all --track-origins=yes --suppressions=supress_file -s ./$(NAME)

norm:
	norminette -R CheckForbiddenSource $(SRCS)

norm_define:
	norminette -R CheckDefine $(HEADER)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all norm norm_define run debug
