/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 08:18:57 by scollon           #+#    #+#             */
/*   Updated: 2016/03/06 10:14:49 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

int		print_str(const char *s, t_a *arg)
{
	int		len;

	len = str_len(s);
	if (arg->prec.pt == 1 && arg->prec.prec == 0)
		return (arg->width);
	arg->prec.prec = (arg->prec.prec == 0 || arg->prec.prec > len ?
			len : arg->prec.prec);
	len = (arg->width > arg->prec.prec ? arg->width : arg->prec.prec);
	arg->width -= arg->prec.prec;
	while (!arg->flag.mn && arg->width-- > 0)
		arg->flag.zr ? write(1, "0", 1) : write(1, " ", 1);
	while (*s != 0 && arg->prec.prec-- > 0)
		write(1, s++, 1);
	while (arg->flag.mn && arg->width-- > 0)
		arg->flag.zr ? write(1, "0", 1) : write(1, " ", 1);
	return (len);
}
