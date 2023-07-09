/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 20:26:02 by asaber            #+#    #+#             */
/*   Updated: 2023/07/08 22:49:55 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>

typedef struct env
{
	char		*variable;
	char		*value;
	struct env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*env;
}	t_shell;
typedef struct command_devide
{
	char				*content;
	int					state;
	int					token;
	struct command_devide	*next;
}t_command_d;

typedef struct file
{
	char		*file_name;
	int			type;
	struct file *next;
}t_file;

typedef struct parsed_command
{
	char					**command;
	int						exit_status;
	struct parsed_command	*next;
	t_file	*file;
}t_pcommand_d;

t_env	*__fill_env(char **env);
int		test(t_command_d	*t);
int 	count_words(t_command_d *t);
void	fifo_cmd(t_pcommand_d **head);
void 	parse_129(t_command_d *t, t_pcommand_d **p);
void 	parse_200(t_command_d *t, t_pcommand_d **p);
void 	parse_127(t_command_d *t, t_pcommand_d *p);
int 	command_number(t_command_d *t);
void	_ft_lstadd_back(t_env **lst, t_env *new);
t_env	*_ft_lstnew(void *variable, void *value);
t_env	*__fill_env(char **env);
char	*cut_secound(char *env, char *first_env);
char	*cut_first(char *env);
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
	EXIT_STATUS =16,
};	
void	_ft_lstadd_back(t_env **lst, t_env *new);
char	*cut_first(char *env);
char	*cut_secound(char *env, char *first_env);
t_env	*_ft_lstnew(void *variable, void *value);
size_t	ft_strlen(const char *c);
t_env	*__fill_env(char **env);
char	**convert_list(void);
void	__export(char *str);
int		do_command(char **command);
void	__pwd(t_env *env);
void	__env(t_env *env);

t_shell		Glob;
#endif