/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 13:23:46 by scollon           #+#    #+#             */
/*   Updated: 2016/03/06 10:14:55 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

static int	print_spaces(t_a *arg, int nbrlen)
{
	int	len;

	len = 0;
	arg->prec.prec = (arg->prec.prec > nbrlen ? arg->prec.prec : nbrlen);
	arg->width -= arg->prec.prec;
	while (!arg->flag.mn && arg->width > 0 && (arg->width--))
	{
		arg->flag.zr ? write(1, "0", 1) : write(1, " ", 1);
		len++;
	}
	while ((arg->prec.prec - nbrlen) > 0 && (arg->prec.prec--))
	{
		write(1, "0", 1);
		len++;
	}
	return (len);
}

int			print_unsigned_int(unsigned long long int n, t_a *arg)
{
	int						len;
	static long long int	depth = 0;

	depth++;
	len = 1;
	if (n > 9)
		len += print_unsigned_int(n / 10, arg);
	if (n <= 9)
		len += print_spaces(arg, depth);
	print_char(n % 10 + '0');
	depth = 0;
	return (len);
}
