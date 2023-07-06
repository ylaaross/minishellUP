#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>
#include "Minishell.h"

int ft_strlen(char *s1)
{
	int i;

	i = 0;
	while(s1[i])
		i++;
	return(i);
}
char	*ft_strjoin(char *s1, char *s2)
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
	if (!p)
		return (0);

	while (s1[++i])
		p[i] = s1[i];
	p[i] = 0;
	while (s2[j])
	p[i++] = s2[j++];
	p[i] = 0;
	// if (s1)
		free(s1);
	return (p);
}

void parse(t_command_d *t, t_pcommand_d **p)
{
	char	*s;
	int		number_alloc;
	int		npipe;
	int		i;

	i = 0;
	npipe = 0;
	number_alloc = count_words(t);

	fifo_cmd(p, 1);
	// fifo_cmd(p, 1);
	(*p)->command = malloc(sizeof(char*) * number_alloc + 1);
	while (t)
	{
		if(t->token == WORD)
		{
			s = t->content;
			
		}
		else if(t->token == QUOTES)
		{
			printf("lbts");
			if(t->next && t->next->state == SDQUOTES)
			{
				printf("talo9i");
				if(t->next)
					t = t->next;
				(*p)->command[i] = calloc(1, sizeof(char));
				while(t && t->state == SDQUOTES)
				{
					(*p)->command[i] = ft_strjoin((*p)->command[i], t->content);
					t = t->next;
				}
				i++;
				(*p)->command[i] = 0;
			}
		}
		else if(t->token == SQUOTES)
		{
			printf("lbts");
			if((t->next && t->next->state == SSQUOTES ))
			{
				printf("talo9i");
				t = t->next;
				(*p)->command[i] = calloc(1, 1);
				while(t && t->state == SSQUOTES)
				{
					(*p)->command[i] = ft_strjoin((*p)->command[i], t->content);
					
					t = t->next;
				}
				i++;
				(*p)->command[i] = 0;
			}
			else if(t->next && t->next->token == QUOTES)
			{
				(*p)->command[i] = malloc(sizeof(char) *1);
				(*p)->command[i] = 0;
			}
		}
		else if(t && t->token == PIPE)
		{
			printf("pipepppppppp\n");
			// number_alloc = count_words(t);
			fifo_cmd(p, 1);
			(*p) = (*p)->next;

			i = 0;
		}
			t = t->next;
	}
}
int command_number(t_command_d *t)
{
	int b;
	int count;

	count = 0;
	b = 1;
	while (t)
	{
		if(t->token == PIPE)
		{
			b = 1;
		}
		else if(t->token != PIPE && b == 1)
		{
			b = 0;
			count++;
		}
		t = t->next;
	}
	return (count);
}
void pass_pipe(t_command_d **t)
{
	while (*t && (*t)->token != PIPE)
		*t = (*t)->next;
	*t = (*t)->next;
}
void command_mallocate(t_command_d *t , t_pcommand_d **p)
{
	int 		i;
	int		npipe;

	i = 0;
	npipe	= command_number(t);
	while(i < npipe)
	{
		fifo_cmd(p , 1);
		i++;
	}
}
void commande_per_pipe(t_command_d *t , t_pcommand_d *p)
{
	int 	i;
	int 	npipe;

	npipe	= command_number(t);
	i = 0;
	while(i < npipe)
	{
		printf("||%d||",count_words(t));
		p->command = malloc(sizeof(char*) * (count_words(t) + 1));
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
	int i;

	i = 0;
	while (t)
	{
		if (t && t->token == WORD && t->state != SDQUOTES)
		{
			p->command[i] = t->content;
			i++;
			p->command[i] = 0;
		}
		else if (t && t->token == QUOTES)
		{
			p->command[i] = calloc(1,sizeof(char));
			while (t && !(t->token == SPACE && t->state == GENERALE))
			{
				if (t && t->token != QUOTES)
				{
							
					p->command[i] = ft_strjoin(p->command[i], t->content);
				}
				if(t)
				t = t->next;
			}
			i++;
			p->command[i] = 0;
		}
		else if(t->token == PIPE)
		{
			printf("%d",t->token);
			p = p->next;
			i = 0;
		}
		if (t)
			t = t->next;
		}
}
void parse_200(t_command_d *t, t_pcommand_d **p)
{
	command_mallocate(t, p);
	commande_per_pipe(t, *p);
	parse_127(t,*p);
}


void parse_129(t_command_d *t, t_pcommand_d **p)
{
	char	*s;
	int		number_alloc;
	int		npipe;
	int		enter;
	int		i;
	t_pcommand_d *cpl;

	i		= 0;
	enter	= 0;
	npipe	= command_number(t);
	while (i < npipe)
	{
		fifo_cmd(p , 1);
		(*p)->command = malloc(sizeof(char) * (count_words(t) + 1));
		if (i < npipe - 1)
		{
			(*p) = (*p)->next;
			pass_pipe(&t);
		}
		i++;
	}

	i = 0;
	while (t)
	{
		if (t && t->token == WORD && t->state != SDQUOTES)
		{
			(*p)->command[i] = t->content;
			i++;
			(*p)->command[i] = 0;
		}
		else if (t->token == QUOTES)
		{
			(*p)->command[i] = calloc(1, 1);
			while (t && !(t->token == SPACE && t->state == GENERALE))
			{
				if (t && t->token != QUOTES)
				{
							
					(*p)->command[i] = ft_strjoin((*p)->command[i], t->content);
				}
				if(t)
				t = t->next;
			}
			i++;
			(*p)->command[i] = 0;
		}
		else if(t->token == PIPE)
		{
			printf("    %s    ",(*p)->command[i]);
			printf("pipe");
			printf("%d",t->token);
			(*p) = (*p)->next;
		}
		if (t)
			t = t->next;
		}			
	}
