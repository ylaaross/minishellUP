/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:12:39 by asaber            #+#    #+#             */
/*   Updated: 2023/07/29 20:39:45 by asaber           ###   ########.fr       */
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

int	do_builtins(t_pcommand_d *cmd)
{
	if (cmd->command[0])
	{
		if (ft_strncmp(cmd->command[0], "cd", 3) == 0)
		{
			ft_cd(cmd);
			return (1);
		}
		else if ((ft_strncmp(cmd->command[0], "export", 7) == 0) && command_len(cmd->command) > 1)
		{
			__export(cmd);
			return (1);
		}
		else if (ft_strncmp(cmd->command[0], "unset", 6) == 0)
		{
			__unset(cmd);
			return (1);
		}
		else if (ft_strncmp(cmd->command[0], "exit", 5) == 0)
		{
			ft_exit(cmd->command);
			return (1);
		}
		//printf("check!!!bultinnnnnnn\n");
	}
	return (0);
}

int	do_execbuiltins(t_pcommand_d *cmd)
{
		if (ft_strncmp(cmd->command[0], "echo", 5) == 0)
		{
			ft_echo(cmd);
			return (1);
		}
		else if (ft_strncmp(cmd->command[0], "pwd", 4) == 0)
		{
			__pwd(cmd);
			return (1);
		}
		else if (ft_strncmp(cmd->command[0], "env", 4) == 0)
		{
			__env(Glob.env);
			return (1);
		}
		else if ((ft_strncmp(cmd->command[0], "export", 7) == 0) && command_len(cmd->command) == 1)
		{
			export_alone();
			return (1);
		}
	return (0);
}