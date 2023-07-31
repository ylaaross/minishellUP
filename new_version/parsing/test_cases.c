/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 23:29:51 by ylaaross          #+#    #+#             */
/*   Updated: 2023/07/29 23:46:55 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dollar_test(char *p, int i, int *v)
{
	if (p[i] == '$')
	{
		if (p[i + 1] && (p[i + 1] == '\'' || p[i + 1] == '"'))
		{
			*v = 22;
			return (1);
		}
		if (p[i + 1] && (p[i + 1] == '*'
				|| ft_isdigit(p[i + 1]) || p[i + 1] == '@'))
			return (2);
		*v = WORD;
		return (1);
	}
	return (0);
}

int	test_special_char(char *p, int i)
{
	if (p[i] == '"' || p[i] == '|' || p[i] == '\'' || p[i] == ' '
		|| p[i] == '<' || p[i] == '>' || p[i] == 9 || p[i] == 11
		|| (p[i] == '$' && (p[i + 1] && (ft_isalpha(p[i + 1])
					|| p[i + 1] == '_'))))
		return (1);
	return (0);
}

int	test_red_out_app(char *p, int i, int *v)
{
	if (p[i + 1] && p[i + 1] == '>')
	{
		*v = APPEND;
		return (2);
	}
	*v = REDIRECT;
	return (1);
}

int	test_red_int_her(char *p, int i, int *v)
{
	if (p[i + 1] && p[i + 1] == '<')
	{
		*v = HERDOCK;
		return (2);
	}
		*v = REDIRECT_IN;
	return (0);
}

int	test_tab(int *v)
{
	*v = TAB;
	return (1);
}
