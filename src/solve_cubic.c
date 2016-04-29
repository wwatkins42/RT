/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_cubic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 11:26:40 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/27 12:20:13 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Finds the real roots of x^3 + a[2] x^2 + a[1] x + a[0] = 0
** arranging them ordered in r and returning the number of the roots (1 or 3)
*/

static t_cubic	init_stru(double *a)
{
	t_cubic	ret;

	ret.q = a[2] * a[2] - 3 * a[1];
	ret.r = 2 * a[2] * a[2] * a[2] - 9 * a[2] * a[1] + 27 * a[0];
	ret.bq = ret.q / 9;
	ret.br = ret.r / 54;
	ret.bq3 = ret.bq * ret.bq * ret.bq;
	ret.br2 = ret.br * ret.br;
	ret.cr2 = 729 * ret.r * ret.r;
	ret.cq3 = 2916 * ret.q * ret.q * ret.q;
	ret.sgnbr = ret.br >= 0 ? 1 : -1;
	ret.i = 0;
	return (ret);
}

static int		solve_second_case(t_cubic c, double *a, double *r)
{
	c.sqrtbq = sqrt(c.bq);
	if (c.br > 0)
	{
		r[0] = -2 * c.sqrtbq - a[2] / 3;
		r[1] = c.sqrtbq - a[2] / 3;
		r[2] = c.sqrtbq - a[2] / 3;
	}
	else
	{
		r[0] = -c.sqrtbq - a[2] / 3;
		r[1] = -c.sqrtbq - a[2] / 3;
		r[2] = 2 * c.sqrtbq - a[2] / 3;
	}
	return (3);
}

static int		solve_third_case(t_cubic c, double *a, double *r)
{
	c.ratio = c.sgnbr * sqrt(c.br2 / c.bq3);
	c.theta = acos(c.ratio);
	c.norm = -2 * sqrt(c.bq);
	c.r0 = c.norm * cos(c.theta / 3) - a[2] / 3;
	c.r1 = c.norm * cos((c.theta + 2.0 * M_PI) / 3) - a[2] / 3;
	c.r2 = c.norm * cos((c.theta - 2.0 * M_PI) / 3) - a[2] / 3;
	if (c.r0 > c.r1)
		swapd(&c.r0, &c.r1);
	if (c.r1 > c.r2)
	{
		swapd(&c.r1, &c.r2);
		if (c.r0 > c.r1)
			swapd(&c.r0, &c.r1);
	}
	r[0] = c.r0;
	r[1] = c.r1;
	r[2] = c.r2;
	return (3);
}

static int		solve_fourth_case(t_cubic c, double *a, double *r)
{
	c.ba = -c.sgnbr * pow(fabs(c.br) + sqrt(c.br2 - c.bq3), 1.0 / 3.0);
	c.bb = c.bq / c.ba;
	r[0] = c.ba + c.bb - a[2] / 3;
	return (1);
}

int				solve_cubic(double *a, double *r)
{
	t_cubic		c;

	c = init_stru(a);
	if (c.br == 0 && c.bq == 0)
	{
		while (c.i++ < 3)
			r[c.i] = -a[2] / 3;
		return (3);
	}
	else if (c.cr2 == c.cq3)
		return (solve_second_case(c, a, r));
	else if (c.br2 < c.bq3)
		return (solve_third_case(c, a, r));
	else
		return (solve_fourth_case(c, a, r));
}
