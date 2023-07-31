/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:20:55 by ylaaross          #+#    #+#             */
/*   Updated: 2023/08/01 00:16:44 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_pipe_red(int *ex_word, int *b_pipe, int *existing_pipe)
{
	*ex_word = 0;
	*b_pipe = 0;
	*existing_pipe = 0;
}

void	increment_init(int *existing_pipe, int *ex_word, int *b_pipe)
{
	*existing_pipe = 0;
	*ex_word = 1;
	*b_pipe = *b_pipe + 1;
}

int	pipe_red_test(t_command_d	*t, int SEARCH)
{
	int		b_pipe;
	int		ex_word;
	int		existing_pipe;

	init_pipe_red(&ex_word, &b_pipe, &existing_pipe);
	if (!count(t, PIPE))
		return (1);
	while (t)
	{
		if ((t->token == QUOTES || t->token == SQUOTES || t->token == WORD
				|| t->token == VARIABLE) && ex_word == 0)
			increment_init(&existing_pipe, &ex_word, &b_pipe);
		else if (t->token == SEARCH && t->state != SDQUOTES
			&& t->state != SSQUOTES)
		{
			existing_pipe = 1;
			ex_word = 0;
			b_pipe--;
		}
		t = t->next;
	}
	if (b_pipe >= 1)
		return (1);
	g_lob.exit_status = 2;
	return (0);
}

int	herdock_pos(t_command_d	*t, int search)
{
	int	pos;

	pos = 1;
	while (t)
	{
		if (t->token == search)
			return (pos);
		pos++;
		t = t->next;
	}
	return (0);
}

void	initialise_her_var(int *pos, int *b_herdock)
{
	*pos = 0;
	*b_herdock = 0;
}
