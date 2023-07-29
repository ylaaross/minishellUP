/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:28:49 by asaber            #+#    #+#             */
/*   Updated: 2023/07/29 20:36:09 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int list_len(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char **convert_list(void)
{
	char **cp_env;
	char *tmp_variable;
	t_env *env;
	int size;
	int i;

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

char *search_env(char *var)
{
	t_env *env;
	int size;

	size = ft_strlen(var);
	env = Glob.env;
	while (env)
	{
		if (!ft_strncmp(var, env->variable, size))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char *check_command(char **path, char *command)
{
	int i;
	char *tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], ft_strjoin("/", command));
		if (access(tmp, F_OK) == 0)
			return (tmp);
		i++;
	}
	printf("minishell>: %s: command not found\n", command);
	Glob.exit_status = 127;
	
	return (NULL);
}

void free_command(t_pcommand_d *cmd)
{
	t_file *tmp_file;

	if (cmd && cmd->file)
	{
		while (cmd->file)
		{
			tmp_file = cmd->file;
			cmd->file = cmd->file->next;
			free(tmp_file->file_name);
			free(tmp_file);
		}
	}
}
int redirect(t_pcommand_d *cmd)
{
	int fd;
	while (cmd->file)
	{
		if (cmd->file->type == 14)
		{
			fd = open(cmd->file->file_name, O_RDONLY);
			if (fd == -1)
			{
				printf("minishell: %s: %s\n", cmd->file->file_name, strerror(errno));
				Glob.exit_status = 1;
				return (1);
			}
			dup2(fd, 0);
			cmd->file = cmd->file->next;
		}
		else if (cmd->file->type == 8)
		{
			fd = open(cmd->file->file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				printf("minishell: %s: %s\n", cmd->file->file_name, strerror(errno));
				Glob.exit_status = 1;
				return (1);
			}
			dup2(fd, 1);
			cmd->file = cmd->file->next;
		}
		else if (cmd->file->type == 7)
		{
			fd = open(cmd->file->file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				printf("minishell: %s: %s\n", cmd->file->file_name, strerror(errno));
				Glob.exit_status = 1;
				return (1);
			}
			dup2(fd, 1);
			cmd->file = cmd->file->next;
		}
		else if (cmd->file->type == 13)
		{
			char *path = ft_strjoin("/tmp/", cmd->file->file_name);
			fd = open(path, O_RDONLY, 0666);
			if (fd == -1)
			{
				printf("minishell: %s: %s\n", cmd->file->file_name, strerror(errno));
				Glob.exit_status = 1;
				return (1);
			}
			dup2(fd, STDIN_FILENO);
			cmd->file = cmd->file->next;
		}
	}
	return (0);
}

int do_command(t_pcommand_d *cmd)
{
	int id;
	int fd[2];
	char **paths;
	char **env;
	int check;
	int input;
	int	status;

	if (!cmd)
		return 0;
	paths = ft_split(search_env("PATH"), ':');
	check = 0;
	input = 0;
		while (cmd)
		{
			if (do_builtins(cmd) && !redirect(cmd))
			{
				cmd = cmd->next;
				env = convert_list();
				continue ;
			}
			pipe(fd);
				id = fork();
				if (id == 0)
				{
					if (!check_builts(cmd->command[0]))
						dup2(input, 0);
					if (cmd->next)
					{
						dup2(fd[1], 1);
						close(fd[1]);
						close(fd[0]);
					}
					if (cmd->file)
						check = redirect(cmd);
					if (cmd->command[0] && check == 0)
					{
						if (do_execbuiltins(cmd))
							exit(Glob.exit_status);
						if (check_command(paths, cmd->command[0]))
							execve(check_command(paths, cmd->command[0]), cmd->command, env);
					}
					// else
						exit(Glob.exit_status);
				}
				else
				{
					close(fd[1]);
					input = fd[0];
					if (!input)
						close(input);
					wait(&status);
					if (WIFEXITED(status))
						Glob.exit_status = WEXITSTATUS(status);
				}
			cmd = cmd->next;
		}
	free_command(cmd);
	return (0);
}
