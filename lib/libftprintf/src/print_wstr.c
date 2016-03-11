/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 12:03:48 by scollon           #+#    #+#             */
/*   Updated: 2016/03/08 19:49:33 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

static int	wchar_t_str_len(const wchar_t *s)
{
	int	len;

	len = 0;
	while (*s)
		len += nbr_binary(*s++);
	return (len);
}

static int	wstr_len(const wchar_t *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int			print_wstr(const wchar_t *s, t_a *arg)
{
	int		i;
	int		ret;
	int		len;
	int		len_unicode;

	i = arg->prec.prec > wstr_len(s) ? wstr_len(s) : arg->prec.prec;
	len = wchar_t_str_len(s);
	if (arg->prec.pt == 1 && arg->prec.prec == 0)
		return (arg->width);
	arg->prec.prec = (arg->prec.prec == 0 || arg->prec.prec > len ? len :
			arg->prec.prec);
	len_unicode = arg->prec.prec - (arg->prec.prec % nbr_binary(s[i - 1]));
	len = arg->width > arg->prec.prec ? arg->width : len_unicode;
	arg->prec.pt == 0 ? len = wchar_t_str_len(s) : 0;
	ret = arg->width;
	arg->width -= len_unicode;
	while (!arg->flag.mn && arg->width-- > 0)
		arg->flag.zr ? write(arg->out, "0", 1) : write(arg->out, " ", 1);
	len_unicode = nbr_binary(*s);
	while (*s != 0 && arg->prec.prec >= len_unicode && (print_wchar(arg, *s++)))
		len_unicode += nbr_binary(*s);
	while (arg->flag.mn && arg->width-- > 0 && (len++))
		arg->flag.zr ? write(arg->out, "0", 1) : write(arg->out, " ", 1);
	return (ret > len ? ret : len);
}
