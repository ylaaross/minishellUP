/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:15:27 by ylaaross          #+#    #+#             */
/*   Updated: 2023/07/31 18:30:44 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>

int	negative(int *n)
{
	if (*n < 0)
	{
		*n = *n * -1;
		return (1);
	}
	else
		return (0);
}

char	*allocate(char *p, size_t len, char *t, int signe)
{
	int		i;
	int		j;

	i = 0;
	j = len ;
	if (signe == 1)
		p = (char *)malloc(len + 3);
	else
	{
	p = (char *)malloc(len + 2);
	}
	if (p == 0)
		return (0);
	else
	{
		if (signe)
			p[i++] = '-';
		while (j >= 0)
			p[i++] = t[j--];
		p[i] = 0;
		return (p);
	}
}

char	*ft_itoa(int n)
{
	char	t[100];
	int		i;
	char	*p;
	int		signe;
	char	*min;

	i = 0;
	p = 0;
	if (n == -2147483648)
	{
		min = ft_itoa(-2147483647);
		min[10] = min[10] + 1;
		return (min);
	}
	signe = negative(&n);
	while (n >= 10)
	{
		t[i] = (n % 10) + '0';
		n = n / 10;
		i++;
	}
	t[i] = n + '0';
	t[i + 1] = 0;
	return (allocate(p, (size_t)i, t, signe));
}
