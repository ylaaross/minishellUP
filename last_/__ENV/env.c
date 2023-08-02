/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:20:00 by asaber            #+#    #+#             */
/*   Updated: 2023/08/01 20:44:29 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minishell.h"

char	*cut_first(char *env)
{
	int		i;
	int		cnt;
	char	*first;

	cnt = 0;
	while (env[cnt] != '=' && env[cnt])
		cnt++;
	first = malloc(cnt + 1);
	i = 0;
	while (i < cnt)
	{
		first[i] = env[i];
		i++;
	}	
	first[i] = '\0';
	return (first);
}

char	*cut_secound(char *env, char *first_env)
{
	int		i;
	int		j;
	char	*sec;

	i = ft_strlen(first_env) + 1;
	sec = malloc(ft_strlen(env) - i + 1);
	j = 0;
	while (env[i])
	{
		sec[j] = env[i];
		i++;
		j++;
	}
	sec[j] = '\0';
	return (sec);
}

void	__edit_env(char *var, char *value)
{
	t_env	*env;
	int		size;

	size = ft_strlen(var);
	env = g_lob.env;
	if (value)
	{
		while (env)
		{
			if (!ft_strncmp(var, env->variable, size))
			{
				free(env->value);
				env->value = ft_strdup(value);
				if (value)
					env->status = 1;
				break ;
			}
			env = env->next;
		}
	}
}

void	init_status(t_env *env)
{
	while (env)
	{
		env->status = 1;
		env = env->next;
	}
}

t_env	*__fill_env(char **env)
{
	int		i;
	t_env	*env_node;
	char	*first;
	char	*sec;

	env_node = malloc(sizeof(t_env));
	env_node->variable = cut_first(env[0]);
	env_node->value = cut_secound(env[0], env_node->variable);
	env_node->next = NULL;
	i = 1;
	while (env[i])
	{
		first = cut_first(env[i]);
		sec = cut_secound(env[i], first);
		_ft_lstadd_back(&env_node, _ft_lstnew(first, sec));
		i++;
	}
	init_status(env_node);
	return (env_node);
}
