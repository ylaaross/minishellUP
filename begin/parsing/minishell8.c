/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell8.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:44:33 by ylaaross          #+#    #+#             */
/*   Updated: 2023/08/01 00:14:27 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	increment_expexit(t_command_d	**t, int *inside, int *previoush)
{
	*t = (*t)->next;
	*inside = 1;
	*previoush = 0;
}

void	expend_exit(t_command_d	*t)
{
	int		previoush;
	int		inside;

	previoush = 0;
	while (t)
	{
		inside = 0;
		if (t->token == HERDOCK && t->state == GENERALE)
			previoush = 1;
		else if (previoush == 1 && t->token != SPACE && t->token != TAB)
		{
			while (t && (!(t->token == SPACE && t->state == GENERALE)
					&& !(t->token == TAB && t->state == GENERALE)))
				increment_expexit(&t, &inside, &previoush);
		}
		else if (previoush == 0 && (t->token == EXIT_STATUS
				&& (t->state == GENERALE || t->state == SDQUOTES)))
		{
			free(t->content);
			t->content = ft_strdup(ft_itoa(g_lob.exit_status));
		}
		if (t && !inside)
			t = t->next;
	}
}

void	free_files(t_pcommand_d	*p)
{
	t_file		*file;

	while (p->file)
	{
		free(p->file->file_name);
		file = p->file->next;
		free(p->file);
		p->file = file;
	}
}

void	free_cmd_files(t_pcommand_d	*p)
{
	t_pcommand_d		*tmp;
	int					i;

	if (!p)
		return ;
	while (p)
	{
		i = 0;
		while (p->command[i])
		{
			free (p->command[i]);
			i++;
		}
		free(p->command);
		if (p->file)
			free_files (p);
		tmp = p->next;
		free (p);
		p = tmp;
	}
}

void	else_tab(int *previoush,
	int *inside, t_command_d	**t, t_command_d **tcp)
{
	while (*t && (! ((*t)->token == TAB && (*t)->state == GENERALE)
			&& !((*t)->token == SPACE && (*t)->state == GENERALE)))
	{
		*previoush = 0;
		*inside = 1;
		fifo_2(tcp, (*t)->content, (*t)->token, (*t)->state);
		(*t) = (*t)->next;
	}
}
