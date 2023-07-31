/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:38:51 by ylaaross          #+#    #+#             */
/*   Updated: 2023/08/01 00:06:56 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	two_functions(t_command_d	**t, t_command_d	**tcp,
	int *inside, int *previoush)
{
	tab_space(t, tcp, inside);
	else_tab(previoush, inside, t, tcp);
}

void	expend_p1(t_command_d	**t, int *previoush,
	t_command_d	**tcp, int *inside)
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
		two_functions(t, tcp, inside, previoush);
	else
		fifo_2(tcp, (*t)->content, (*t)->token, (*t)->state);
}

t_command_d	*expend(t_command_d	*t)
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
