/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 19:52:39 by scollon           #+#    #+#             */
/*   Updated: 2016/03/13 10:42:19 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

int			ft_printf_fd(const int fd, const char *format, ...)
{
	t_e		e;
	t_a		arg;

	e.alen = 0;
	e.plen = 0;
	e.out = fd;
	va_start(e.ap, format);
	while (format && format[e.alen] != 0)
	{
		if (format[e.alen] == '%')
		{
			++e.alen;
			if (parse_format(&format[e.alen], &arg, &e) == -1)
				return (e.plen == 0 ? 0 : e.plen);
			arg.null == 0 ? e.plen += print_arg(&e, &arg) : 0;
		}
		else
		{
			write(e.out, &format[e.alen++], 1);
			e.plen++;
		}
	}
	va_end(e.ap);
	return (e.plen);
}
