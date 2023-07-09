/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:58:53 by asaber            #+#    #+#             */
/*   Updated: 2022/11/17 00:07:11 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*ptrd;

	ptr = (unsigned char *) src;
	ptrd = (unsigned char *) dst;
	if (!ptr && !ptrd)
		return (0);
	while (n-- > 0)
	{
		*ptrd = *ptr;
		ptr++;
		ptrd++;
	}
	return (dst);
}
