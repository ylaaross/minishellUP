/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:21:06 by asaber            #+#    #+#             */
/*   Updated: 2023/08/02 15:53:31 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expend_exit_her(t_command_d	*t)
{
	char	*c;

	c = 0;
	while (t)
	{
		if (t->token == EXIT_STATUS)
		{
			free(t->content);
			c = ft_itoa(g_lob.exit_status);
			t->content = ft_strdup(c);
			free(c);
		}
		t = t->next;
	}
}

int	heardoc_check(t_file *file)
{
	t_file	*files;

	files = file;
	while (files)
	{
		if (files->type == 13)
			return (1);
		files = files->next;
	}
	return (0);
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
			t = 0;
			split_parse(line, &t);
			if (!file->state)
			{
				expend_herdock(t);
				expend_exit(t);
				expend_exit_her(t);
			}
			line = concat_herdock(t);
			free_token(t);
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
		}
	}
}

void	finded_heardoc(t_file *tmp, int fd[2])
{
	int		pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		start_heardoc(fd, tmp->file_name, tmp);
		close(fd[1]);
		exit(0);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
	}
}

void	do_heardoc(t_pcommand_d *cmd)
{
	int		fd[2];
	char	*buf;
	t_file	*tmp;

	tmp = cmd->file;
	while (tmp)
	{
		if (tmp->type == 13)
			finded_heardoc(tmp, fd);
		tmp = tmp->next;
	}
	buf = ft_calloc(1, 1);
	dup2(fd[0], 0);
	close(fd[0]);
	read(0, buf, 0);
	free(buf);
}
