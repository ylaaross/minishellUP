/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:12:39 by asaber            #+#    #+#             */
/*   Updated: 2023/07/22 23:42:10 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builts(char *command)
{
	int	size;

	size = ft_strlen(command);
	if (command)
	{
		if (ft_strncmp(command, "cd", size) == 0)
			return (1);
		else if (ft_strncmp(command, "echo", size) == 0)
			return (1);
		else if (ft_strncmp(command, "pwd", size) == 0)
			return (1);
		else if (ft_strncmp(command, "export", size) == 0)
			return (1);
		else if (ft_strncmp(command, "unset", size) == 0)
			return (1);
		else if (ft_strncmp(command, "env", size) == 0)
			return (1);
		else if (ft_strncmp(command, "exit", size) == 0)
			return (1);
	}
	return (0);
}

void	do_builtins(t_pcommand_d *cmd, int *status)
{
	if (cmd->command)
	{
		if (ft_strncmp(cmd->command[0], "cd", ft_strlen(cmd->command[0])) == 0)
			ft_cd(cmd, status);
		else if (ft_strncmp(cmd->command[0], "echo", ft_strlen(cmd->command[0])) == 0)
			ft_echo(cmd);
		else if (ft_strncmp(cmd->command[0], "pwd", ft_strlen(cmd->command[0])) == 0)
			__pwd(cmd);
		else if (ft_strncmp(cmd->command[0], "export", ft_strlen(cmd->command[0])) == 0)
			__export(cmd);
		else if (ft_strncmp(cmd->command[0], "unset", ft_strlen(cmd->command[0])) == 0)
			__unset(cmd);
		else if (ft_strncmp(cmd->command[0], "env", ft_strlen(cmd->command[0])) == 0)
			__env(Glob.env);
		else if (ft_strncmp(cmd->command[0], "exit", ft_strlen(cmd->command[0])) == 0)
			ft_exit(cmd->command, status);
	}
}