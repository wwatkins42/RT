/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 08:53:58 by scollon           #+#    #+#             */
/*   Updated: 2016/03/08 19:44:05 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

static void	init_arg(t_a *arg, int out)
{
	arg->flag.pl = 0;
	arg->flag.mn = 0;
	arg->flag.sp = 0;
	arg->flag.di = 0;
	arg->flag.zr = 0;
	arg->width = 0;
	arg->prec.pt = 0;
	arg->prec.prec = 0;
	arg->mod.h = 0;
	arg->mod.hh = 0;
	arg->mod.l = 0;
	arg->mod.ll = 0;
	arg->mod.j = 0;
	arg->mod.z = 0;
	arg->type = '\0';
	arg->null = 0;
	arg->out = out;
}

static void	printpad(t_a *arg, t_e *e, int before)
{
	if (arg->flag.mn == 0 && before == 1)
	{
		while (arg->width - arg->prec.prec > 0)
		{
			arg->flag.zr ? write(1, "0", 1) : write(1, " ", 1);
			arg->width--;
			e->plen++;
		}
	}
	else if (arg->flag.mn == 1 && before == 0)
	{
		while (arg->width - arg->prec.prec > 0)
		{
			arg->flag.zr ? write(1, "0", 1) : write(1, " ", 1);
			arg->width--;
			e->plen++;
		}
	}
}

static void	check_arg(t_e *e, t_a *arg)
{
	va_list copy;

	va_copy(copy, e->ap);
	if (arg->type == 's' || (arg->type == 'S'))
	{
		if ((va_arg(copy, char *)) == NULL)
		{
			arg->null = 1;
			(arg->prec.pt == 0 && arg->prec.prec < 6) ? arg->prec.prec = 6 : 0;
			arg->prec.prec > 6 ? arg->prec.prec = 6 : 0;
			printpad(arg, e, 1);
			write(1, "(null)", arg->prec.prec);
			e->plen += arg->prec.prec;
			va_arg(e->ap, wchar_t*);
			printpad(arg, e, 0);
		}
	}
	va_end(copy);
}

int			parse_format(const char *format, t_a *arg, t_e *e)
{
	int	i;

	i = 0;
	init_arg(arg, e->out);
	i = get_flags(format, i, arg);
	i = get_width(format, i, arg);
	i = get_prec(format, i, arg);
	i = get_mod(format, i, arg);
	arg->type = format[i];
	i += 1;
	if ((check_err(arg) == -1))
		return (-1);
	check_arg(e, arg);
	e->alen += i;
	return (0);
}
