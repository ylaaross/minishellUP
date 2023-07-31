/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 11:38:25 by asaber            #+#    #+#             */
/*   Updated: 2022/10/24 12:53:19 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*pt;

	while (*lst)
	{
		pt = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = pt;
	}
	*lst = 0;
}
