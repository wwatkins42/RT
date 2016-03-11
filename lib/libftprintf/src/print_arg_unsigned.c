/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 13:25:14 by scollon           #+#    #+#             */
/*   Updated: 2016/03/08 19:45:34 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

static unsigned long long	unsigned_mod(t_e *e, t_a *arg)
{
	if (arg->type == 'u' && arg->mod.hh)
		return ((unsigned char)va_arg(e->ap, unsigned int));
	if (arg->type == 'u' && arg->mod.h)
		return ((unsigned short)va_arg(e->ap, unsigned int));
	if (arg->type == 'U' || (arg->type == 'u' && arg->mod.l))
		return (va_arg(e->ap, unsigned long int));
	if (arg->type == 'u' && arg->mod.ll)
		return (va_arg(e->ap, unsigned long long int));
	if (arg->type == 'u' && arg->mod.j)
		return (va_arg(e->ap, uintmax_t));
	if (arg->type == 'u' && arg->mod.z)
		return (va_arg(e->ap, size_t));
	return (va_arg(e->ap, unsigned int));
}

void						print_arg_unsigned(t_e *e, t_a *arg, int *i)
{
	unsigned long long	va;

	if (arg->prec.pt && arg->prec.prec == 0)
		return ;
	va = unsigned_mod(e, arg);
	*i = print_unsigned_int(va, arg);
	while (arg->flag.mn && arg->width > 0 && (arg->width--))
	{
		write(arg->out, " ", 1);
		(*i)++;
	}
}
