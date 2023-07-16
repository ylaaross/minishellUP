/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:28:49 by asaber            #+#    #+#             */
/*   Updated: 2023/07/16 19:35:12 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	list_len(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**convert_list(void)
{
	char	**cp_env;
	char	*tmp_variable;
	t_env	*env;
	int		size;
	int		i;

	env = Glob.env;
	size = list_len(env);
	cp_env = (char **)malloc((size + 1) * sizeof(char *));
	i = 0;
	while (env)
	{
		tmp_variable = ft_strjoin(env->variable, "=");
		cp_env[i] = ft_strjoin(tmp_variable, env->value);
		env = env->next;
		i++;
	}
	cp_env[i] = 0;
	return (cp_env);
}

char	*search_env(char *var)
{
	t_env	*env;
	int		size;

	size = ft_strlen(var);
	env = Glob.env;
	while (env)
	{
		if (!ft_strncmp(var, env->variable, size))
			return (env->value);
		env = env->next;
	}
	return(NULL);
}

char *check_command(char **path, char *command)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], ft_strjoin("/", command));
		if (access(tmp, F_OK) == 0)
			return (tmp);
		i++;
	}
	return (NULL);
}

void	free_command(t_pcommand_d *cmd)
{
	t_file			*tmp_file;

		while (cmd->file)
		{
			tmp_file = cmd->file;
			cmd->file = cmd->file->next;
			free(tmp_file->file_name);
			free(tmp_file);
		}
}
int	redirect(t_pcommand_d *cmd)
{
	int		fd;
	//char	*line;
//if type of redirection is '<' do this
	if (cmd->file->type == 14)
	{
		fd = open(cmd->file->file_name, O_RDONLY);
		if (fd == -1)
		{
			printf("minishell: %s: %s\n", cmd->file->file_name, strerror(errno));
			return (1);
		}
		dup2(fd, 0);
		cmd->file = cmd->file->next;
	}
// if type of redirection is '>' do this
	else if (cmd->file->type == 8)
	{
		fd = open(cmd->file->file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			printf("minishell: %s: %s\n", cmd->file->file_name, strerror(errno));
			return (1);
		}
		dup2(fd, 1);
		cmd->file = cmd->file->next;
	}
// if type of redirection is '>>' do this
	else if (cmd->file->type == 9)
	{
		fd = open(cmd->file->file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			printf("minishell: %s: %s\n", cmd->file->file_name, strerror(errno));
			return (1);
		}
		dup2(fd, 1);
		cmd->file = cmd->file->next;
	}

//if is heardoc do this
	// else if (cmd->file->type == 10)
	// {
	// 	fd = open("tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	// 	if (fd == -1)
	// 	{
	// 		printf("minishell: %s: %s\n", cmd->file->file_name, strerror(errno));
	// 		return (1);
	// 	}
	// 	dup2(fd, 1);
	// 	cmd->file = cmd->file->next;
	// 	while (cmd->file->type != 11)
	// 	{
	// 		printf("> ");
	// 		get_next_line(0);
	// 		write(fd, line, ft_strlen(line));
	// 		write(fd, "\n", 1);

	// 	}
	// 	close(fd);
	// 	fd = open("tmp", O_RDONLY);
	// 	dup2(fd, 0);
	// 	cmd->file = cmd->file->next;
	// }
	return (0);
}




int	do_command(t_pcommand_d *cmd, int *exit_s)
{
	int		i;
	char	**paths;
	char	**env;
	int		id;
	int		check;

	paths = ft_split(search_env("PATH"), ':');
	env = convert_list();
	i = 0;
	id = fork();
	check = 0;
	if (id == 0)
	{
		printf("command: %s\n", cmd->command[0]);
		if (cmd->file)
			check = redirect(cmd);
		if (cmd->command[0] && check == 0)
		{
			if (check_command(paths, cmd->command[0]))
				execve(check_command(paths, cmd->command[0]), cmd->command, env);
			else
			{
				*exit_s = 127;
				printf("minishell>: %s: command not found\n", cmd->command[0]);
				cmd = cmd->next;
			}
		}
		else
			exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
	free_command(cmd);
	return (0);
}
