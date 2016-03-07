/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:10:11 by wwatkins          #+#    #+#             */
/*   Updated: 2016/01/03 12:35:51 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	int		i;
	int		sign;
	int		size;
	char	*new;

	size = ft_nbrlen(n);
	sign = (n < 0 ? 1 : 0);
	if (!(new = ft_strnew(size + sign)))
		return (NULL);
	if (n == -2147483648)
		return (ft_strcpy(new, "-2147483648"));
	i = -1;
	(n < 0 ? n *= -1 : 0);
	while (++i < size)
	{
		new[i] = n % 10 + '0';
		n /= 10;
	}
	(sign == 1 ? new[size] = '-' : 0);
	return (ft_strrev(new, size + sign));
}
