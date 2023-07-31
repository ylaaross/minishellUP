/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:21:06 by asaber            #+#    #+#             */
/*   Updated: 2023/07/31 17:01:54 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heardoc_check(t_pcommand_d *cmmd)
{
	t_pcommand_d *cmd;

	cmd = cmmd;
	while (cmd->file)
	{
		if (cmd->file->type == 13)
			return (1);
		cmd->file = cmd->file->next;
	}
	return (0);
}

// int	endslne(t_file *files)
// {
// 	int	i;

// 	i = 0;
// 	while(files)
// 	{
// 		if (files->type == 13)
// 			i++;
// 		files = files->next;
// 	}
// 	return (i);
// }

// void	fill_endo(char **ends, t_file *files)
// {
// 	int	i;

// 	i = 0;
// 	while (files)
// 	{
// 		if (files->type == 13)
// 		{
// 			ends[i] = files->file_name;
// 			i++;
// 		}
// 		files = files->next;
// 	}
// 	ends[i] = 0;
// }

// int	do_heardoc(t_pcommand_d *cmd)
// {
// 	int			fd;
// 	int			i;
// 	char		*line;
// 	char		**end_files;
// 	char		*path;
// 	t_command_d	*t;

// 	path = ft_strjoin("tmp/", cmd->file->file_name);
// 	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0666);
// 	end_files = (char **)malloc(endslne(cmd->file) + 1);
// 	if (!end_files)
// 		return (0);
// 	fill_endo(end_files, cmd->file);
// 	if (fd == -1)
// 	{
// 		printf("minishell: %s: %s\n", cmd->file->file_name, strerror(errno));
// 		return (EXIT_FAILURE);
// 	}
// 	i = 0;
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (line && !ft_strncmp(line, end_files[i], ft_strlen(line)))
// 			i++;
// 		if (i == endslne(cmd->file))
// 			break ;
// 		else
// 		{
// 		t = 0;
// 		split_parse(line, &t);
// 		if(!cmd->file->state)
// 			expend_herdock(t);
// 		line = concat_herdock(t);
// 		free_token(t);
// 			write (fd, line , ft_strlen (line));
// 			write (fd , "\n", 1);
// 		}
// 		//free(line);
// 	}
// 	close(fd);
// 	//free(path);
// 	return (1); 
// }

void	start_heardoc(int *fd, char *endo, t_file *file)
{
	char		*line;
	t_command_d	*t;

	while (1)
	{
		line = 	readline("> ");
		if (line)
		{
			if (ft_strncmp(endo, line, ft_strlen(endo)+1) == 0)
				break ;
			t = 0;
			split_parse(line, &t);
			if(!file->state)
				expend_herdock(t);
			line = concat_herdock(t);
			free_token(t);
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
				start_heardoc(fd, cmd->file->file_name, tmp);
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
	//printf("check buf %s\n", buf);
}