/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 10:26:32 by scollon           #+#    #+#             */
/*   Updated: 2016/03/08 19:52:00 by scollon          ###   ########.fr       */
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

int			print_wchar(t_a *arg, unsigned int c)
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
				ret += print_char(arg, ((c >> 18) & 7) | 240);
				ret += print_char(arg, ((c >> 12) & 63) | 128);
			}
			else
				ret += print_char(arg, ((c >> 12) & 15) | 224);
			ret += print_char(arg, ((c >> 6) & 63) | 128);
		}
		else
			ret += print_char(arg, ((c >> 6) & 31) | 192);
		ret += print_char(arg, (c & 63) | 128);
	}
	else
		ret += print_char(arg, c);
	return (ret);
}
