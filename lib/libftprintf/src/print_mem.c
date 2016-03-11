/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 16:47:28 by scollon           #+#    #+#             */
/*   Updated: 2016/03/08 19:48:04 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

int		print_mem(void *p, t_a *arg)
{
	int	len;
	int	plen;

	len = 2;
	plen = len + nbr_len_base((long)p, 16);
	arg->width -= plen;
	while (!arg->flag.mn && !arg->flag.zr && --arg->width >= 0 && (len++))
		arg->flag.zr ? write(arg->out, "0", 1) : write(arg->out, " ", 1);
	write(arg->out, "0x", 2);
	if (!(arg->prec.pt && arg->prec.prec == 0))
		len += print_base(arg, (long)p, 16, 'a');
	while ((arg->flag.mn || arg->flag.zr) && --arg->width >= 0 && (len++))
		arg->flag.zr ? write(arg->out, "0", 1) : write(arg->out, " ", 1);
	while ((arg->prec.prec - plen + 2) > 0)
	{
		write(arg->out, "0", 1);
		arg->prec.prec--;
		len++;
	}
	return (len);
}
