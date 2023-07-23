/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:43:12 by asaber            #+#    #+#             */
/*   Updated: 2023/07/22 23:45:17 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(char **command, int *status)
{
	int	i;

	i = 0;
	if (command[1] == NULL)
		exit(*status);
	else if (command[1] != NULL && command[2] == NULL)
	{
		while (command[1][i])
		{
			if (ft_isdigit(command[1][i]) == 0)
			{
				ft_putstr_fd("exit\n", 2);
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(command[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				exit(255);
			}
			i++;
		}
		exit(ft_atoi(command[1]));
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	}
}
