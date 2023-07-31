/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:34:20 by asaber            #+#    #+#             */
/*   Updated: 2023/07/31 18:13:15 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// g_lob env is a g_lobal variable in this case

int	home_error(t_pcommand_d *cmd)
{
	if (ft_strlen(cmd->command[1]) == 0 && search_env("HOME") == NULL)
	{
		printf("minishell: cd: HOME not set\n");
		g_lob.exit_status = 1;
		return (1);
	}
	return (0);
}

int	cd_command_len(t_pcommand_d *cmd)
{
	int	i;

	i = 1;
	while (cmd->next)
	{
		i++;
		cmd = cmd->next;
	}
	return (1);
}

void	printerror(int i, char *tmp)
{
	if (i == -1)
	{
		printf("minishell: cd: %s: %s\n", tmp, strerror(errno));
		g_lob.exit_status = 1;
	}
}

void	ft_cd(t_pcommand_d *cmd)
{
	char	*tmp;
	int		i;

	if (home_error(cmd) || cmd->lenth > 1)
		return ;
	if (ft_strlen(cmd->command[1]) == 0)
		tmp = search_env("HOME");
	else if (ft_strlen(cmd->command[1]) == 1 && cmd->command[1][0] == '~')
		tmp = search_env("HOME");
	else
		tmp = cmd->command[1];
	i = chdir(tmp);
	printerror(i, tmp);
}
