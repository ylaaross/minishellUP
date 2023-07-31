/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:43:12 by asaber            #+#    #+#             */
/*   Updated: 2023/07/31 16:47:31 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int is_digit_loop(char *s)
{
	int i;

	i = 0;
	if ((s[i] == '-' || s[i] == '+') && s[i + 1])
		i++;
	while (s[i])
	{
		if (ft_isdigit(s[i]))
				i++;
		else
			return (1);
	}
	return (0);
}



void	ft_exit(char **command)
{
	int	i;

	i = 0;
	if (command[1] == NULL)
		exit(g_lob.exit_status);
	else if (command[1] && command[2] && is_digit_loop(command[1]) == 1)
	{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(command[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
			
	}
	else if (command[1] != NULL && command[2] == NULL)
	{
		if (is_digit_loop(command[1]) == 1)
		{
			//ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(command[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		exit(ft_atoi(command[1]));
	}
	else
	{
		//ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_lob.exit_status = 1;
	}
}
