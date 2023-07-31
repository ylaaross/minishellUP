/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 20:22:41 by asaber            #+#    #+#             */
/*   Updated: 2023/07/31 16:47:31 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	main(int ac, char **av, char **env)
// {
// 	 char	*ptr;

// 	// while (1)
// 	// {
// 	// 	ptr = readline("AE_SHELL_> ");
// 	// 	(void) ac;
// 	// 	(void) av;
// 	// 	printf("check!! %s\n", ptr);
// 	// 	g_lob.env = __fill_env(env);
// 	// 	if (ft_strncmp(ptr, "pwd", 3) == 0)
// 	// 		__pwd(g_lob.env);
// 	// 	if (ft_strncmp(ptr, "env", 3) == 0)
// 	// 		__env(g_lob.env);
// 	// 	if (ft_strncmp(ptr, "export", 6) == 0)
// 	// 	{
// 	// 		__export(ptr);
// 	// 		//__env(g_lob.env);
// 	// 	}
// 	// 	free(ptr);
// 	// }

// 	(void) ac;
// 	(void) av;
// 	char **command;
// 	g_lob.env = __fill_env(env);
// 	while (1)
// 	{
// 		ptr = readline("AE_SHELL_> ");
// 		command = ft_split(ptr, ' ');
// 		if (do_command(command) == 0)
// 			printf("coomand not found\n");
// 		free(ptr);
// 	}
// 	printf("7aaaadak tam\n");
// 	return (0);
// }
