/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:20:00 by asaber            #+#    #+#             */
/*   Updated: 2023/07/18 16:39:13 by asaber           ###   ########.fr       */
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
	{
		cnt++;
	}
	first = malloc(cnt + 1);
	i = 0;
	while (i < cnt && env[cnt])
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


//if you want edit in the value of each variable you can use this function

void	__edit_env(char *var, char *value)
{
	t_env	*env;
	int		size;

	size = ft_strlen(var);
	env = Glob.env;
	while (env)
	{
		if (!ft_strncmp(var, env->variable, size))
		{
			free(env->value);
			env->value = ft_strdup(value);
			break ;
		}
		env = env->next;
	}
}

t_env	*__fill_env(char **env)
{
	int		i;
	t_env	*env_node;

	env_node = malloc(sizeof(t_env));
	env_node->variable = cut_first(env[0]);
	env_node->value = cut_secound(env[0], cut_first(env[0]));
	env_node->next = NULL;
	i = 1;
	while (env[i])
	{
		_ft_lstadd_back(&env_node, _ft_lstnew(cut_first(env[i]),
				cut_secound(env[i], cut_first(env[i]))));
		i++;
	}
	return (env_node);
}
