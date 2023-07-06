/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:14:30 by asaber            #+#    #+#             */
/*   Updated: 2023/06/21 20:46:23 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"
#include<stdio.h>
void	_ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*end;

	end = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
		while (end->next)
			end = end->next;
		end->next = new;
		new->next = NULL;
}

t_env	*_ft_lstnew(void *variable, void *value)
{
	t_env	*begin;

	begin = NULL;
	begin = (t_env *) malloc(sizeof(t_env));
	if (begin == 0)
		return (NULL);
	begin->variable = variable;
	begin->value = value;
	begin->next = NULL;
	return (begin);
}