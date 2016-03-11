/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg_notype.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 16:11:12 by scollon           #+#    #+#             */
/*   Updated: 2016/03/08 19:45:12 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

void		print_arg_notype(t_e *e, t_a *arg, int *i)
{
	if (arg->prec.pt && arg->width == 0)
	{
		write(arg->out, &arg->type, 1);
		*i += 1;
		return ;
	}
	arg->width--;
	while (!arg->flag.mn && arg->width-- > 0)
	{
		arg->flag.zr ? write(arg->out, "0", 1) : write(arg->out, " ", 1);
		e->plen++;
	}
	write(arg->out, &arg->type, 1);
	*i += 1;
	while (arg->flag.mn && arg->width-- > 0)
	{
		write(arg->out, " ", 1);
		e->plen++;
	}
}
