NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

LIBFT_DIR = __LIBFT/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = execution/main.c execution/redirection.c execution/unset.c execution/heardoc.c execution/exit.c execution/cd.c execution/echo.c __LIBFT/ft_strlen.c __ENV/env.c __ENV/linked_data.c execution/pwd.c execution/env.c execution/export.c execution/normal.c execution/check_builtins.c minishell.c parsing/parse2.c parsing/ft_strdup.c gnl/get_next_line.c gnl/get_next_line_utils.c

OBJS = $(SRC:.c=.o)

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $(NAME) -lreadline

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re