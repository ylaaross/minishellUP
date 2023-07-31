/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:43:57 by ylaaross          #+#    #+#             */
/*   Updated: 2023/07/31 17:39:40 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>
#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*cs1;
	unsigned char	*cs2;

	cs1 = (unsigned char *) s1;
	cs2 = (unsigned char *) s2;
	i = 0;
	while (cs1[i] || cs2[i])
	{
		if (cs1[i] != cs2[i])
			return (cs1[i] - cs2[i]);
		i++;
	}
	return (0);
}

int	count(t_command_d	*t, int search)
{
	int	i;

	i = 0;
	while (t)
	{
		if (t->token == search)
			i++;
		t = t->next;
	}
	if (i >= 1)
		return (1);
	return (0);
}

int	count_words(t_command_d *t)
{
	int		b;
	int		count;

	b = 1;
	count = 0;
	while (t)
	{
		if ((t->token == SPACE || t->token == TAB) && t->state == GENERALE)
			b = 1;
		else if (t->token != SPACE && b == 1)
		{
			count++;
			b = 0;
		}
		t = t->next;
	}
	return (count);
}

int variable_test(int i, int counter, int *v, char *p)
{
	i++;
	counter++;
	while (p[i] && (ft_isalnum(p[i]) || p[i] == '_'))
	{
		counter++;
		i++;
	}
	*v = VARIABLE;
	return (counter);
}
void ft_strlen_word(int i, int *v, int *counter, char *p)
{
	while (p[i] && !(p[i] == '"' || p[i] == '|' || p[i] == '<'
			|| p[i] == '>' || p[i] == '\'' || p[i] == ' '
			|| p[i] == 9 || p[i] == 11 || p[i] == '$'))
	{
		*v = WORD;
		*counter = *counter + 1;
		i++;
	}
}
int exit_status_test(char *p,int i, int *v)
{
	if (p[i] == '$' && (p[i + 1] && p[i + 1] == '?'))
	{
		*v = EXIT_STATUS;
		return (2);
	}
	return (0);
}


int special_char_cases(char *p, int i, int counter, int *v)
{
	if (test_special_char(p, i))
	{
		if (p[i] == '|')
			*v = PIPE;
		else if (p[i] == ' ')
			*v = SPACE;
		else if (p[i] == '\'')
			*v = SQUOTES;
		else if (p[i] == '"')
			*v = QUOTES;
		else if (p[i] == '>')
			return (test_red_out_app(p, i, v));
		else if (p[i] == '<')
		{
			if (test_red_int_her(p, i, v))
				return (test_red_int_her(p, i, v));
		}
		else if (p[i] == 9 || p[i] == 11)
			test_tab(v);
		else if (p[i] == '$' && (p[i + 1]
				&& !(p[i + 1] >= '0' && p[i + 1] <= '9')))
			return (variable_test(i, counter, v, p));
		return (1);
	}
	return (0);
}
int ft_strlen_m(char *p, int i, int *v)
{
	int	counter;

	counter = 0;
	if (special_char_cases(p, i, counter, v))
		return (special_char_cases(p, i, counter, v));
	if (exit_status_test(p, i, v))
		return (exit_status_test(p, i, v));
	if (dollar_test(p, i, v))
		return (dollar_test(p, i, v));
	ft_strlen_word(i, v, &counter, p);
	return (counter);
}

char *cp(char *p, int lent, int *s)
{
	char		*c;
	int			i;

	i = 0;
	c = malloc(sizeof(char) * lent + 1);
	while (p[*s] && i < lent)
	{
		c[i] = p[*s];
		*s = *s + 1;
		i++;
	}
	c[i] = 0;
	return (c);
}

int	var_digit(char *str)
{
	int		i;
	char	t[3];

	t[0] = '$';
	t[1] = '0';
	t[2] = 0;
	i = 0;
	while (t[1] <= '9')
	{
		if (!strcmp(t, str))
			return (1);
		t[1] = t[1] + 1;
	}
	return (0);
}
void	put_state(t_command_d	*t,	int state, int nbr, int *dsquotes)
{
	t->state = state;
	*dsquotes = nbr;
}

void	detect_state(t_command_d	*t)
{
	int		bdquotes;
	int		bsquotes;

	bdquotes = 0;
	bsquotes = 0;
	while (t)
	{
		if (t->content[0] == '\'' && bsquotes == 0 && bdquotes != 1)
			put_state(t, GENERALE, 1, &bsquotes);
		else if (t->content[0] == '"' && bdquotes == 0 && bsquotes != 1)
			put_state(t, GENERALE, 1, &bdquotes);
		else if (t->content[0] == '\'' && bsquotes == 1)
			put_state(t, GENERALE, 0, &bsquotes);
		else if (t->content[0] == '"' && bdquotes == 1)
			put_state(t, GENERALE, 0, &bdquotes);
		else if (t->content[0] != '\'' && bsquotes == 1)
			t->state = SSQUOTES;
		else if (t->content[0] != '"' && bdquotes == 1)
			t->state = SDQUOTES;
		else
			t->state = GENERALE;
		t = t->next;
	}
}

void	count_quotes(int *quotes)
{
	*quotes = *quotes + 1;
	if (!(*quotes % 2))
		*quotes = 0;
}

int		detect_quotes2(t_command_d *t)
{
	int	d_quotes;
	int	s_quotes;

	d_quotes = 0;
	s_quotes = 0;
	while (t)
	{
		if (t->token == QUOTES && s_quotes == 0)
			count_quotes(&d_quotes);
		else if (t->token == SQUOTES && d_quotes == 0)
			count_quotes(&s_quotes);
		t = t->next;
	}
	if (!d_quotes && !s_quotes)
		return (1);
	g_lob.exit_status = 1;
	return (0);
}

int test(t_command_d	*t)
{
	int	i;
	int	token_t[5];

	i = 0;
	token_t[0] = PIPE;
	token_t[1] = APPEND;
	token_t[2] = REDIRECT;
	token_t[3] = HERDOCK;
	token_t[4] = REDIRECT_IN;
	while (i < 5)
	{
		if (token_t[i] == t->token)
			return (1);
		i++;
	}
	return (0);
}

void init_pipe_red(int *ex_word, int *b_pipe,int *existing_pipe)
{
	*ex_word = 0;
	*b_pipe = 0;
	*existing_pipe = 0;
}


void increment_init(int * existing_pipe, int *ex_word, int *b_pipe)
{
	*existing_pipe = 0;
	*ex_word = 1;
	*b_pipe = *b_pipe + 1;
}

int pipe_red_test(t_command_d	*t, int SEARCH)
{
	int		b_pipe;
	int		ex_word;
	int		existing_pipe;

	init_pipe_red(&ex_word, &b_pipe, &existing_pipe);
	if (!count(t, PIPE))
		return (1);
	while (t)
	{
		if ((t->token == QUOTES || t->token == SQUOTES || t->token == WORD
				|| t->token == VARIABLE) && ex_word == 0)
			increment_init(&existing_pipe, &ex_word, &b_pipe);
		else if (t->token == SEARCH && t->state != SDQUOTES
			&& t->state != SSQUOTES)
		{
			existing_pipe = 1;
			ex_word = 0;
			b_pipe--;
		}
		t = t->next;
	}
	if (b_pipe >= 1)
		return (1);
	g_lob.exit_status = 1;
	return (0);
}

int		herdock_pos(t_command_d	*t, int search)
{
	int	pos;

	pos = 1;
	while (t)
	{
		if (t->token == search)
			return (pos);
		pos++;
		t = t->next;
	}
	return (0);
}

void initialise_her_var(int *pos, int *b_herdock)
{
	*pos = 0;
	*b_herdock = 0;
}

int while_herdock(t_command_d	*t, int search,int *b_herdock)
{
	while (t)
	{
		if (*b_herdock >= 1 && test(t))
		{
			g_lob.exit_status = 258;
			return (0);
		}
		if (t->token == search && t->state == GENERALE)
			*b_herdock = *b_herdock + 1;
		if ((t->token == QUOTES || t->token == SQUOTES || t->token == WORD
				||t->token == VARIABLE || t->token == EXIT_STATUS)
			&& *b_herdock >= 1)
			*b_herdock = *b_herdock - 1;
		t = t->next;
	}
	return (1);
}
int herdock_redirect_test(t_command_d	*t ,int search)
{
	int		b_herdock;
	int		pos;
	int		c_red_herdock;

	c_red_herdock = count(t, search);
	initialise_her_var(&pos, &b_herdock);
	if (c_red_herdock == 0)
		return (1);
	if (!while_herdock(t, search, &b_herdock))
		return (0);
	if (b_herdock == 0)
		return (1);
	g_lob.exit_status = 258;
	return (0);
}

void	free_nodes(t_command_d	*t)
{
	t_command_d		*s;

	while (t)
	{
		s = t->next;
		free(t);
		t = s;
	}	
}

int	ft_strcmp_(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*cs1;
	unsigned char	*cs2;

	cs1 = (unsigned char *) s1;
	cs2 = (unsigned char *) s2;
	i = 0;
	while (cs1[i + 1] || cs2[i])
	{
		if (cs1[i + 1] != cs2[i])
			return (cs1[i + 1] - cs2[i]);
		i++;
	}
	return (0);
}

char*	find(t_command_d	*t, t_env	*enva)
{
	while (enva)
	{
		if (ft_strcmp_(t->content ,enva->variable) == 0)
			return (strdup(enva->value));
		enva = enva->next;	
	}
	return (NULL);
}

void init_expend(int *previous, int *previoush)
{
	*previous = 0;
	*previoush = 0;
}

void	free_token(t_command_d	*t)
{
	t_command_d	*tmp;

	while (t)
	{
		tmp = t->next;
		free(t->content);
		free(t);
		t = tmp;
	}
}

void	search(t_command_d	*t ,t_env	*enva , t_command_d		**tcp)
{
	char	*s;

	s = 0;
	s = find(t, enva);
	if (s)
	{
		free(t->content);
		t->content = ft_strdup(s);
	}
	else
	{
		free(t->content);
		t->content = calloc(1, 1);
	}
	fifo_2(tcp, t->content, t->token, SDQUOTES);
}
void search2(t_command_d	*t ,t_env	*enva , t_command_d		**tcp)
{
	char	*s;

	s = 0;
	s = find(t, enva);
	if (s)
		split_parse_2(s, tcp, GENERALE);
	else
		fifo_2(tcp, "", t->token, GENERALE);
}

void	tab_space(t_command_d	**t , t_command_d		**tcp, int *inside)
{
	while (*t && (((*t)->token == TAB && (*t)->state == GENERALE)
			|| ((*t)->token == SPACE && (*t)->state == GENERALE)))
	{
		*inside = 1;
		fifo_2(tcp, (*t)->content, (*t)->token, (*t)->state);
		*t = (*t)->next;
	}
}

void else_tab(int *previoush , int *inside,t_command_d	**t, t_command_d **tcp)
{
	while (*t && (! ((*t)->token == TAB && (*t)->state == GENERALE)
			&& !((*t)->token == SPACE && (*t)->state == GENERALE)))
	{
		*previoush = 0;
		*inside = 1;
		fifo_2(tcp, (*t)->content, (*t)->token, (*t)->state);
		(*t) = (*t)->next;
	}
}
void two_functions(t_command_d	**t ,t_command_d	**tcp, int *inside ,int *previoush)
{
	tab_space(t, tcp, inside);
	else_tab(previoush, inside, t, tcp);
}

void expend_p1(t_command_d	**t, int *previoush,t_command_d	**tcp, int *inside)
{
	if ((*t)->token == HERDOCK && (*t)->state == GENERALE)
	{
		fifo_2(tcp, (*t)->content, (*t)->token, (*t)->state);
		*previoush = 1;
	}
	else if ((*t)->token == VARIABLE && *previoush == 0
		&& ((*t)->state == SDQUOTES))
		search(*t, g_lob.env, tcp);
	else if ((*t)->token == VARIABLE && *previoush == 0
		&& ((*t)->state == GENERALE))
		search2((*t), g_lob.env, tcp);
	else if (*previoush == 1)
		two_functions(t , tcp, inside, previoush);
	else
		fifo_2(tcp, (*t)->content, (*t)->token, (*t)->state);
}

t_command_d	*	expend(t_command_d	*t)
{
	int				previoush;
	t_command_d		*tmp;
	t_command_d		*tcp;
	int				inside;

	tcp = 0;
	tmp = t;
	previoush = 0;
	while (t)
	{
		inside = 0;
		expend_p1(&t, &previoush, &tcp, &inside);
		if (t && inside == 0)
			t = t->next;
	}
	free_token(tmp);
	return (tcp);
}

void	expend_herdock(t_command_d	*t)
{
	char			*s;

	while (t)
	{
		if (t->token == VARIABLE)
		{
			s = 0;
			s = find(t, g_lob.env);
			if (s)
			{
				free(t->content);
				t->content = ft_strdup(s);
			}
			else
			{
				free(t->content);
				t->content = calloc(1, 1);
			}
		}
		t = t->next;
	}
}
char	*concat_herdock(t_command_d	*t)
{
	char	*join;

	join = calloc(1, sizeof(char));
	while (t)
	{
		join = ft_strjoin_parse(join, t->content);
		t = t->next;
	}
	return (join);
}
void increment_expexit(t_command_d	**t, int *inside, int *previoush)
{
	*t = (*t)->next;
	*inside = 1;
	*previoush = 0;
}

void	expend_exit(t_command_d	*t, int exit_s)
{
	int		previoush;
	int		inside;

	previoush = 0;
	while (t)
	{
		inside = 0;
		if (t->token == HERDOCK && t->state == GENERALE)
			previoush = 1;
		else if (previoush == 1 && t->token != SPACE && t->token != TAB)
		{
			while (t && (!(t->token == SPACE && t->state == GENERALE)
					&& !(t->token == TAB && t->state == GENERALE)))
				increment_expexit(&t, &inside, &previoush);
		}
		else if (previoush == 0 && (t->token == EXIT_STATUS
				&& (t->state == GENERALE || t->state == SDQUOTES)))
		{
			free(t->content);
			t->content = ft_strdup(ft_itoa(exit_s));
		}
		if (t && !inside)
			t = t->next;
	}
}
void	free_files(t_pcommand_d	*p)
{
	t_file		*file;

	while (p->file)
	{
		free(p->file->file_name);
		free(p->file);
		file = p->file->next;
		p->file = file;
	}
}

void	free_cmd_files(t_pcommand_d	*p)
{
	t_pcommand_d		*tmp;
	int					i;

	while (p)
	{
		i = 0;
		while (p->command[i])
		{
			free (p->command[i]);
			i++;
		}
		free(p->command);
		if (p->file)
			free_files (p);
		tmp = p->next;
		p = tmp;
	}
}
void	calculate_lenth(t_pcommand_d	*p)
{
	int					i;
	t_pcommand_d		*tmp;

	i = 0;
	tmp = p;
	while (p)
	{
		i++;
		p = p->next;
	}
	while (tmp)
	{
		tmp->lenth = i;
		tmp = tmp->next;
	}
}
int		main(int argc, char* argv[], char* envp[])
{
	int 			exit_s;
	int 			exit_p;
	char			*read;
	t_command_d		*t;
	t_pcommand_d	*p;
	
	
	p = 0;
	exit_p = 0;
	exit_s = 0;
	(void)argc;
	(void)argv;
	g_lob.env = __fill_env(envp);
	int stdin = dup(STDIN_FILENO);
	int stdout = dup(STDOUT_FILENO);


	while (1)
	{
		t = 0;
		read = readline("minishell> ");
		if (!read)
			exit(g_lob.exit_status);
		add_history(read);
		split_parse(read, &t);
		detect_state(t);
		exit_p = g_lob.exit_status;
		if(detect_quotes2(t) && herdock_redirect_test(t, REDIRECT_IN) && herdock_redirect_test(t, REDIRECT) &&
		herdock_redirect_test(t, REDIRECT_IN) && herdock_redirect_test(t, APPEND) && herdock_redirect_test(t, HERDOCK) && pipe_red_test(t , PIPE))
		{
			// printf("	content		|	token	|	state	\n");
			// printf("	______________________________________________\n");
			p = 0;
			t = expend(t);
			// while(t)
			// {
			// 	printf("%s   %d   %d\n",t->content,t->state,t->token);
			// 	t=t->next;
			// }
			expend_exit(t, exit_p);
			parse_200(t, &p);
			calculate_lenth(p);
			free_token(t);
		// int i;
		// while (p)
		// {
			
		// 	i = 0;
		// 	printf("--------------cmd--------------\n");
		// 	while (p->command[i])
		// 	{
		// 		printf("||%s||\n",p->command[i]);
		// 		i++;	
		// 	}
		// 	printf("||%d||",p->lenth);
		// 	printf("--------------file-------------\n");	
		// 		while(p->file)
		// 		{
		// 			printf("%s    %d  %d\n",p->file->file_name,p->file->type,p->file->state);
		// 			p->file= p->file->next;	
		// 		}
		// 	printf("--------------next cmd---------\n");	
		// 	p = p->next;
		// }

			if (p && heardoc_check(p))
				do_heardoc(p);
			if (p)
				do_command(p);	
			  dup2(stdin, STDIN_FILENO);
			  dup2(stdout, STDOUT_FILENO);
		}
		else
		{
			write(2,"minishell: syntax error\n",24);
		}
	}
	return (0);
}
