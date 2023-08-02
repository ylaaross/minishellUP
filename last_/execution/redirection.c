/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:07:21 by asaber            #+#    #+#             */
/*   Updated: 2023/08/01 17:51:12 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_redir_error(t_pcommand_d *cmd)
{
	printf("minishell: %s: %s\n",
		cmd->file->file_name, strerror(errno));
	g_lob.exit_status = 1;
	return (1);
}

int	ft_stdin(t_pcommand_d *cmd)
{
	int	fd;

	fd = open(cmd->file->file_name, O_RDONLY);
	if (fd == -1)
		return (print_redir_error(cmd));
	dup2(fd, 0);
	return (0);
}

int	ft_stdout(t_pcommand_d *cmd)
{
	int	fd;

	fd = open(cmd->file->file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (print_redir_error(cmd));
	dup2(fd, 1);
	return (0);
}

int	ft_append(t_pcommand_d *cmd)
{
	int	fd;

	fd = open(cmd->file->file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (print_redir_error(cmd));
	dup2(fd, 1);
	return (0);
}

int	redirect(t_pcommand_d *cmd)
{
	int	check;

	while (cmd->file)
	{
		if (cmd->file->type == 14)
		{
			check = ft_stdin(cmd);
			if (check)
				return (check);
		}
		else if (cmd->file->type == 8)
		{
			check = ft_stdout(cmd);
			if (check)
				return (check);
		}
		else if (cmd->file->type == 7)
		{
			check = ft_append(cmd);
			if (check)
				return (check);
		}
		cmd->file = cmd->file->next;
	}
	return (0);
}
