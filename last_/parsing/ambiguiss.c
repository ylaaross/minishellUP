/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguiss.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:32:35 by ylaaross          #+#    #+#             */
/*   Updated: 2023/08/03 00:32:45 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_a(char *s)
{
	int	i;
	int	space;
	int	count;

	count = 0;
	space = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && space)
		{
			space = 0;
			count++;
		}
		else if (s[i] == ' ')
			space = 1;
		i++;
	}
	return (count);
}

int	loop(t_command_d	**t)
{
	char	*c;

	while ((*t) && !((*t)->token == SPACE && (*t)->state == GENERALE))
	{
		c = 0;
		if ((*t) && (*t)->token == VARIABLE && (*t)->state == GENERALE)
		{
			c = find(*t, g_lob.env);
			if (c && ft_count_a(c) >= 2)
			{
				printf("minishell: ambiguous redirect\n");
				g_lob.exit_status = 1;
			}
			return (0);
		}
		if (t)
			(*t) = (*t)->next;
	}
	return (1);
}

int	test_ambiguiss(t_command_d	*t)
{
	int		red;
	char	*c;

	red = 0;
	c = 0;
	while (t)
	{
		if ((t->token == REDIRECT || t->token == REDIRECT_IN
				||t->token == APPEND) && t->state == GENERALE)
			red = 1;
		if (red == 1)
		{
			while (t && (t->token == SPACE && t->state == GENERALE))
				t = t->next;
			if (!loop(&t))
				return (0);
			red = 0;
		}
		if (t)
			t = t->next;
	}
	return (1);
}
