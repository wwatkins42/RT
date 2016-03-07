/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_len_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 15:56:57 by scollon           #+#    #+#             */
/*   Updated: 2016/03/06 10:14:07 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

int		nbr_len_base(long n, const int base)
{
	int		len;

	len = 1;
	if (n == 0)
		return (len);
	if (n < 0)
	{
		n *= -1;
		base == 10 ? len += 1 : 0;
	}
	while ((n /= base) > 0)
		len++;
	return (len);
}
