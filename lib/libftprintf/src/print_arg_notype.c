/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg_notype.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 16:11:12 by scollon           #+#    #+#             */
/*   Updated: 2016/03/06 10:14:25 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

void		print_arg_notype(t_e *e, t_a *arg, int *i)
{
	if (arg->prec.pt && arg->width == 0)
	{
		write(1, &arg->type, 1);
		*i += 1;
		return ;
	}
	arg->width--;
	while (!arg->flag.mn && arg->width-- > 0)
	{
		arg->flag.zr ? write(1, "0", 1) : write(1, " ", 1);
		e->plen++;
	}
	write(1, &arg->type, 1);
	*i += 1;
	while (arg->flag.mn && arg->width-- > 0)
	{
		write(1, " ", 1);
		e->plen++;
	}
}
