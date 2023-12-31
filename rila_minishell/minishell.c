/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:43:57 by ylaaross          #+#    #+#             */
/*   Updated: 2023/07/20 20:30:41 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>
#include "minishell.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>
#include "minishell.h"


void	fifo_2(t_command_d **head, char* str, int v,int state)
{
	t_command_d	*t;

	t = 0;
	if (*head == 0)
	{
		*head = malloc(sizeof(t_command_d));
		(*head)->content = ft_strdup(str);
		(*head)->token = v;
		(*head)->state = state;
		// printf("%s--%d--",(*head)->content,state);
		(*head)->next = 0;
	}
	else
	{
		t = *head;
		while (t->next)
			t = t->next;
		t->next = malloc(sizeof(t_command_d));
		t->next->content = ft_strdup(str);
		t->next->token = v;
		t->next->state = state;
		// printf("--%d--",state);
		t->next->next = 0;
	}
}

int count(t_command_d	*t, int search)
{
	int i;
	
	i = 0;
	while(t)
	{
		if(t->token == search)
			i++;
		t = t->next;
	}
	if(i >= 1)
		return (1);
	return(0);
}

int count_words(t_command_d *t)
{
	int b;
	int count;
	
	b = 1;
	count = 0;
	while(t)
	{
		
		if((t->token == SPACE || t->token == TAB) && t->state == GENERALE)
			b = 1;
		else if(t->token != SPACE && b == 1)
		{
			count++;
			b = 0;
		}
		t = t->next;
	}
	return(count);
}
void	fifo(t_command_d **head, char* str, int v)
{
	t_command_d	*t;

	t = 0;
	if (*head == 0)
	{
		*head = malloc(sizeof(t_command_d));
		(*head)->content = str;
		(*head)->token = v;
		(*head)->next = 0;
	}
	else
	{
		t = *head;
		while (t->next)
			t = t->next;
		t->next = malloc(sizeof(t_command_d));
		t->next->content = str;
		t->next->token = v;
		t->next->next = 0;
	}
}

void	fifo_cmd(t_pcommand_d **head)
{
	t_pcommand_d	*t;

	t = 0;
	if (*head == 0)
	{
		*head = malloc(sizeof(t_pcommand_d));
		(*head)->file = 0;
		(*head)->next = 0;
	}
	else
	{
		t = *head;
		while (t->next)
			t = t->next;
		t->next = malloc(sizeof(t_pcommand_d));
		t->next->file = 0;
		t->next->next = 0;
	}
}

int ft_strlen_m(char *p, int i, int *v)
{
	int b;
	int counter;

	b = 0;
	counter = 0;
	
	if(p[i] == '"' || p[i] == '|' || p[i] == '\'' || p[i] == ' '|| p[i] == '<' || p[i] == '>' || p[i] == 9 || p[i] == 11 || 
	
	(p[i] == '$' && (p[i + 1] && (ft_isalpha(p[i + 1]) || p[i + 1] == '_')))
	)
	{
		 if(p[i] == '|')
			*v = PIPE;
		else if(p[i] == ' ')
			*v = SPACE;
		else if(p[i] == '\'')
			*v = SQUOTES;
		else if(p[i] == '"')
			*v = QUOTES;
		else if(p[i] == '>')
		{
			if (p[i + 1] && p[i + 1] == '>')
			{
				*v = APPEND;
				return(2);
				
			}
			*v = REDIRECT;
			return(1);
		}
		else if(p[i] == '<')
		{
			if (p[i + 1] && p[i + 1] == '<')
			{
				*v = HERDOCK;
				return(2);
			}
			*v = REDIRECT_IN;
		}
		else if(p[i] == 9 || p[i] == 11 )
		{
			*v = TAB;
			return(1);
		}
		else if (p[i] == '$' && (p[i + 1] && !(p[i + 1] >= '0' && p[i + 1] <= '9')))
		{
			i++;
			counter++;
			while(p[i] && (ft_isalnum(p[i]) || p[i]=='_'))
			{
				counter++;
				i++;
			}
			*v = VARIABLE;
			return (counter);
		}
		return(1);
	}
	if(p[i] == '$' && (p[i + 1] && p[i + 1] == '?'))
	{
		*v = EXIT_STATUS;
		return (2);
	}
	if(p[i] == '$')
	{
		*v = WORD;
		return (2);
	}
	while (p[i] && !(p[i] == '"' ||p[i] == '|' || p[i] == '<' || p[i] == '>' || p[i] == '\'' || p[i] == ' ' || p[i] == 9 || p[i] == 11 || p[i] == '$'))
	{
		*v = WORD;
		counter++;
		i++;
	}
	return(counter);
}

char *cp(char *p, int lent, int *s)
{
	char *c;
	int i;
	i = 0;
	c = malloc(sizeof(char) * lent + 1);
	while(p[*s] && i < lent)
	{
		c[i] = p[*s];
		*s = *s + 1;	
		i++;
	}
	c[i] = 0;
	return(c);
}

void split_parse(char *p,t_command_d	**t)
{
	int i;
	char *s;
	int v;
	i = 0;
	while (p[i])
	{
		v = 0;
		s = 0;
		s = cp(p, ft_strlen_m(p, i, &v), &i);
		
		fifo(t, s, v);
		
	}
	free(p);

}
char* split_parse_2(char *p,t_command_d	**t,int state)
{
	int i;
	char *s;
	int v;
	i = 0;
	while (p[i])
	{
		v = 0;
		s = 0;
		s = cp(p, ft_strlen_m(p, i, &v), &i);
		if(v == REDIRECT || v == REDIRECT_IN || v == HERDOCK || v == PIPE || v == APPEND)
		{
			
			fifo_2(t, s, v, SSQUOTES);
			// printf("%s  %d",s,SSQUOTES);
		}
		else
		{
			printf("what");
			fifo_2(t,s, v, state);
		}
	}
	return(s);
}
void put_state(t_command_d	*t, int state, int nbr, int *dsquotes)
{
	t->state = state;
	*dsquotes = nbr;
}
void detect_state(t_command_d	*t)
{
	int BDQUOTES;
	int BSQUOTES;
	
	BDQUOTES = 0;
	BSQUOTES = 0;
	while(t)
	{
		if(t->content[0] == '\'' && BSQUOTES == 0 && BDQUOTES != 1)
			put_state(t, GENERALE, 1, &BSQUOTES);
		else if(t->content[0] == '"' && BDQUOTES == 0 && BSQUOTES != 1)
			put_state(t, GENERALE, 1, &BDQUOTES);
		else if(t->content[0] == '\'' && BSQUOTES == 1)
			put_state(t, GENERALE, 0, &BSQUOTES);
		else if(t->content[0] == '"' && BDQUOTES == 1)
			put_state(t, GENERALE, 0, &BDQUOTES);
		else if(t->content[0] != '\'' && BSQUOTES == 1)
	
			t->state = SSQUOTES;
		else if(t->content[0] != '"' && BDQUOTES == 1)
			t->state = SDQUOTES;
		else
			t->state = GENERALE;
		t = t->next;
	}
}

int	DETECT_QUOTES2(t_command_d *t, int *exit_s)
{
	int D_QUOTES;
	int S_QUOTES;
	
	D_QUOTES = 0;
	S_QUOTES = 0;
	while(t)
	{
		if(t->token == QUOTES && S_QUOTES == 0)
		{
			D_QUOTES++;
			if(!(D_QUOTES%2))
				D_QUOTES = 0;
		}
		else if(t->token == SQUOTES && D_QUOTES == 0)
		{
			S_QUOTES++;
			if(!(S_QUOTES%2))
				S_QUOTES = 0;
		}
		t = t->next;
	}
	
	if(!D_QUOTES && !S_QUOTES)
	{
		*exit_s = 0;
		return(1);
	}
	*exit_s = 1;
	return(0);
}
int		DETECT_QUOTES(t_command_d	*t, int *exit_s)
{
	int D_QUOTES;
	int S_QUOTES;
	
	D_QUOTES = 0;
	S_QUOTES = 0;
	while (t)
	{
		if(t->state == SDQUOTES && D_QUOTES == 0 && S_QUOTES == 0)
			D_QUOTES = 1;
		else if(t->state == GENERALE && D_QUOTES == 1)
			D_QUOTES = 0;
		else if(t->state == SSQUOTES && D_QUOTES == 0 && S_QUOTES == 0)
			S_QUOTES = 1;
		else if(t->state == GENERALE && S_QUOTES == 1)
			S_QUOTES = 0;				
		t = t->next;
	}
	if(D_QUOTES || S_QUOTES)
	{
		*exit_s = 0;
		return(1);
	}
	*exit_s = 1;
	return(0);
	
}

int test(t_command_d	*t)
{
	int i;
	int token_t[5];
	
	i = 0;
	token_t[0] = PIPE;
	token_t[1] = APPEND;
	token_t[2] = REDIRECT;
	token_t[3] = HERDOCK;
	token_t[4] = REDIRECT_IN;
	while(i < 5)
	{
		if(token_t[i] == t->token)
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
int pipe_red_test(t_command_d	*t, int SEARCH, int *exit_s)
{
	int		b_pipe;
	int		ex_word;
	int		existing_pipe;
	
	init_pipe_red(&ex_word, &b_pipe, &existing_pipe);
	if (!count(t, PIPE))
	{
		*exit_s = 0;
		return(1);
	}
	while (t)
	{
		// if(existing_pipe >= 1 && test(t))
		// {
		// 	*exit_s = 258;
		// 	return(0);
		// }
		if ((t->token == QUOTES || t->token == SQUOTES || t->token == WORD || t->token == VARIABLE) && ex_word == 0)
			increment_init(&existing_pipe, &ex_word, &b_pipe);
		else if(t->token == SEARCH && t->state != SDQUOTES && t->state != SSQUOTES ) 
		{
			existing_pipe = 1;
			ex_word = 0;
			b_pipe--;
		}
		t = t->next;
	}
	if (b_pipe >= 1)
	{
		*exit_s = 0;
		return(1);
	}
	*exit_s = 1;
	return(0);
}

// int		pipe_search(t_command_d	*t, int SEARCH, int *exit_s)
// {
// 	int		f_pipe;
	
// 	f_pipe = 0;
// 	while (t)
// 	{
		
// 		t = t->next;
// 	}
// 	return (0);
// }	

int herdock_pos(t_command_d	*t, int search)
{
	int pos;
	
	pos = 1;
	while (t)
	{
		if (t->token == search)
			return(pos);
		pos++;
		t = t->next;	
	}
	return (0);
}




int herdock_redirect_test(t_command_d	*t ,int search,int *exit_s)
{
	int		b_herdock;
	int		ex_word;
	int		pos;
	int		c_red_herdock;
	
	pos = 0;
	c_red_herdock = count(t, search);
	ex_word = 0;
	b_herdock = 0;
	if(c_red_herdock == 0)
	{
		*exit_s = 0;
		return(1);
	}
	while (t)
	{
		if(b_herdock >= 1 && test(t))
		{
			*exit_s = 258;
			return(0);
		}
		if(t->token == search && t->state == GENERALE)
			b_herdock++;
		if((t->token == QUOTES || t->token == SQUOTES ||t->token == WORD || t->token == VARIABLE || t->token == EXIT_STATUS)&& b_herdock >= 1) 	
			b_herdock--;
		t = t->next;
	}
	if(b_herdock == 0)
	{
		*exit_s = 0;
		return(1);
	}
	*exit_s = 258;
	return(0);
	
}
void	free_nodes(t_command_d *t)
{
	t_command_d		*s;
	
	while(t)
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
char* find(t_command_d	*t, t_env	*enva)
{
	while(enva)
	{
		
		if(ft_strcmp_(t->content ,enva->variable) == 0)
			return (strdup(enva->value));
		enva = enva->next;	
	}
	return(NULL);
}
void init_expend(int *previous, int *previoush)
{
	*previous = 0;
	*previoush = 0;
}


void	free_token(t_command_d	*t)
{
	t_command_d *tmp;

	while(t)
	{
		tmp = t->next;
		free(t->content);
		free(t);
		t = tmp;
	}
}

t_command_d	*	expend(t_command_d	*t, t_env	*enva)
{
	char *s;
	// int	pred;
	int previoush;
	int previous;
	t_command_d		*tmp;
	t_command_d		*tcp;
	int 	inside;
	
	tcp = 0;
	int i;
	i = 0;
	tmp = t;
	init_expend(&previous, &previoush);
	while(t)
	{
		inside = 0;
		if(t->token == HERDOCK && t->state == GENERALE)
		{
			fifo_2(&tcp, t->content, t->token, t->state);
			previoush = 1;
		}
		else if(t->token == VARIABLE && previoush == 0 && (t->state == SDQUOTES))
		{
			s = 0;
			s = find(t, enva);
			if(s)
			{
				free(t->content);
				t->content = ft_strdup(s);
			}
			else
			{
				free(t->content);
				t->content = calloc(1, 1);
			}
			fifo_2(&tcp, t->content, t->token, SDQUOTES);
		}
		else if(t->token == VARIABLE && previoush == 0 && (t->state == GENERALE))
		{
			s=0;
			s = find(t, enva);
			if(s)
				split_parse_2(s, &tcp, GENERALE);
			else
				fifo_2(&tcp, "", t->token, GENERALE);
		}
		else if(previoush == 1)
		{
			
			while(t && ((t->token == TAB && t->state == GENERALE ) || (t->token == SPACE && t->state == GENERALE)))
			{
				
				inside = 1;
				fifo_2(&tcp, t->content, t->token, t->state);
				t = t->next;
			}
			while(t && (!(t->token == TAB && t->state == GENERALE ) && !(t->token == SPACE && t->state == GENERALE)))
			{
				previoush = 0;
				inside = 1;
				fifo_2(&tcp, t->content, t->token, t->state);
				t = t->next;
			}
		}
		else
			fifo_2(&tcp, t->content, t->token, t->state);
		i++;
		if(t && inside == 0)
			t = t->next;	
	}
	free_token(tmp);
	return (tcp);
}

void	expend_exit(t_command_d	*t, int exit_s)
{
	int previoush;
	int inside;

	previoush = 0;
	// init_expend(&previous, &previoush);
	while(t)
	{
		inside = 0;
		if(t->token == HERDOCK && t->state == GENERALE)
			previoush = 1;
		else if(previoush == 1 && t->token != SPACE && t->token != TAB)
		{
			while(t && (!(t->token == SPACE && t->state == GENERALE) && !(t->token == TAB && t->state == GENERALE)))
			{
				inside = 1;
				previoush = 0;
				t = t->next;
			}
		}
		else if(previoush == 0 && (t->token == EXIT_STATUS && (t->state == GENERALE || t->state == SDQUOTES)))
		{
			free(t->content);
			t->content = ft_strdup(ft_itoa(exit_s));
		}
		if(t && !inside)
			t = t->next;
	}
}

/// @brief 
/// @param argc 
/// @param argv 
/// @param envp 
/// @return 

// void herdok()
// {
	
// }
void free_files(t_pcommand_d	*p)
{
	t_file *file;
	
	while (p->file)
	{
		free(p->file->file_name);
		free(p->file);
		file = p->file->next;
		p->file=file;
	}
}
void	free_cmd_files(t_pcommand_d	*p)
{
	t_pcommand_d	*tmp;
	int 			i;
	
	while (p)
	{
		i = 0;
		while (p->command[i])
		{
			free (p->command[i]);
			i++;	
		}
		// free(p->command);
		// if(p->file)
		// 	free_files (p);
		tmp = p->next;
		p = tmp;
	}
}
int		main(int argc, char* argv[], char* envp[])
{
	int 			exit_s;
	int 			exit_p;
	char			*read;
	t_command_d		*t;
	t_pcommand_d	*p;
	t_env	* enva;
	
	p = 0;
	exit_p = 0;
	exit_s = 0;
	(void)argc;
	(void)argv;
	Glob.env = __fill_env(envp);
	enva = __fill_env(envp);
	while (1)
	{
		t = 0;
		
		read = readline("minishell> ");
		
		if (!read)
			exit(0);
		add_history(read);
		split_parse(read, &t);
		
		detect_state(t);
		exit_p = exit_s;
		if(DETECT_QUOTES2(t, &exit_s) && herdock_redirect_test(t, REDIRECT_IN,&exit_s) && herdock_redirect_test(t, REDIRECT, &exit_s) &&
		herdock_redirect_test(t, REDIRECT_IN, &exit_s) && herdock_redirect_test(t, APPEND, &exit_s) && herdock_redirect_test(t, HERDOCK, &exit_s) && pipe_red_test(t , PIPE,&exit_s))
		{
			
			// printf("	content		|	token	|	state	\n");
			// printf("	______________________________________________\n");
			p = 0;
			t = expend(t, enva);
			expend_exit(t, exit_p);
			
			// while(t)
			// {
			// 	printf("%s     %d     %d\n",t->content,t->token,t->state);
			// 	t = t->next;
			// }
				
			parse_200(t, &p);
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
		// 	printf("--------------file-------------\n");	
		// 		while(p->file)
		// 		{
		// 			printf("%s    %d  %d\n",p->file->file_name,p->file->type,p->file->state);
		// 			p->file= p->file->next;	
		// 		}
		// 	printf("--------------next cmd---------\n");	
		// 	p = p->next;
		// }
		free_cmd_files(p);
			// free_cmd_files(p);
			// if (check_builts(p->command[0]))
			// 	do_builtins(p->command);
			// else
			// 	do_command(p, &exit_s);
		}
		else
			write(2,"Syntax error\n",13);
	}
	return (0);
}

