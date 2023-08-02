/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 22:25:56 by ylaaross          #+#    #+#             */
/*   Updated: 2023/08/02 01:14:34 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_file	*fifo_file(t_file *head, char*str, int v, int state)
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
		free(str);
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
		free(str);
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
		if (t->token == PIPE && t->state == GENERALE)
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
