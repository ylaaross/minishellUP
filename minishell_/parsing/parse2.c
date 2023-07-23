/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 18:13:10 by ylaaross          #+#    #+#             */
/*   Updated: 2023/07/22 15:41:54 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>
#include "../minishell.h"

t_file	*fifo_file(t_file *head, char* str, int v,int state)
{
	t_file	*t;

	t = 0;
	if (head == 0)
	{
		head = malloc(sizeof(t_file));
		head->file_name = ft_strdup(str);
		head->state = state;
		head->type = v;
		head->next = 0;
	}
	else
	{
		t = head;
		while (t->next)
			t = t->next;
		t->next = malloc(sizeof(t_file));
		t->next->file_name = ft_strdup(str);
		t->next->type = v;
		t->next->state = state;
		t->next->next = 0;
	}
	return (head);
}

int	test2(t_command_d	*t)
{
	int	i;
	int	token_t[4];

	i = 0;
	if (t)
	{
		token_t[0] = APPEND;
		token_t[1] = REDIRECT;
		token_t[2] = HERDOCK;
		token_t[3] = REDIRECT_IN;
		while (i < 4)
		{
			if (token_t[i] == t->token)
				return (1);
			i++;
		}
	}
	return (0);
}

int	detect_token(t_command_d	*t)
{
	int	i;
	int	token_t[4];

	i = 0;
	token_t[0] = APPEND;
	token_t[1] = REDIRECT;
	token_t[2] = HERDOCK;
	token_t[3] = REDIRECT_IN;
	while (i < 4)
	{
		if (token_t[i] == t->token)
			return (t->token);
		i++;
	}
	return (0);
}

int	command_number(t_command_d *t)
{
	int	b;
	int	count;

	count = 0;
	b = 1;
	while (t)
	{
		if (t->token == PIPE)
			b = 1;
		else if (t->token != PIPE && b == 1)
		{
			b = 0;
			count++;
		}
		t = t->next;
	}
	return (count);
}

char	*ft_strjoin_parse(char *s1, char *s2)
{
	size_t		ls1;
	size_t		ls2;
	int			i;
	char		*p;
	int			j;

	p = 0;
	i = -1;
	j = 0;
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	p = (char *)malloc(ls1 + ls2 + 1);
	if (p == 0)
	{
		free(s1);
		return (0);
	}
	while (s1[++i])
		p[i] = s1[i];
	p[i] = 0;
	while (s2[j])
	p[i++] = s2[j++];
	p[i] = 0;
	free(s1);
	return (p);
}

void command_mallocate(t_command_d *t , t_pcommand_d **p)
{
	int 		i;
	int		npipe;

	i = 0;
	npipe	= command_number(t);
	while(i < npipe)
	{
		fifo_cmd(p);
		i++;
	}
}
void pass_pipe(t_command_d **t)
{
	while (*t && (*t)->token != PIPE)
		*t = (*t)->next;
	*t = (*t)->next;
}
void commande_per_pipe(t_command_d *t , t_pcommand_d *p)
{
	int 	i;
	int 	npipe;

	npipe	= command_number(t);
	i = 0;
	while(i < npipe)
	{
		p->command = calloc((count_words(t) + 1), sizeof(char*));
		if (i < npipe - 1)
		{
			p = p->next;
			pass_pipe(&t);
		}
		i++;
	}
}

void parse_127(t_command_d *t, t_pcommand_d *p)
{
	int		i;
	char	*s;
	int		token;
	int		state;

	i = 0;

	while (t)
	{
		if((t && t->token == QUOTES && t->state == GENERALE) && 
		(t->next && t->next->token == QUOTES && t->next->state == GENERALE) &&
		((t->next->next && t->next->next->token == SPACE && t->next->next->state == GENERALE) || 
		!(t->next->next))
		)
		{
			p->command[i] = malloc(sizeof(char));
			p->command[i][0] = '\0';
			t = t->next;
			t = t->next;
			i++;
		}
		if (t && !(test2(t) && t->state == GENERALE)  &&  !(t->token == SPACE && t->state == GENERALE) 
			&& !(t->token == TAB && t->state == GENERALE) && !(t->token == PIPE && t->state == GENERALE)) 
		{
			p->command[i] = calloc(1, sizeof(char));
			while (t && !((t->token == SPACE || t->token == TAB) && t->state == GENERALE) && !(t->token == PIPE && t->state == GENERALE) && !(test2(t) && t->state == GENERALE))
			{
				
				if (t && (t->state == SSQUOTES || t->state == SDQUOTES 
				|| (t->token != SQUOTES && t->state == GENERALE) ||
				(t->token != QUOTES && t->state == GENERALE)
				)
				&&!(t->token == PIPE && t->state == GENERALE)
				&& !(t->token == QUOTES && t->state == GENERALE)
				&& !(t->token == SQUOTES && t->state == GENERALE))
					p->command[i] = ft_strjoin_parse(p->command[i], t->content);
				if (t)
					t = t->next;
			}
			i++;
			p->command[i] = 0;
		}
		if (test2(t) && t->state == GENERALE)
		{
			while(test2(t))
			{
				state = 0;
				token = detect_token(t);
				t = t->next;
				while(t && (t->token == SPACE || t->token == TAB))
					t = t->next;
					s = calloc(1,sizeof(char));
					while (t && !((t->token == SPACE || t->token == TAB) && t->state == GENERALE) && !(test2(t) && t->state == GENERALE) && t->token != PIPE )
						{
							if(t->token == QUOTES || t->token == SQUOTES)  	
								state = 1;
						if (t && (t->state == SSQUOTES || t->state == SDQUOTES 
						|| (t->token != SQUOTES && t->state == GENERALE) ||
						(t->token != QUOTES && t->state == GENERALE))
						&&!(t->token == PIPE && t->state == GENERALE)
						&& !(t->token == QUOTES && t->state == GENERALE)
						&& !(t->token == SQUOTES && t->state == GENERALE))
						{
							s = ft_strjoin_parse(s, t->content);
						}
						if(t)
						t = t->next;
					}
				p->file = fifo_file(p->file, s, token, state);
			}
		}
		if(t && t->token == PIPE)
		{
			i = 0;
			p = p->next;
		
		}
		if (t)
			t = t->next;
	}
	
}

void parse_200(t_command_d *t, t_pcommand_d **p)
{
	command_mallocate(t, p);
	commande_per_pipe(t, *p);
	parse_127(t, *p);
}