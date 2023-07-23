/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:18:20 by asaber            #+#    #+#             */
/*   Updated: 2022/10/25 11:25:07 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

char	ft_calcul(long nb, int i)
{
	char	n;

	while (i)
	{
		n = nb % 10 + 48;
		nb /= 10;
		i--;
	}
	return (n);
}

int	lennmb(long nb)
{
	int	i;

	i = 0;
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	int		i;
	char	nbr;

	nbr = '?';
	nb = n;
	i = lennmb(nb);
	if (nb == 0)
		write(fd, "0", 1);
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb *= -1;
	}
	while (i)
	{
		nbr = ft_calcul(nb, i);
		write(fd, &nbr, 1);
		i--;
	}
}
