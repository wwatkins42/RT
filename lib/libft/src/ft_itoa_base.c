/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 12:27:47 by wwatkins          #+#    #+#             */
/*   Updated: 2016/01/29 13:17:55 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_nbrlen_base(long n, int *abs, int base)
{
	int len;

	len = 0;
	*abs = 1;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		*abs = -1;
		base == 10 ? len++ : 0;
	}
	while (n > 0)
	{
		n /= base;
		len++;
	}
	return (len);
}

char		*ft_itoa_base(int value, int base)
{
	int		len;
	int		abs;
	int		cal;
	char	*r;

	if (base < 2 || base > 16)
		return (NULL);
	len = ft_nbrlen_base((long)value, &abs, base);
	if (!(r = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	r[len] = '\0';
	r[0] = (abs == -1 && base == 10 ? '-' : 0);
	while (--len > 0)
	{
		cal = (value % base) * abs;
		r[len] = (cal > 9 ? cal - 10 + 'A' : cal + '0');
		value /= base;
	}
	if (abs == 1 || base != 10)
	{
		cal = (value % base) * abs;
		r[len] = (cal > 9 ? cal - 10 + 'A' : cal + '0');
	}
	return (r);
}
