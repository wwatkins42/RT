/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 10:11:52 by scollon           #+#    #+#             */
/*   Updated: 2016/03/06 10:13:34 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

int		get_flags(const char *format, int i, t_a *arg)
{
	while (is_flag(format[i]))
	{
		format[i] == ' ' ? arg->flag.sp = 1 : 0;
		format[i] == '+' ? arg->flag.pl = 1 : 0;
		format[i] == '-' ? arg->flag.mn = 1 : 0;
		format[i] == '#' ? arg->flag.di = 1 : 0;
		format[i] == '0' ? arg->flag.zr = 1 : 0;
		i++;
	}
	return (i);
}
