/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 13:10:52 by asaber            #+#    #+#             */
/*   Updated: 2022/10/25 11:19:32 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*allocat;

	allocat = (char *) malloc(count * size);
	if (allocat == 0)
		return (0);
	ft_bzero(allocat, count * size);
	return (allocat);
}
