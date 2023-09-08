NAME = minishell

SRCS =	minishell.c\
		utils.c\
		signals.c\
		# exec.c\

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

clean:
	@echo "removing ./minishell."
	@rm -f $(NAME)

fclean:
	@echo "removing libft.a."
	@rm -f $(LIBFT)
	@echo "removing ./minishell."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
