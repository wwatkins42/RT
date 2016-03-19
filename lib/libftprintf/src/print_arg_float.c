/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 11:10:43 by scollon           #+#    #+#             */
/*   Updated: 2016/03/19 10:05:52 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

static int	print_float(double f, t_a *a)
{
	int		tmp;
	int		len;

	if (f == 0)
	{
		write(a->out, "0.0", 3);
		return (3);
	}
	if (f < 0)
	{
		write(a->out, "-", 1);
		f *= -1;
		len++;
	}
	tmp = f;
	len += print_int(tmp, a);
	write(a->out, ".", 1);
	len++;
	tmp = f * 1000;
	len += print_int(tmp % 1000, a);
	return (len);
}

void		print_arg_float(t_e *e, t_a *a, int *i)
{
	double		va;

	va = va_arg(e->ap, double);
	*i = print_float(va, a);
}
