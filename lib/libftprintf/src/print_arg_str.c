/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 11:16:50 by scollon           #+#    #+#             */
/*   Updated: 2016/03/08 19:45:26 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

void		print_arg_str(t_e *e, t_a *arg, int *i)
{
	while (arg->prec.pt && arg->prec.prec == 0 && arg->width > 0)
	{
		arg->flag.zr ? write(arg->out, "0", 1) : write(arg->out, " ", 1);
		arg->width--;
		e->plen++;
	}
	if (arg->mod.l || arg->type == 'S')
		*i = print_wstr(va_arg(e->ap, wchar_t *), arg);
	else
		*i = print_str(va_arg(e->ap, char *), arg);
}
