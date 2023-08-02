/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:14:30 by asaber            #+#    #+#             */
/*   Updated: 2023/08/01 17:37:20 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*search_env(char *var)
{
	t_env	*env;
	int		size;

	size = ft_strlen(var);
	env = g_lob.env;
	while (env)
	{
		if (!ft_strncmp(var, env->variable, size))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	list_len(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}
