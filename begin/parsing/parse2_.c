/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 23:58:24 by ylaaross          #+#    #+#             */
/*   Updated: 2023/08/01 00:01:44 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	test_cases_parse(t_command_d *t)
{
	if (t && !((t->token == SPACE || t->token == TAB)
			&& t->state == GENERALE)
		&& !(test2(t) && t->state == GENERALE) && t->token != PIPE)
		return (1);
	return (0);
}

void	parse_127(t_command_d *t, t_pcommand_d *p)
{
	int		i;
	char	*s;
	int		token;
	int		state;

	i = 0;
	while (t)
	{
		if (double_singlecotes(t))
			double_singlecotes_inside(&t, p, &i);
		kk(&t, p, &i);
		if (test2(t) && t->state == GENERALE)
		{
			while (test2(t))
			{
				state_token(&t, &state, &token);
				s = calloc(1, sizeof(char));
				while (test_cases_parse(t))
					join_parse_next(&t, &state, &s);
				p->file = fifo_file(p->file, s, token, state);
			}
		}
		pipe_next(&t, &p, &i);
	}
}

void	parse_200(t_command_d *t, t_pcommand_d **p, t_pcommand_d **tmp)
{
	command_mallocate(t, p);
	commande_per_pipe(t, *p);
	parse_127(t, *p);
	*tmp = *p;
}
