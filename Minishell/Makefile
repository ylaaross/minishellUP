CC = CC

 FLAGS = -Wall -Wextra -Werror -fsanitize=address -g

SRC	= minishell.c parse2.c ft_strdup.c env.c linked_data.c ft_itoa.c

OBJ	= $(SRC:.c=.o)

Name = minishell

all : $(Name)

$(Name) : $(OBJ)
	$(CC) -lreadline $(FLAGS) $^ -o $@

%.o:%.c
	$(CC)  $(FLAGS)  -c $^ -o $@

clean : 
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(Name)

re : fclean all

.phony : all clean fclean re