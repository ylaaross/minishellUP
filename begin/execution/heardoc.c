/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:21:06 by asaber            #+#    #+#             */
/*   Updated: 2023/07/31 20:23:17 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int	heardoc_check(t_file *file)
{
	t_file *files;

	files = file;
	while (files)
	{
		if (files->type == 13)
			return (1);
		files = files->next;
	}
	return (0);
}
void	expend_exit_her(t_command_d	*t)
{
	while (t)
	{
		if (t->token == EXIT_STATUS)
		{
			free(t->content);
			t->content = ft_strdup(ft_itoa(g_lob.exit_status));
		}
		t = t->next;
	}
}

void	start_heardoc(int *fd, char *endo, t_file *file)
{
	char		*line;
	t_command_d	*t;

	while (1)
	{
		line = readline("> ");
		if (line)
		{
			if (ft_strncmp(endo, line, ft_strlen(endo) + 1) == 0)
				break ;
			if (!file->state)
			{
				t = 0;
				split_parse(line, &t);
				expend_herdock(t);
				expend_exit_her(t);
				line = concat_herdock(t);
				free_token(t);
			}
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
		}
	}
}

void	do_heardoc(t_pcommand_d *cmd)
{
	int	fd[2];
	char *buf = ft_calloc(45, 1);
	int	pid;
	t_file *tmp;

	tmp = cmd->file;
	while (tmp)
	{
		if (tmp->type == 13)
		{
			pipe(fd);
			pid = fork();
			if (pid == 0) {
				close(fd[0]);
				start_heardoc(fd, tmp->file_name, tmp);
				exit(0);
			}
			else
			{
				close(fd[1]);
				waitpid(pid, NULL, 0);
			}
		}
		tmp = tmp->next;
	}
	dup2(fd[0], 0);
	close(fd[0]);
	read(0, buf, 0);
}