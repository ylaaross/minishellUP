/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 20:49:56 by asaber            #+#    #+#             */
/*   Updated: 2023/07/10 22:54:32 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	__pwd(t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		printf("FORK FAILED IN PWD\n");
		exit(1);
	}
	if (pid == 0)
	{
		while (env)
		{
			if (ft_strncmp(env->variable, "PWD", 3) == 0)
			{
				printf("%s\n", env->value);
			}
			env = env->next;
		}
	}
}
