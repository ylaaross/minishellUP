/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   personalised_splites.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 23:27:44 by ylaaross          #+#    #+#             */
/*   Updated: 2023/07/31 18:31:30 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_parse(char *p, t_command_d	**t)
{
	int		i;
	char	*s;
	int		v;

	i = 0;
	while (p[i])
	{
		v = 0;
		s = 0;
		s = cp(p, ft_strlen_m(p, i, &v), &i);
		if (ft_strcmp(s, "$@") && !var_digit(s)
			&& ft_strcmp(s, "$*") && !(ft_strcmp(s, "$") == 0 && v == 22))
			fifo(t, s, v);
		else
			free(s);
	}
	free(p);
}

char	*split_parse_2(char *p, t_command_d	**t, int state)
{
	int		i;
	char	*s;
	int		v;

	i = 0;
	while (p[i])
	{
		v = 0;
		s = 0;
		s = cp(p, ft_strlen_m(p, i, &v), &i);
		if (v == REDIRECT || v == REDIRECT_IN
			|| v == HERDOCK || v == PIPE || v == APPEND)
			fifo_2(t, s, v, SSQUOTES);
		else
			fifo_2(t, s, v, state);
	}
	return (s);
}
