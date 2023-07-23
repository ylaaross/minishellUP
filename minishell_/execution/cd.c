/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:34:20 by asaber            #+#    #+#             */
/*   Updated: 2023/07/22 23:32:42 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// glob env is a global variable in this case

int	home_error(t_pcommand_d *cmd, int *status)
{
	if (ft_strlen(cmd->command[1]) == 0 && search_env("HOME") == NULL)
	{
		printf("minishell: cd: HOME not set\n");
		*status = 1;
		return (1);
	}
	return (0);
}

void	ft_cd(t_pcommand_d *cmd, int *status)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (redirect(cmd) == -1)
		return ;
	while (cmd->command[i])
		i++;
	// if (i > 2)
	// {
	// 	printf("cd: too many arguments\n");
	// 	return ;
	// }
	if (home_error(cmd, status))
		return ;
	else if (i == 2 && cmd->command[1][0] == '~')
	{
		tmp = search_env("HOME");
		tmp2 = ft_strjoin(tmp, cmd->command[1] + 1);
		if (chdir(tmp) == -1)
		{
			printf("minishell: cd: %s: %s\n", tmp, strerror(errno));
			*status = 1;
		}
		free(tmp);
		free(tmp2);
	}
	else
	if (i == 1)
	{
		tmp = search_env("HOME");
		if (chdir(tmp) == -1)
		{
			printf("minishell: cd: %s: %s\n", tmp, strerror(errno));
			*status = 1;
		}
		free(tmp);
	}
	else
	{
		if (chdir(cmd->command[1]) == -1)
		{
			printf("minishell: cd: %s: %s\n", cmd->command[1], strerror(errno));
			*status = 1;
		}
	}
	i = 0;
	while (cmd->command[i])
	{
		free(cmd->command[i]);
		i++;
	}
	free(cmd->command);
}
