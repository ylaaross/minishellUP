NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CSFLAGS = #-I/Users/asaber/.brew/opt/readline/include
LDFLAGS = #-L/Users/asaber/.brew/opt/readline/lib

LIBFT_DIR = __LIBFT/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIRS = execution parsing __ENV __LIBFT
MAIN_SRC_DIR = .

OBJ_DIR = obj
MAIN_OBJ_DIR = obj/main

SRC = __ENV/env.c __ENV/linked_data.c __LIBFT/ft_strlen.c __LIBFT/ft_strncmp.c execution/cd.c execution/check_builtins.c execution/echo.c execution/env.c execution/exit.c execution/export.c execution/heardoc.c execution/main.c execution/main.o execution/normal.c execution/normal1.c execution/pwd.c execution/redirection.c execution/signals.c execution/unset.c parsing/ft_itoa.c parsing/ft_split.c parsing/ft_strdup.c parsing/ambiguiss.c parsing/minishell1.c parsing/minishell2.c parsing/minishell3.c parsing/minishell4.c parsing/minishell5.c parsing/minishell6.c parsing/minishell7.c parsing/minishell8.c parsing/minishell9.c parsing/nodes_creation.c parsing/parse2.c parsing/parse2_.c parsing/parse2_utils.c parsing/parse2_utils1.c parsing/parse2_utils2.c parsing/personalised_splites.c parsing/test_cases.c
MAIN_SRC = minishell.c

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
MAIN_OBJ = $(addprefix $(MAIN_OBJ_DIR)/,$(MAIN_SRC:.c=.o))

$(shell mkdir -p $(OBJ_DIR) $(addprefix $(OBJ_DIR)/,$(SRC_DIRS)) $(MAIN_OBJ_DIR))

RM = rm -rf

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(CSFLAGS)  -c $< -o $@

$(MAIN_OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(CSFLAGS)  -c $< -o $@

$(NAME): $(OBJ) $(MAIN_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJ) $(MAIN_OBJ) -lreadline -L $(LIBFT_DIR) -lft

clean:
	$(RM) $(OBJ) $(MAIN_OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
