/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:43:57 by ylaaross          #+#    #+#             */
/*   Updated: 2023/07/09 17:51:09 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>
#include "minishell.h"

	// WORD = 1,
	// SPACE = 2,
	// ENV = 3,
	// PIPE = 4,
	// QUOTES = 5,
	// SQUOTES = 6,
	// APPEND = 7,
	// REDIRECT = 8,
	// VARIABLE = 9,
	// GENERALE = 10,
	// SDQUOTES = 11,
	// SSQUOTES = 12,
	// HERDOCK = 13,
	// REDIRECT_IN = 14,
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
	if(i == 1)
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
		
		if(t->token == SPACE && t->state == GENERALE)
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
	
	if(p[i] == '"' || p[i] == '|' || p[i] == '\'' || p[i] == ' '|| p[i] == '<' || p[i] == '>' || p[i] == 9 || p[i] == 11 || (p[i] == '$'  && (p[i + 1] && (!(p[i + 1] >= '0' && p[i + 1] <= '9') && p[i + 1] != '@' && p[i + 1] != '$' && p[i + 1] != '?'))))
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
			printf("ssss");
			i++;
			counter++;
			while(p[i] && !(p[i] == '$' ||p[i] == '"' ||p[i] == '|' || p[i] == '<' || p[i] == '>' || p[i] == '\'' || p[i] == ' ' || p[i] == '@'))
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
	while (p[i] && !(p[i] == '"' ||p[i] == '|' || p[i] == '<' || p[i] == '>' || p[i] == '\'' || p[i] == ' ' || p[i] == 9 || p[i] == 11))
	{
		if((p[i] == '$' && (p[i + 1] && !(p[i + 1] >= '0' && p[i + 1] <= '9')  && p[i + 1] != '$')))
			return(counter);
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

char* split_parse(char *p,t_command_d	**t)
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
		if ((t->token == QUOTES || t->token == SQUOTES ||t->token == WORD) && ex_word == 0)
			increment_init(&existing_pipe, &ex_word, &b_pipe);
		else if(t->token == SEARCH && t->state != SDQUOTES && t->state != SSQUOTES ) 
		{
			existing_pipe = 1;
			printf("%d",t->state);
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
	int 	h_pos;
	int		c_red_herdock;
		// printf("noo");
	pos = 0;
	c_red_herdock = count(t, search);
	ex_word = 0;
	b_herdock = 0;

	h_pos = herdock_pos(t, search);
	if(c_red_herdock == 0)
	{
		// printf("|MATGOLHACHE %d|",search); 
		*exit_s = 0;
		return(1);
	}
	while (t)
	{
		
	// if(b_herdock == 1 && test(t))
	// {
		
	// 	*exit_s = 258;
	// 	return(0);
	// }
	// else if (h_pos < pos && (t->token == WORD || t->token == QUOTES || t->token == SQUOTES) && ex_word == 0 )
	// {
	// 	*exit_s = 0;
	// 	return(1);
	// }
	// 	pos++;
		if(b_herdock >= 1 && test(t))
		{
			*exit_s = 258;
			return(0);
		}
		else if(t->token == search && t->state == GENERALE)
		{
			
			b_herdock++;
			printf("-%d-\n",b_herdock);
		}
		else if((t->token == QUOTES || t->token == SQUOTES ||t->token == WORD)&& b_herdock >= 1) 	
		{
			b_herdock--;
			printf("-%d-\n",b_herdock);
		}
		t = t->next;
	}
	if(b_herdock ==0)
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
			return (enva->value);
		enva = enva->next;	
	}
	return(NULL);
}
void init_expend(int *previous, int *previoush)
{
	*previous = 0;
	*previoush = 0;
}
void	expend(t_command_d	*t, t_env	*enva)
{
	char *s;
	
	int previoush;
	int previous ;
	
	init_expend(&previous, &previoush);
	while(t)
	{
		if(t->token == HERDOCK)
			previoush = 1;
		else if(previoush != 0 &&t->token != HERDOCK && (t->state != SDQUOTES || t->state != SSQUOTES))
		{
			previous = 1;
		}
		else if(t->token == SPACE && (t->state != SDQUOTES || t->state != SSQUOTES) && previous == 1)
			init_expend(&previous, &previoush);	
		else if(t->token == VARIABLE && previoush == 0 && (t->state == GENERALE || t->state == SDQUOTES))
		{
			s = find(t, enva);
			if(s)
				t->content = ft_strdup(find(t, enva));
			else
			{
				free(t->content);
				t->content = calloc(1, 1);
			}
		}
		t = t->next;
	}
}

void	expend_exit(t_command_d	*t, int exit_s)
{
	int previoush;
	int previous ;
	
	init_expend(&previous, &previoush);
	while(t)
	{
		if(t->token == HERDOCK)
			previoush = 1;
		else if(previoush != 0 && t->token != HERDOCK && (t->state != SDQUOTES || t->state != SSQUOTES))
		{
			previous = 1;
		}
		else if(t->token == SPACE && (t->state != SDQUOTES || t->state != SSQUOTES) && previous == 1)
			init_expend(&previous, &previoush);	
		else if(t->token == EXIT_STATUS && previoush == 0 && (t->state == GENERALE || t->state == SDQUOTES))
				t->content = ft_strdup(ft_itoa(exit_s));
		t = t->next;
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
	exit_s = 0;
	(void)argc;
	(void)argv;
	Glob.env = __fill_env(envp);
	while (1)
	{
		t = 0;
		
		read = readline("minishell> ");
		enva = __fill_env(envp);
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
		expend(t, enva);
		expend_exit(t, exit_p);
		parse_200(t, &p);
		// int i;
		// while (p)
		// {
			
		// 	i = 0;
		// 	printf("--------------cmd-------------\n");
		// 	while (p->command[i])
		// 	{
		// 		printf("||%s||\n",p->command[i]);
		// 		i++;	
		// 	}
		// 	printf("--------------file-------------\n");	
		// 		while(p->file)
		// 		{
		// 			printf("%s    %d\n",p->file->file_name,p->file->type);
		// 			p->file= p->file->next;	
		// 		}
		// 	printf("--------------next cmd-------------\n");	
		// 	p = p->next;
		// }
		do_command(p->command);
		}
	}
	return (0);
}

