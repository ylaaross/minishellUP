/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:57:27 by asaber            #+#    #+#             */
/*   Updated: 2022/10/25 11:22:26 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_nblen(int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
	{
		i++;
		return (i);
	}
	while (nb != 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	nb;
	char	*allocat;
	int		slen;

	nb = n;
	slen = ft_nblen(nb);
	if (nb < 0)
		slen++;
	allocat = (char *) malloc(slen + 1 * sizeof(char));
	if (allocat == 0)
		return (0);
	if (nb < 0)
	{
		nb *= -1;
		allocat[0] = '-';
	}
	allocat[slen] = '\0';
	while (nb >= 0)
	{
		allocat[--slen] = 48 + (nb % 10);
		nb /= 10;
		if (nb == 0)
			break ;
	}
	return (allocat);
}
