/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:00:18 by asaber            #+#    #+#             */
/*   Updated: 2023/06/21 20:42:50 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_global(char *str, int start, int end)
{
	int	i;

	i = start;
	while (i <= end)
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	if (i <= end)
	{
		_ft_lstadd_back(&Glob.env, _ft_lstnew(cut_first(&str[start]),
				cut_secound(&str[start], cut_first(&str[start]))));
	}
}

void	export_alone(void)
{
	t_env	*env;

	env = Glob.env;
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->variable, env->value);
		env = env->next;
	}
}

int	check_str_is_alone(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i])
	{
		while (str[i] && !(str[i] == ' ' || str[i] == '\t'))
			i++;
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
		if (str[i] && str[i] && (str[i] == ' ' || str[i] == '\t'))
			return (i);
	}
	return (0);
}

void	__export(char *str)
{
	int	start;

	if ((start = check_str_is_alone(str)))
		add_global(str, start, ft_strlen(str));
	else
		export_alone();
}
