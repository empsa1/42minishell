NAME = minishell

SRCS =	parsing/parsing.c\
		parsing/utils_parsing.c\
		parsing/expand_parsing.c\
		parsing/token_error.c\
		parsing/check_unclosed.c\
		minishell.c\
		signals.c\
		utils/utils.c\
		utils/utils2.c\
		utils/error_printing.c\
		utils/utils3.c\
		utils/get_env.c\
		utils/cleardata.c\
		builtins/check_builtins.c\
		builtins/cd.c\
		builtins/echo.c\
		builtins/exit.c\
		builtins/env.c\
		builtins/export.c\
		builtins/pwd.c\
		builtins/unset.c\
		execution/exec.c\
		execution/heredoc.c\
		execution/utils_exec.c\
		execution/expand.c\
		utils/free_data.c\
		#parsing/check_unclosed.c\
		#parsing/token_error.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I ./includes

HEADERFILES = ./includes/minishell.h

LIBFT = libft.a

LIBS = -lreadline $(LIBFT)

all: $(NAME)

$(NAME): $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $^ $(INCLUDES) $(LIBS) -o $(NAME) -g
	@echo "compilation OK."

$(LIBFT):
	$(MAKE) -C libft
	mv libft/$(LIBFT) .
	$(MAKE) -C libft clean

lean:
	@echo "removing ./minishell."
	@rm -f $(NAME)

fclean:
	@echo "removing libft.a."
	@rm -f $(LIBFT)
	@echo "removing ./minishell."
	@rm -f $(NAME)

re: fclean all

r: re && clear && ./minisheel

.PHONY: all clean fclean re r