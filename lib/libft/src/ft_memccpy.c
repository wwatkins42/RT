/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 10:02:39 by wwatkins          #+#    #+#             */
/*   Updated: 2015/11/29 18:00:12 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dstt;
	unsigned char	*srct;

	i = 0;
	dstt = (unsigned char*)dst;
	srct = (unsigned char*)src;
	while (i < n)
	{
		if ((*dstt++ = *srct++) == (unsigned char)c)
			return (dstt);
		i++;
	}
	return (NULL);
}
