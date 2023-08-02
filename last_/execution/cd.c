/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:34:20 by asaber            #+#    #+#             */
/*   Updated: 2023/08/01 20:31:30 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
