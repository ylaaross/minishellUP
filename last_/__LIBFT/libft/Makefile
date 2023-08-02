SRCS	= ft_strlcat.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_memset.c ft_bzero.c ft_memcpy.c ft_toupper.c ft_tolower.c  ft_memmove.c  ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_strlcpy.c  ft_calloc.c ft_atoi.c ft_strjoin.c ft_itoa.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_strtrim.c ft_strmapi.c ft_putnbr_fd.c ft_striteri.c ft_split.c

SRCSB	= ft_lstadd_back.c ft_lstadd_front.c ft_lstsize.c ft_strlen.c ft_lstlast.c ft_lstnew.c ft_lstclear.c ft_lstdelone.c

OBJS	= $(SRCS:.c=.o)

OBJB	= $(SRCSB:.c=.o)

NAME	= libft.a

FLAGS 	= -Wall -Werror -Wextra

CC		= gcc

RM		= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

%.o		:	%.c
			gcc $(FLAGS) -c $< -o $@

bonus:		$(OBJB)
			ar rcs $(NAME) $(OBJB)

clean:
			$(RM) $(OBJS) $(OBJB)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all
