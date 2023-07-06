/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:46:25 by ylaaross          #+#    #+#             */
/*   Updated: 2023/06/24 22:18:33 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>

typedef struct command_devide
{
	char				*content;
	int					state;
	int					token;
	struct command_devide	*next;
}t_command_d;

typedef struct file
{
	char *file_name;
	int type;
	struct file *next;
}t_file;

typedef struct parsed_command
{
	char				**command;
	struct parsed_command	*next;
	t_file	*file;
}t_pcommand_d;





typedef struct env
{
	char		*variable;
	char		*value;
	struct env	*next;
}	t_env;

t_env	*__fill_env(char **env);
int		ft_strlen(char *str);
int		test(t_command_d	*t);
int 	count_words(t_command_d *t);
void	fifo_cmd(t_pcommand_d **head, int v);
void 	parse_129(t_command_d *t, t_pcommand_d **p);
void 	parse_200(t_command_d *t, t_pcommand_d **p);
void 	parse_127(t_command_d *t, t_pcommand_d *p);
int 	command_number(t_command_d *t);
void	_ft_lstadd_back(t_env **lst, t_env *new);
t_env	*_ft_lstnew(void *variable, void *value);
t_env	*__fill_env(char **env);
char	*cut_secound(char *env, char *first_env);
char	*cut_first(char *env);
int		ft_strlen(char *str);
char	*ft_strdup(char *s1);
void	fifo(t_command_d **head, char* str, int v);
t_file	*fifo_file(t_file *head, char* str, int v);
enum token{
	WORD = 1,
	SPACE = 2,
	ENV = 3,
	PIPE = 4,
	QUOTES = 5,
	SQUOTES = 6,
	APPEND = 7,
	REDIRECT = 8,
	VARIABLE = 9,
	GENERALE = 10,
	SDQUOTES = 11,
	SSQUOTES = 12,
	HERDOCK = 13,
	REDIRECT_IN = 14,
	TAB = 15,
};	