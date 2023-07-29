/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 10:48:26 by asaber            #+#    #+#             */
/*   Updated: 2022/10/25 11:29:12 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ss;
	char	cc;
	int		ln;
	int		i;

	ss = (char *)s;
	cc = (char)c;
	ln = ft_strlen(s);
	if (cc == '\0')
		return ((ss + ln));
	i = 0;
	while (ss[i])
	{
		if (ss[i] == cc)
			return (&ss[i]);
		i++;
	}
	return (0);
}
