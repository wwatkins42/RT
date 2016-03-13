/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 15:19:26 by scollon           #+#    #+#             */
/*   Updated: 2016/03/13 11:48:27 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

int			check_err(t_a *arg)
{
	if (arg->type == '\0')
		return (-1);
	if (arg->flag.zr == 1 && arg->flag.mn == 1)
		arg->flag.zr = 0;
	if (arg->flag.zr == 1 && arg->prec.pt == 1 && (arg->type == 'd' ||
		arg->type == 'i' || arg->type == 'u' || arg->type == 'x' ||
		arg->type == 'X' || arg->type == 'D'))
		arg->flag.zr = 0;
	if (arg->flag.sp == 1 && arg->flag.pl == 1)
		arg->flag.sp = 0;
	if (arg->type == 'f')
	{
		arg->flag.pl = 0;
		arg->flag.zr = 0;
		arg->flag.di = 0;
		arg->flag.sp = 0;
		arg->flag.mn = 0;
		arg->prec.pt = 0;
		arg->prec.prec = 0;
	}
	return (0);
}
