/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:54:51 by ylaaross          #+#    #+#             */
/*   Updated: 2023/07/31 18:30:50 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	variable_test(int i, int counter, int *v, char *p)
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

void	ft_strlen_word(int i, int *v, int *counter, char *p)
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
