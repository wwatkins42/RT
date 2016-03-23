/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quartic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 23:36:24 by tbeauman          #+#    #+#             */
/*   Updated: 2016/03/22 02:22:54 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		solve_quadratic(t_poly4 *p)
{
	double	delta;

	if (p->a2 == 0)
	{
		if (p->a1 == 0)
			return (0);
		else
		{
			p->root1 = -p->a0 / p->a1;
			return (1);
		}
	}
	delta = p->a1 * p->a1 - 4 * p->a2 * p->a0;
	if (delta < 0)
		return (0);
	else
	{
		p->root1 = (-p->a1 - sqrt(delta)) / 2 * p->a2;
		p->root2 = (-p->a1 + sqrt(delta)) / 2 * p->a2;
		return (1);
	}
}

int	solve_cubic(t_poly4 *p)
{
	double	q;
	double	qqq;
	double	r;
	double	rr;
	double	b;
	double	c;
	double	d;

	if (fabsl(p->a3) < EPSILON)
		return (solve_quadratic(p));
	d = p->a0 / p->a3;
	c = p->a1 / p->a3;
	b = p->a2 / p->a3;
	q = (b * b - c * 3) / 9;
	qqq = q * q * q;
	r = (2 * b * b * b - 9 * b * c + 27 * d) / 54;
	rr = r * r;
	if (rr < qqq)
	{
		double	theta = acos(r / sqrt(qqq));
		p->root1 = -2 * sqrt(q);
		p->root2 = -2 * sqrt(q);
		p->root3 = -2 * sqrt(q);
		p->root1 *= cos(theta / 3);
		p->root2 *= cos((theta + 2 * M_PI) / 3);
		p->root3 *= cos((theta - 2 * M_PI) / 3);
		p->root1 -= b / 3;
		p->root2 -= b / 3;
		p->root3 -= b / 3;
		return (3);
	}
	else
	{
		double	a2 = -cbrt(fabsl(r) + sqrt(rr - qqq));
		if (a2 != 0)
		{
			if (r < 0)
				a2 = -a2;
			p->root1 = a2 + q / a2;
		}
		p->root1 -= b / 3;
		return (1);
	}
	return (0);
}

int	solve_quartic(t_poly4 *p4)
{
	double	b;
	double	c;
	double	d;
	double	e;
	double	bb;
	double	i;
	double	j;
	double	k;
	t_poly4	p3;
	t_poly4	p2;
	double	z;
	int		fr = 0;
	int		far = 0;

	b = p4->a3 / p4->a4;
	c = p4->a2 / p4->a4;
	d = p4->a1 / p4->a4;
	e = p4->a0 / p4->a4;
	bb = b * b;
	i = -3 * bb * 0.125 + c; // P
	j = bb * b * 0.125 - b * c * 0.5 + d; // Q
//	 if (i > 0 || j > 0)
//		return (0);
	k = -3 * bb * bb / 256 + c * bb / 16 - b * d * 0.25 + e;
	p3.a3 = 1;
	p3.a2 = 2 * i;
	p3.a1 = i * i - 4 * k;
	p3.a0 = -j * j;
	solve_cubic(&p3);
	z = p3.root1;
	double	p = sqrt(z);
	double	r = -p;
	double	q = (i + z - j / p) / 2;
	double	s = (i + z + j / p) / 2;

	p2.a2 = 1;
	p2.a1 = p;
	p2.a0 = q;
	if ((fr = solve_quadratic(&p2)))
	{
		p4->root1 = p2.root1 - b / 4;
		p4->root2 = p2.root2 - b / 4;
	}
	p2.a2 = 1;
	p2.a1 = r;
	p2.a0 = s;
	if ((far = solve_quadratic(&p2)))
	{
		if (fr == 0)
		{
			p4->root1 = p2.root1 - b / 4;
			p4->root2 = p2.root2 - b / 4;
		}
		else
		{
			p4->root3 = p2.root1 - b / 4;
			p4->root4 = p2.root2 - b / 4;
		}
	}
	if (isnan(p4->root1))
		return (0);
	return ((fr + far) * 2);
}
