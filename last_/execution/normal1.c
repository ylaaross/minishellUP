/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 20:38:38 by asaber            #+#    #+#             */
/*   Updated: 2023/08/02 01:37:35 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_impliment(t_pcommand_d **cmd, char	***env)
{
	free_cpenv(*env);
	*cmd = (*cmd)->next;
	*env = convert_list();
	g_lob.exit_status = 0;
}

void	signals_free(char	**env, t_pcommand_d **cmd)
{
	signals();
	free_cpenv(env);
	*cmd = (*cmd)->next;
}

int	check_valid(t_pcommand_d *cmd)
{
	if (!cmd->command[0])
		return (1);
	if (!cmd->file && cmd->command[0][0] == '\0')
	{
		printf("minishell : command not found\n");
		g_lob.exit_status = 127;
		return (1);
	}
	return (0);
}

void	do_command(t_pcommand_d *cmd)
{
	int		id;
	int		fd[2];
	char	**env;
	int		input;

	input = 0;
	while (cmd)
	{
		if (check_valid(cmd))
			return ;
		env = convert_list();
		if (do_builtins(cmd))
		{
			free_impliment(&cmd, &env);
			continue ;
		}
		pipe(fd);
		signal (SIGINT, SIG_IGN);
		id = fork();
		if (id == 0)
			child_command(cmd, env, fd, input);
		else
			wait_chlid(fd, &input);
		signals_free(env, &cmd);
	}
}
