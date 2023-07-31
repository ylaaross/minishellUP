/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:28:31 by ylaaross          #+#    #+#             */
/*   Updated: 2023/08/01 00:13:27 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_expend(int *previous, int *previoush)
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

void	search(t_command_d	*t, t_env	*enva, t_command_d **tcp)
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

void	search2(t_command_d	*t, t_env	*enva, t_command_d **tcp)
{
	char	*s;

	s = 0;
	s = find(t, enva);
	if (s)
		split_parse_2(s, tcp, GENERALE);
	else
		fifo_2(tcp, "", t->token, GENERALE);
}

void	tab_space(t_command_d	**t, t_command_d **tcp, int *inside)
{
	while (*t && (((*t)->token == TAB && (*t)->state == GENERALE)
			|| ((*t)->token == SPACE && (*t)->state == GENERALE)))
	{
		*inside = 1;
		fifo_2(tcp, (*t)->content, (*t)->token, (*t)->state);
		*t = (*t)->next;
	}
}
