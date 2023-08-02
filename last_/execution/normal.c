/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:28:49 by asaber            #+#    #+#             */
/*   Updated: 2023/08/02 00:05:27 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**convert_list(void)
{
	char	**cp_env;
	char	*tmp_variable;
	t_env	*env;
	int		size;
	int		i;

	env = g_lob.env;
	size = list_len(env);
	cp_env = (char **)malloc((size + 1) * sizeof(char *));
	i = 0;
	while (env)
	{
		tmp_variable = ft_strjoin(env->variable, "=");
		cp_env[i] = ft_strjoin(tmp_variable, env->value);
		free(tmp_variable);
		env = env->next;
		i++;
	}
	cp_env[i] = 0;
	return (cp_env);
}

void	free_cpenv(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	*check_command(char **path, char *command)
{
	int		i;
	char	*tmp;

	i = 0;
	if (command[0] == '/')
	{
		if (access(command, F_OK) == 0)
			return (command);
	}
	if (path)
	{
		while (path[i])
		{
			tmp = ft_strjoin(path[i], ft_strjoin("/", command));
			if (access(tmp, F_OK) == 0)
				return (tmp);
			i++;
		}
	}
	printf("minishell>: %s: command not found\n", command);
	g_lob.exit_status = 127;
	return (NULL);
}

void	child_command(t_pcommand_d *cmd, char **env, int *fd, int input)
{
	int		check;
	char	**paths;

	def_signals();
	paths = ft_split(search_env("PATH"), ':');
	check = 0;
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
	if (check == 0)
	{
		if (do_execbuiltins(cmd))
			exit(0);
		if (check_command(paths, cmd->command[0]))
			execve(check_command(paths, cmd->command[0]),
				cmd->command, env);
	}
	exit(g_lob.exit_status);
}

void	wait_chlid(int *fd, int *input)
{
	int	status;

	close(fd[1]);
	*input = fd[0];
	if (!*input)
		close(*input);
	wait(&status);
	if (WIFEXITED(status))
		g_lob.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_lob.exit_status = WTERMSIG(status) + 128;
}
