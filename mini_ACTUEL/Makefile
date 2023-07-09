NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = main.c __LIBFT/ft_strlen.c __ENV/env.c __ENV/linked_data.c pwd.c env.c export.c normal.c minishell.c yassir_v3/parse2.c yassir_v3/ft_strdup.c

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
