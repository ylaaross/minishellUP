/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:12:39 by asaber            #+#    #+#             */
/*   Updated: 2023/07/10 22:54:06 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builts(char *command)
{
	int	size;

	size = ft_strlen(command);
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
	return (0);
}

void	do_builtins(char **command)
{
	(void) command;
}