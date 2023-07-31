/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 22:55:11 by ylaaross          #+#    #+#             */
/*   Updated: 2023/07/31 23:54:16 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	content_file_parse(t_command_d *t)
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

void	double_singlecotes_inside(t_command_d **t, t_pcommand_d *p, int *i)
{
	p->command[*i] = malloc(sizeof(char));
	p->command[*i][0] = '\0';
	*t = (*t)->next;
	*t = (*t)->next;
	*i = *i + 1;
}

void	inside_parse(t_command_d **t, t_pcommand_d *p, int *i)
{
	p->command[*i] = calloc(1, sizeof(char));
	while ((*t) && !(((*t)->token == SPACE || (*t)->token == TAB)
			&& (*t)->state == GENERALE)
		&& !((*t)->token == PIPE && (*t)->state == GENERALE)
		&& !(test2((*t)) && (*t)->state == GENERALE))
	{
		if (content_to_parse((*t)))
			p->command[*i] = ft_strjoin_parse(p->command[*i], (*t)->content);
		if ((*t))
			(*t) = (*t)->next;
	}
	*i = *i + 1;
	p->command[*i] = 0;
}

void	pipe_(t_command_d *t, t_pcommand_d **p, int *i)
{
	if (t && t->token == PIPE)
	{
		*i = 0;
		*p = (*p)->next;
	}
}

void	next(t_command_d **t)
{
	if (*t)
		*t = (*t)->next;
}
