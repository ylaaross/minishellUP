/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 22:49:05 by ylaaross          #+#    #+#             */
/*   Updated: 2023/07/31 18:31:21 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	command_mallocate(t_command_d *t, t_pcommand_d **p)
{
	int			i;
	int			npipe;

	i = 0;
	npipe = command_number(t);
	while (i < npipe)
	{
		fifo_cmd(p);
		i++;
	}
}

void	pass_pipe(t_command_d **t)
{
	while (*t && (*t)->token != PIPE)
		*t = (*t)->next;
	*t = (*t)->next;
}

void	commande_per_pipe(t_command_d *t, t_pcommand_d *p)
{
	int		i;
	int		npipe;

	npipe = command_number(t);
	i = 0;
	while (i < npipe)
	{
		p->command = calloc((count_words(t) + 1), sizeof(char *));
		if (i < npipe - 1)
		{
			p = p->next;
			pass_pipe(&t);
		}
		i++;
	}
}

int	double_singlecotes(t_command_d *t)
{
	if ((t && t->token == QUOTES && t->state == GENERALE)
		&& (t->next && t->next->token == QUOTES && t->next->state == GENERALE)
		&& ((t->next->next && t->next->next->token == SPACE
				&& t->next->next->state == GENERALE)
			||!(t->next->next)))
		return (1);
	return (0);
}

int	content_to_parse(t_command_d *t)
{
	if (t && (t->state == SSQUOTES || t->state == SDQUOTES
			|| (t->token != SQUOTES && t->state == GENERALE)
			|| (t->token != QUOTES && t->state == GENERALE))
		&&!(t->token == PIPE && t->state == GENERALE)
		&& !(t->token == QUOTES && t->state == GENERALE)
		&& !(t->token == SQUOTES && t->state == GENERALE))
		return (1);
	return (0);
}
