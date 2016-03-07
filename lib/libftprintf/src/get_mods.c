/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mods.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 15:11:14 by scollon           #+#    #+#             */
/*   Updated: 2016/03/06 10:13:38 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

int		get_mod(const char *format, int i, t_a *arg)
{
	if (is_mod(format[i]) == 1)
	{
		format[i] == 'j' ? arg->mod.j = 1 : 0;
		format[i] == 'z' ? arg->mod.z = 1 : 0;
		format[i] == 'l' ? arg->mod.l = 1 : 0;
		format[i] == 'h' ? arg->mod.h = 1 : 0;
		if (format[i] == 'l' && format[i + 1] == 'l')
		{
			i++;
			arg->mod.ll = 1;
			arg->mod.l = 0;
		}
		if (format[i] == 'h' && format[i + 1] == 'h')
		{
			i++;
			arg->mod.hh = 1;
			arg->mod.h = 0;
		}
		i++;
	}
	return (i);
}
