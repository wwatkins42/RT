/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 11:10:15 by scollon           #+#    #+#             */
/*   Updated: 2016/03/06 10:14:20 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

void		print_arg_char(t_e *e, t_a *arg, int *i)
{
	wchar_t	c;

	if (arg->mod.l || arg->type == 'C')
	{
		c = va_arg(e->ap, wchar_t);
		arg->width -= nbr_binary(c);
	}
	else
		arg->width--;
	while (!arg->flag.mn && arg->width-- > 0)
	{
		arg->flag.zr ? write(1, "0", 1) : write(1, " ", 1);
		e->plen++;
	}
	if (arg->mod.l || arg->type == 'C')
		*i = print_wchar((unsigned int)c);
	else
		*i = print_char(va_arg(e->ap, int));
	while (arg->flag.mn && arg->width-- > 0)
	{
		arg->flag.zr ? write(1, "0", 1) : write(1, " ", 1);
		e->plen++;
	}
}
