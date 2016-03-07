/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 10:26:32 by scollon           #+#    #+#             */
/*   Updated: 2016/03/06 10:14:58 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

static int	nbr_binary_b(unsigned int v)
{
	int i;

	i = 1;
	while (v >>= 1)
		i++;
	return (i);
}

int			print_wchar(unsigned int c)
{
	int				n;
	int				ret;

	n = nbr_binary_b(c);
	ret = 0;
	if (n > 7)
	{
		if (n > 11)
		{
			if (n > 16)
			{
				ret += print_char(((c >> 18) & 7) | 240);
				ret += print_char(((c >> 12) & 63) | 128);
			}
			else
				ret += print_char(((c >> 12) & 15) | 224);
			ret += print_char(((c >> 6) & 63) | 128);
		}
		else
			ret += print_char(((c >> 6) & 31) | 192);
		ret += print_char((c & 63) | 128);
	}
	else
		ret += print_char(c);
	return (ret);
}
