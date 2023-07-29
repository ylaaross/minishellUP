/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:21:06 by asaber            #+#    #+#             */
/*   Updated: 2023/07/29 21:18:35 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	endslne(t_file *files)
{
	int	i;

	i = 0;
	while(files)
	{
		if (files->type == 13)
			i++;
		files = files->next;
	}
	return (i);
}

void	fill_endo(char **ends, t_file *files)
{
	int	i;

	i = 0;
	while (ends[i] && files)
	{
		if (files->type == 13)
		{
			ends[i] = files->file_name;
			i++;
		}
		files = files->next;
	}
}

int	do_heardoc(t_pcommand_d *cmd)
{
	int			fd;
	int			i;
	char		*line;
	char		**end_files;
	char		*path;
	t_command_d	*t;

	path = ft_strjoin("/tmp/", cmd->file->file_name);
	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0666);
	end_files = (char **)malloc(endslne(cmd->file) + 1);
	if (!end_files)
		return (0);
	end_files[endslne(cmd->file)] = 0;
	fill_endo(end_files, cmd->file);
	if (fd == -1)
	{
		printf("minishell: %s: %s\n", cmd->file->file_name, strerror(errno));
		return (EXIT_FAILURE);
	}
	i = 0;
	while (1)
	{
		line = readline("> ");
		if (line && !ft_strncmp(line, end_files[i], ft_strlen(line)))
			i++;
		if (i == endslne(cmd->file))
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
	close(fd);
	free(path);
	return (1); 
}