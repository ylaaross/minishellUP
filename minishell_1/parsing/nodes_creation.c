/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 23:22:28 by ylaaross          #+#    #+#             */
/*   Updated: 2023/07/29 23:46:48 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fifo_2(t_command_d **head, char *str, int v, int state)
{
	t_command_d	*t;

	t = 0;
	if (*head == 0)
	{
		*head = malloc(sizeof(t_command_d));
		(*head)->content = ft_strdup(str);
		(*head)->token = v;
		(*head)->state = state;
		(*head)->next = 0;
	}
	else
	{
		t = *head;
		while (t->next)
			t = t->next;
		t->next = malloc(sizeof(t_command_d));
		t->next->content = ft_strdup(str);
		t->next->token = v;
		t->next->state = state;
		t->next->next = 0;
	}
}

void	fifo(t_command_d **head, char *str, int v)
{
	t_command_d	*t;

	t = 0;
	if (*head == 0)
	{
		*head = malloc(sizeof(t_command_d));
		(*head)->content = str;
		(*head)->token = v;
		(*head)->next = 0;
	}
	else
	{
		t = *head;
		while (t->next)
			t = t->next;
		t->next = malloc(sizeof(t_command_d));
		t->next->content = str;
		t->next->token = v;
		t->next->next = 0;
	}
}

void	fifo_cmd(t_pcommand_d **head)
{
	t_pcommand_d	*t;

	t = 0;
	if (*head == 0)
	{
		*head = malloc(sizeof(t_pcommand_d));
		(*head)->file = 0;
		(*head)->next = 0;
	}
	else
	{
		t = *head;
		while (t->next)
			t = t->next;
		t->next = malloc(sizeof(t_pcommand_d));
		t->next->file = 0;
		t->next->next = 0;
	}
}