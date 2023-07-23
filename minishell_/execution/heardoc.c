/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:21:06 by asaber            #+#    #+#             */
/*   Updated: 2023/07/23 18:21:26 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// if is heardoc in the command

int	heardoc_check(t_pcommand_d *cmd)
{
	while (cmd)
	{
		if (cmd->file)
		{
			if (cmd->file->type == 13)
				return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}

// int	under_cmd_check_heardoc(t_pcommand_d *cmd)
// {
// 	while (cmd->)
// }
 
// if is heardoc in the command

int	do_heardoc(t_pcommand_d *cmd)
{
	int			fd;
	char		*line;
	char		*path;
	t_command_d	*t;
	
	//while (heardoc_check(che))
	path = ft_strjoin("/tmp/", cmd->file->file_name);
	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd == -1)
	{
		printf("minishell: %s: %s\n", cmd->file->file_name, strerror(errno));
		return (EXIT_FAILURE);
	}
	// pause();
	while (1)
	{
		line = readline("> ");
		if (line && !ft_strncmp(line, cmd->file->file_name, ft_strlen(line)))
			break ;
		else
		{
		t = 0;
		split_parse(line, &t);
		if(!cmd->file->state)
			expend_herdock(t);
		line = concat_herdock(t);
		free_token(t);
			write (fd, line , ft_strlen (line));
			write (fd , "\n", 1);
		}
		free(line);
	}
	// now dupliacte the fd to stdin
	// dup2(fd, STDIN_FILENO);
	close(fd);
	free(path);
	return (1); 
}