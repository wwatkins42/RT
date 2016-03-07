/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:08:50 by wwatkins          #+#    #+#             */
/*   Updated: 2015/11/29 17:35:19 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1t;
	unsigned char	*s2t;

	i = 0;
	s1t = (unsigned char*)s1;
	s2t = (unsigned char*)s2;
	while (s1t[i] == s2t[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1t[i] - (unsigned char)s2t[i]);
}
