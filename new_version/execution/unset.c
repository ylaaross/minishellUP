/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 21:20:44 by asaber            #+#    #+#             */
/*   Updated: 2023/07/31 16:47:31 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rm_node(t_env *env)
{
	t_env	*tmp;

	tmp = env->next;
	env->next = tmp->next;
	free(tmp->variable);
	free(tmp->value);
	free(tmp);
}

int	isin_env(char *var)
{
	t_env	*env;
	int		size;
	int		i;

	env = g_lob.env;
	size = ft_strlen(var);
	i = 0;
	while (env)
	{
		if (ft_strncmp(env->variable, var, size) == 0)
			return (i);
		env = env->next;
		i++;
	}
	return (0);
}

void	find_rm(int posision)
{
	t_env	*env;
	int		i;

	env = g_lob.env;
	i = 1;
	while (env)
	{
		if (i == posision)
		{
			rm_node(env);
			break ;
		}
		i++;
		env = env->next;
	}	
}

void	__unset(t_pcommand_d *cmd)
{
	int	i;
	int	posision;

	i = 1;
	if (redirect(cmd) == -1)
		return ;
	while (cmd->command[i])
	{
		if ((posision = isin_env(cmd->command[i])))
			find_rm(posision);
		i++;
	}
}