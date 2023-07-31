/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:56:03 by asaber            #+#    #+#             */
/*   Updated: 2022/10/25 11:43:52 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*begin;

	begin = NULL;
	begin = (t_list *) malloc(sizeof(t_list));
	if (begin == 0)
		return (NULL);
	begin->content = content;
	begin->next = NULL;
	return (begin);
}
