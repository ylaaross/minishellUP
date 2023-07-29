/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 20:26:02 by asaber            #+#    #+#             */
/*   Updated: 2023/07/29 23:55:50 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "__LIBFT/libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

typedef struct env
{
        char            *variable;
        char            *value;
		int				status;
        struct env      *next;
}       t_env;

typedef struct s_shell
{
        t_env   *env;
		int		exit_status;
}       t_shell;
typedef struct command_devide
{
        char                            *content;
        int                                     state;
        int                                     token;
        struct command_devide   *next;
}t_command_d;

typedef struct file
{
		int 					state;
        char            *file_name;
        int                     type;
        struct file *next;
}t_file;

typedef struct parsed_command
{
        char                    **command;
        int                     exit_status;
        struct parsed_command   *next;
        t_file  *file;
}t_pcommand_d;
void    command_mallocate(t_command_d *t , t_pcommand_d **p);
void	fifo(t_command_d **head, char *str, int v);
int	ft_strcmp(const char *s1, const char *s2);
int     ft_strlen_m(char *p, int i, int *v);
void	fifo_2(t_command_d **head, char *str, int v, int state);
char    *cp(char *p, int lent, int *s);
int	var_digit(char *str);
int	test_tab(int *v);
int	test_red_int_her(char *p, int i, int *v);
int	test_red_out_app(char *p, int i, int *v);
int	test_special_char(char *p, int i);
int	dollar_test(char *p, int i, int *v);
char   *split_parse_2(char *p, t_command_d **t, int state);
void	split_parse(char *p, t_command_d	**t);
t_env   *__fill_env(char **env);
int             test(t_command_d        *t);
int     count_words(t_command_d *t);
void    fifo_cmd(t_pcommand_d **head);
void    parse_129(t_command_d *t, t_pcommand_d **p);
void    parse_200(t_command_d *t, t_pcommand_d **p);
void    parse_127(t_command_d *t, t_pcommand_d *p);
int     command_number(t_command_d *t);
void    _ft_lstadd_back(t_env **lst, t_env *new);
t_env   *_ft_lstnew(void *variable, void *value);
t_env   *__fill_env(char **env);
char    *cut_secound(char *env, char *first_env);
char    *cut_first(char *env);
char    *ft_strdup(char *s1);
void    fifo(t_command_d **head, char* str, int v);
t_file  *fifo_file(t_file *head, char* str, int v, int state);
void	expend_herdock(t_command_d	*t);
char	*concat_herdock(t_command_d	*t);
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
void	fifo_2(t_command_d **head, char *str, int v, int state);
void    _ft_lstadd_back(t_env **lst, t_env *new);
char    *cut_first(char *env);
char    *cut_secound(char *env, char *first_env);
t_env   *_ft_lstnew(void *variable, void *value);
size_t  ft_strlen(const char *c);
t_env   *__fill_env(char **env);
char    **convert_list(void);
void    __export(t_pcommand_d *cmd);
int		do_command(t_pcommand_d *cmd);
int		check_builts(char *command);
int		do_builtins(t_pcommand_d *cmd);
void	__pwd(t_pcommand_d *cmd);
void    __env(t_env *env);
void	__unset(t_pcommand_d *cmd);
char	*get_next_line(int fd);
void	ft_echo(t_pcommand_d *t);
void	ft_cd(t_pcommand_d *t);
char	*search_env(char *var);
void	ft_exit(char **command);
void	__edit_env(char *var, char *value);
int		isin_env(char *var);
void	rm_node(t_env *env);
int		isin_env(char *var);
void	find_rm(int posision);
void	free_token(t_command_d	*t);
int		heardoc_check(t_pcommand_d *cmd);
int		do_heardoc(t_pcommand_d *cmd);
int		command_check(t_pcommand_d *cmd);
int		redirect(t_pcommand_d *cmd);
void	        expend_herdock(t_command_d	*t);
char	        *ft_strjoin_parse(char *s1, char *s2);
char	        *concat_herdock(t_command_d	*t);
void	        split_parse(char *p, t_command_d	**t);
int		do_execbuiltins(t_pcommand_d *cmd);
int		command_len(char **command);
void	        export_alone(void);
t_shell         Glob;
#endif