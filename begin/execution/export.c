/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:00:18 by asaber            #+#    #+#             */
/*   Updated: 2023/07/31 16:47:31 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_status(t_env *env, int	status)
{
	while (env->next)
	{
		env = env->next;
	}
	env->status = status;
}

void	add_g_lobal(char *str, int start, int end)
{
	int	i;
	int	status;

	status = 1;
	i = start;
	if (start == end)
		status = 0;
	else
	{
		while (i <= end)
		{
			if (str[i] == '=' || str[i])
				break ;
			i++;
		}
	}
	if (i <= end)
	{
		_ft_lstadd_back(&g_lob.env, _ft_lstnew(cut_first(&str[0]), cut_secound(&str[start], cut_first(&str[start]))));
		add_status(g_lob.env, status);
	}
}

void	export_alone(void)
{
	t_env	*env;

	env = g_lob.env;
	while (env)
	{
		if (env->status)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(env->variable, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\"", 1);
			ft_putstr_fd("\n", 1);
		}
		else
			printf("declare -x %s\n", env->variable);
		env = env->next;
	}
}

int	command_len(char **command)
{
	int i;

	i = 0;
	while (command[i])
	{
		i++;
	}
	return (i);
}

int	validation_variable(char *str)
{
	int		i;

	i = 1;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	__export(t_pcommand_d *cmd)
{
	int		i;
	char	*check;

	i = 1;
	while (cmd->command[i])
	{
		check = cut_first(cmd->command[i]);
		if (validation_variable(check))
		{
			printf("minishell: not a valid identifier\n");
			g_lob.exit_status = 1;
		}
		else if (isin_env(check))
			__edit_env(check, cut_secound(cmd->command[i], check));
		else
			add_g_lobal(cmd->command[i], ft_strlen(check), ft_strlen(cmd->command[i]));
		i++;
	}
}