/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:14:04 by ylaaross          #+#    #+#             */
/*   Updated: 2023/08/01 00:07:24 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_state(t_command_d	*t,	int state, int nbr, int *dsquotes)
{
	t->state = state;
	*dsquotes = nbr;
}

void	detect_state(t_command_d	*t)
{
	int		bdquotes;
	int		bsquotes;

	bdquotes = 0;
	bsquotes = 0;
	while (t)
	{
		if (t->content[0] == '\'' && bsquotes == 0 && bdquotes != 1)
			put_state(t, GENERALE, 1, &bsquotes);
		else if (t->content[0] == '"' && bdquotes == 0 && bsquotes != 1)
			put_state(t, GENERALE, 1, &bdquotes);
		else if (t->content[0] == '\'' && bsquotes == 1)
			put_state(t, GENERALE, 0, &bsquotes);
		else if (t->content[0] == '"' && bdquotes == 1)
			put_state(t, GENERALE, 0, &bdquotes);
		else if (t->content[0] != '\'' && bsquotes == 1)
			t->state = SSQUOTES;
		else if (t->content[0] != '"' && bdquotes == 1)
			t->state = SDQUOTES;
		else
			t->state = GENERALE;
		t = t->next;
	}
}

void	count_quotes(int *quotes)
{
	*quotes = *quotes + 1;
	if (!(*quotes % 2))
		*quotes = 0;
}

int	detect_quotes2(t_command_d *t)
{
	int	d_quotes;
	int	s_quotes;

	d_quotes = 0;
	s_quotes = 0;
	while (t)
	{
		if (t->token == QUOTES && s_quotes == 0)
			count_quotes(&d_quotes);
		else if (t->token == SQUOTES && d_quotes == 0)
			count_quotes(&s_quotes);
		t = t->next;
	}
	if (!d_quotes && !s_quotes)
		return (1);
	g_lob.exit_status = 2;
	write(2, "minishell: syntax error\n", 24);
	return (0);
}

int	test(t_command_d	*t)
{
	int	i;
	int	token_t[5];

	i = 0;
	token_t[0] = PIPE;
	token_t[1] = APPEND;
	token_t[2] = REDIRECT;
	token_t[3] = HERDOCK;
	token_t[4] = REDIRECT_IN;
	while (i < 5)
	{
		if (token_t[i] == t->token)
			return (1);
		i++;
	}
	return (0);
}
