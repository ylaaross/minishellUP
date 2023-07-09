/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:04:18 by asaber            #+#    #+#             */
/*   Updated: 2022/10/24 19:43:33 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*end;

	end = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
		while (end->next)
			end = end->next;
		end->next = new;
		new->next = NULL;
}
