CC = CC

 FLAGS = -Wall -Wextra -Werror -fsanitize=address -g

SRC	= minishell.c parse2.c ft_strdup.c env.c linked_data.c

OBJ	= $(SRC:.c=.o)

Name = minishell

all : $(Name)

$(Name) : $(OBJ)
	$(CC) -lreadline $(FLAGS) $^ -o $@

%.o:%.c
	$(CC)  $(CFLAGS)  -c $^ -o $@

clean : 
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(Name)

re : fclean all

.phony : all clean fclean re