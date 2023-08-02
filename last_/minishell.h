/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 20:26:02 by asaber            #+#    #+#             */
/*   Updated: 2023/08/02 00:10:25 by asaber           ###   ########.fr       */
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
	char		*variable;
	char		*value;
	int			status;
	struct env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*env;
	int		exit_status;
}	t_shell;

t_shell		g_lob;

typedef struct command_devide
{
	char					*content;
	int						state;
	int						token;
	struct command_devide	*next;
}t_command_d;

typedef struct file
{
	int			state;
	char		*file_name;
	int			type;
	struct file	*next;
}t_file;

typedef struct parsed_command
{
	int						lenth;
	char					**command;
	int						exit_status;
	struct parsed_command	*next;
	t_file					*file;
}t_pcommand_d;

void		parse_200(t_command_d *t, t_pcommand_d **p, t_pcommand_d **tmp);
void		parse_127(t_command_d *t, t_pcommand_d *p);
int			test_cases_parse(t_command_d *t);
void		dup_function(int stdin, int stdout);
void		expend_free(t_command_d **t, t_pcommand_d	**p);
int			test_cases(t_command_d	*t);
void		read_split(t_command_d	**t);
void		var_init_env(int *stdin, int *stdout, t_pcommand_d	**p);
void		do_heardoc(t_pcommand_d *cmd);
void		free_cmd_files(t_pcommand_d	*p);
void		free_files(t_pcommand_d	*p);
void		expend_exit(t_command_d	*t);
void		increment_expexit(t_command_d	**t, int *inside, int *previoush);
char		*concat_herdock(t_command_d	*t);
void		expend_herdock(t_command_d	*t);
t_command_d	*expend(t_command_d	*t);
void		expend_p1(t_command_d	**t, int *previoush,
				t_command_d	**tcp, int *inside);
void		two_functions(t_command_d	**t, t_command_d	**tcp,
				int *inside, int *previoush);
void		else_tab(int *previoush, int *inside,
				t_command_d	**t, t_command_d **tcp);
void		tab_space(t_command_d	**t, t_command_d **tcp, int *inside);
void		search2(t_command_d	*t, t_env	*enva, t_command_d **tcp);
void		search(t_command_d	*t, t_env	*enva, t_command_d **tcp);
void		free_token(t_command_d	*t);
void		init_expend(int *previous, int *previoush);
char		*find(t_command_d	*t, t_env	*enva);
int			ft_strcmp_(const char *s1, const char *s2);
void		free_nodes(t_command_d	*t);
int			herdock_redirect_test(t_command_d *t, int search);
int			while_herdock(t_command_d	*t, int search, int *b_herdock);
void		initialise_her_var(int *pos, int *b_herdock);
int			herdock_pos(t_command_d	*t, int search);
int			pipe_red_test(t_command_d	*t, int SEARCH);
void		increment_init(int *existing_pipe, int *ex_word, int *b_pipe);
void		init_pipe_red(int *ex_word, int *b_pipe, int *existing_pipe);
int			test(t_command_d	*t);
int			detect_quotes2(t_command_d *t);
void		count_quotes(int *quotes);
void		detect_state(t_command_d	*t);
void		put_state(t_command_d	*t,	int state, int nbr, int *dsquotes);
int			var_digit(char *str);
char		*cp(char *p, int lent, int *s);
int			ft_strlen_m(char *p, int i, int *v);
int			special_char_cases(char *p, int i, int counter, int *v);
int			exit_status_test(char *p, int i, int *v);
void		ft_strlen_word(int i, int *v, int *counter, char *p);
int			variable_test(int i, int counter, int *v, char *p);
int			count_words(t_command_d *t);
int			count(t_command_d	*t, int search);
int			ft_strcmp(const char *s1, const char *s2);
void		pipe_next(t_command_d **t, t_pcommand_d **p, int *i);
void		state_token(t_command_d **t, int *state, int *token);
void		file_test_case(t_command_d **t, t_pcommand_d *p, int *i);
void		join_parse_next(t_command_d **t, int *state, char **s);
void		skip_files(t_command_d **t);
void		next(t_command_d **t);
void		pipe_(t_command_d *t, t_pcommand_d **p, int *i);
void		inside_parse(t_command_d **t, t_pcommand_d *p, int *i);
void		double_singlecotes_inside(t_command_d **t, t_pcommand_d *p, int *i);
int			content_file_parse(t_command_d *t);
int			content_to_parse(t_command_d *t);
int			double_singlecotes(t_command_d *t);
void		commande_per_pipe(t_command_d *t, t_pcommand_d *p);
void		pass_pipe(t_command_d **t);
void		command_mallocate(t_command_d *t, t_pcommand_d **p);
char		*ft_strjoin_parse(char *s1, char *s2);
int			command_number(t_command_d *t);
int			detect_token(t_command_d	*t);
int			test2(t_command_d	*t);
t_file		*fifo_file(t_file *head, char *str, int v, int state);
void		command_mallocate(t_command_d *t, t_pcommand_d **p);
void		fifo(t_command_d **head, char *str, int v);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strlen_m(char *p, int i, int *v);
void		fifo_2(t_command_d **head, char *str, int v, int state);
char		*cp(char *p, int lent, int *s);
int			var_digit(char *str);
int			test_tab(int *v);
int			test_red_int_her(char *p, int i, int *v);
int			test_red_out_app(char *p, int i, int *v);
int			test_special_char(char *p, int i);
int			dollar_test(char *p, int i, int *v);
char		*split_parse_2(char *p, t_command_d **t, int state);
void		split_parse(char *p, t_command_d	**t);
t_env		*__fill_env(char **env);
int			test(t_command_d *t);
int			count_words(t_command_d *t);
void		fifo_cmd(t_pcommand_d **head);
void		parse_200(t_command_d *t, t_pcommand_d **p, t_pcommand_d **tmp);
void		parse_127(t_command_d *t, t_pcommand_d *p);
int			command_number(t_command_d *t);
void		_ft_lstadd_back(t_env **lst, t_env *new);
t_env		*_ft_lstnew(void *variable, void *value);
t_env		*__fill_env(char **env);
char		*cut_secound(char *env, char *first_env);
char		*cut_first(char *env);
char		*ft_strdup(char *s1);
void		fifo(t_command_d **head, char *str, int v);
t_file		*fifo_file(t_file *head, char *str, int v, int state);
void		expend_herdock(t_command_d	*t);
char		*concat_herdock(t_command_d	*t);

# undef SPACE
# undef TAB

enum e_token
{
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
void		fifo_2(t_command_d **head, char *str, int v, int state);
void		_ft_lstadd_back(t_env **lst, t_env *new);
char		*cut_first(char *env);
char		*cut_secound(char *env, char *first_env);
t_env		*_ft_lstnew(void *variable, void *value);
size_t		ft_strlen(const char *c);
t_env		*__fill_env(char **env);
char		**convert_list(void);
void		__export(t_pcommand_d *cmd);
void		do_command(t_pcommand_d *cmd);
int			check_builts(char *command);
int			do_builtins(t_pcommand_d *cmd);
void		__pwd(t_pcommand_d *cmd);
void		__env(t_env *env);
void		__unset(t_pcommand_d *cmd);
void		ft_echo(t_pcommand_d *t);
void		ft_cd(t_pcommand_d *t);
char		*search_env(char *var);
void		ft_exit(char **command);
void		__edit_env(char *var, char *value);
int			isin_env(char *var);
void		rm_node(t_env *env);
int			isin_env(char *var);
void		find_rm(int posision);
void		free_token(t_command_d	*t);
int			heardoc_check(t_file *file);
int			redirect(t_pcommand_d *cmd);
void		expend_herdock(t_command_d	*t);
char		*ft_strjoin_parse(char *s1, char *s2);
char		*concat_herdock(t_command_d	*t);
void		split_parse(char *p, t_command_d	**t);
int			do_execbuiltins(t_pcommand_d *cmd);
int			command_len(char **command);
void		export_alone(void);
int			list_len(t_env *env);
int			redirect(t_pcommand_d *cmd);
void		free_impliment(t_pcommand_d **cmd, char	***env);
void		do_command(t_pcommand_d *cmd);
void		free_cpenv(char **env);
void		child_command(t_pcommand_d *cmd, char **env, int *fd, int input);
void		wait_chlid(int *fd, int *input);
void		signals(void);
void		sig_handler(int sig);
void		signals(void);
void		def_signals(void);
#endif