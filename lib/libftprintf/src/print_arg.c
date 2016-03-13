/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 09:59:16 by scollon           #+#    #+#             */
/*   Updated: 2016/03/13 11:09:37 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf_utils.h>

int		print_arg(t_e *e, t_a *arg)
{
	int		i;

	i = 0;
	if (!is_type(arg->type))
		print_arg_notype(e, arg, &i);
	else if (arg->type == 'f')
		print_arg_float(e, arg, &i);
	else if (arg->type == 'd' || arg->type == 'i' || arg->type == 'D')
		print_arg_int(e, arg, &i);
	else if (arg->type == 'c' || arg->type == 'C')
		print_arg_char(e, arg, &i);
	else if (arg->type == 's' || arg->type == 'S')
		print_arg_str(e, arg, &i);
	else if (arg->type == 'u' || arg->type == 'U')
		print_arg_unsigned(e, arg, &i);
	else if (arg->type == 'x' || arg->type == 'X' || arg->type == 'b')
		print_arg_base(e, arg, &i);
	else if (arg->type == 'o' || arg->type == 'O')
		print_arg_base(e, arg, &i);
	else if (arg->type == 'p')
		print_arg_ptr(e, arg, &i);
	return (i);
}
