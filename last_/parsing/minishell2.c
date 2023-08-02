/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:02:36 by ylaaross          #+#    #+#             */
/*   Updated: 2023/07/31 18:30:52 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_status_test(char *p, int i, int *v)
{
	if (p[i] == '$' && (p[i + 1] && p[i + 1] == '?'))
	{
		*v = EXIT_STATUS;
		return (2);
	}
	return (0);
}

int	special_char_cases(char *p, int i, int counter, int *v)
{
	if (test_special_char(p, i))
	{
		if (p[i] == '|')
			*v = PIPE;
		else if (p[i] == ' ')
			*v = SPACE;
		else if (p[i] == '\'')
			*v = SQUOTES;
		else if (p[i] == '"')
			*v = QUOTES;
		else if (p[i] == '>')
			return (test_red_out_app(p, i, v));
		else if (p[i] == '<')
		{
			if (test_red_int_her(p, i, v))
				return (test_red_int_her(p, i, v));
		}
		else if (p[i] == 9 || p[i] == 11)
			test_tab(v);
		else if (p[i] == '$' && (p[i + 1]
				&& !(p[i + 1] >= '0' && p[i + 1] <= '9')))
			return (variable_test(i, counter, v, p));
		return (1);
	}
	return (0);
}

int	ft_strlen_m(char *p, int i, int *v)
{
	int	counter;

	counter = 0;
	if (special_char_cases(p, i, counter, v))
		return (special_char_cases(p, i, counter, v));
	if (exit_status_test(p, i, v))
		return (exit_status_test(p, i, v));
	if (dollar_test(p, i, v))
		return (dollar_test(p, i, v));
	ft_strlen_word(i, v, &counter, p);
	return (counter);
}

char	*cp(char *p, int lent, int *s)
{
	char		*c;
	int			i;

	i = 0;
	c = malloc(sizeof(char) * lent + 1);
	while (p[*s] && i < lent)
	{
		c[i] = p[*s];
		*s = *s + 1;
		i++;
	}
	c[i] = 0;
	return (c);
}

int	var_digit(char *str)
{
	int		i;
	char	t[3];

	t[0] = '$';
	t[1] = '0';
	t[2] = 0;
	i = 0;
	while (t[1] <= '9')
	{
		if (!strcmp(t, str))
			return (1);
		t[1] = t[1] + 1;
	}
	return (0);
}
