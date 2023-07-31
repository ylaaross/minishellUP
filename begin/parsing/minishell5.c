/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:25:15 by ylaaross          #+#    #+#             */
/*   Updated: 2023/08/01 00:10:08 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	while_herdock(t_command_d	*t, int search, int *b_herdock)
{
	while (t)
	{
		if (*b_herdock >= 1 && test(t))
		{
			g_lob.exit_status = 258;
			return (0);
		}
		if (t->token == search && t->state == GENERALE)
			*b_herdock = *b_herdock + 1;
		if ((t->token == QUOTES || t->token == SQUOTES || t->token == WORD
				||t->token == VARIABLE || t->token == EXIT_STATUS)
			&& *b_herdock >= 1)
			*b_herdock = *b_herdock - 1;
		t = t->next;
	}
	return (1);
}

int	herdock_redirect_test(t_command_d	*t, int search)
{
	int		b_herdock;
	int		pos;
	int		c_red_herdock;

	c_red_herdock = count(t, search);
	initialise_her_var(&pos, &b_herdock);
	if (c_red_herdock == 0)
		return (1);
	if (!while_herdock(t, search, &b_herdock))
		return (0);
	if (b_herdock == 0)
		return (1);
	g_lob.exit_status = 2;
	return (0);
}

void	free_nodes(t_command_d	*t)
{
	t_command_d		*s;

	while (t)
	{
		s = t->next;
		free(t);
		t = s;
	}	
}

int	ft_strcmp_(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*cs1;
	unsigned char	*cs2;

	cs1 = (unsigned char *) s1;
	cs2 = (unsigned char *) s2;
	i = 0;
	while (cs1[i + 1] || cs2[i])
	{
		if (cs1[i + 1] != cs2[i])
			return (cs1[i + 1] - cs2[i]);
		i++;
	}
	return (0);
}

char	*find(t_command_d	*t, t_env	*enva)
{
	while (enva)
	{
		if (ft_strcmp_(t->content, enva->variable) == 0)
			return (strdup(enva->value));
		enva = enva->next;
	}
	return (NULL);
}
