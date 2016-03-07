/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_len_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 15:47:44 by scollon           #+#    #+#             */
/*   Updated: 2016/03/06 10:14:09 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

int		nbr_len_unsigned(unsigned long long int n)
{
	int		len;

	len = 1;
	if (n == 0)
		return (1);
	while ((n /= 10) > 0)
		len++;
	return (len);
}
