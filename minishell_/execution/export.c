/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:00:18 by asaber            #+#    #+#             */
/*   Updated: 2023/07/22 21:11:44 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_global(char *str, int start, int end)
{
	int	i;

	i = start;
	while (i <= end)
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	if (i <= end)
	{
		_ft_lstadd_back(&Glob.env, _ft_lstnew(cut_first(&str[start]),
				cut_secound(&str[start], cut_first(&str[start]))));
	}
}

void	export_alone(void)
{
	t_env	*env;

	env = Glob.env;
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->variable, env->value);
		env = env->next;
	}
}

int	check_str_is_alone(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i])
	{
		while (str[i] && !(str[i] == ' ' || str[i] == '\t'))
			i++;
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
		if (str[i] && str[i] && (str[i] == ' ' || str[i] == '\t'))
			return (i);
	}
	return (0);
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

void	__export(t_pcommand_d *cmd)
{
	int		i;
	int		j;
	int		len;
	char	*check;
	char 	*value;

	i = 1;
	len = command_len(cmd->command);
	if (redirect(cmd) == -1)
		return ;
	if (len == 1)
		export_alone();
	else
	{
		while (cmd->command[i])
		{
			check = cut_first(cmd->command[i]);
			if (isin_env(check) == 0)
			{
				j = check_str_is_alone(cmd->command[i]);
				if (j)
					add_global(cmd->command[i], 0, j - 1);
				else
					add_global(cmd->command[i], 0, ft_strlen(cmd->command[i]) - 1);
			}
			else
			{
				value = cut_secound(cmd->command[i], check);
				__edit_env(check, value);
				free(value);
			}
			free(check);
			i++;
		}
	}
}