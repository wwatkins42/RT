/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solving_polyn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 08:04:55 by tbeauman          #+#    #+#             */
/*   Updated: 2016/03/21 23:26:28 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rt.h"
#define SIGN(x) x < 0 ? -1 : 1
#define EPSILON 1e-9

void	fix_zeros(t_poly6 *p)
{
	int		i;

	i = 0;
	while (i < 7)
	{
		if (fabs(p->a[i]) < EPSILON)
			p->a[i] = 0;
		i++;
	}
}

int 		est_polynome_nul(t_poly6 p)
{
	int 	i;

	i = 0;
	while (i < 7)
	{
		if (fabs(p.a[i]) > EPSILON)
			return (0);
		i++;
	}
	return (1);
}

int			degree(t_poly6 p)
{
	int		ret;

	if (est_polynome_nul(p))
		return (-1);
	ret = 6;
	while (fabs(p.a[ret]) < EPSILON)
		ret--;
	return (ret);
}

void	print_poly(t_poly6 p, char *name)
{
	int i = 0;
	int d = degree(p);

	if (d == -1)
		{
			printf("%s: 0\n", name);
			return ;
		}
	printf("%s: %f%s", name, p.a[0], d == 0 ? "\n" : " + ");
	while (++i < d + 1)
		printf("%f*x^%d%s", p.a[i], i, i == d ? "\n" : " + ");
}

t_poly6		poly_sub(t_poly6 p, t_poly6 q)
{
	t_poly6	ret;
	int		i;

	i = 0;
	while (i < 7)
	{
		ret.a[i] = p.a[i] - q.a[i];
		i++;
	}
	fix_zeros(&ret);
	return (ret);
}

t_poly6		poly_mult(t_poly6 p, t_poly6 q)
{
	t_poly6	ret;
	int		i;
	int		m;

	i = 0;
	while (i < 7)
	{
		m = 0;
		ret.a[i] = 0;
		while (m <= i)
		{
			ret.a[i] += p.a[m] * q.a[i - m];
			m++;
		}
		i++;
	}
	fix_zeros(&ret);
	return (ret);
}

t_poly6		poly_smult(t_poly6 p, double scal)
{
	t_poly6	ret;
	int		i;

	i = 0;
	while (i < 7)
	{
		ret.a[i] = p.a[i] * scal;
		i++;
	}
	fix_zeros(&ret);
	return (ret);
}

t_euclid	division(t_poly6 a, t_poly6 b)
{
	int			da;
	int			db;
	int			u = 1;
	t_euclid	ret;

	db = degree(b);
	ret.q = (t_poly6){{0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
	ret.r = (t_poly6){{0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
	while (degree(ret.r) >= db || u)
	{
		da = degree(a);
		ret.q.a[da - db] = a.a[da] / b.a[db];
		ret.r = poly_sub(a, poly_mult(b, ret.q));
		fix_zeros(&ret.r);
		a = ret.r;
		ret.q.a[da-db] = 0;
		u = 0;
	}
	return (ret);
}

void	print_suite_poly(t_poly6 *s)
{
	int i = 0;
	while (i < 7 && degree(s[i]) != -1)
	{
		printf("s[%d]", i);
		print_poly(s[i], "");
		i++;
	}
}

t_sturm		cree_suite_poly(t_poly6 p)
{
	t_poly6	*s;
	t_sturm	ret;
	int		i;

	if (!(s = (t_poly6*)malloc(sizeof(t_poly6) * 8)))
		return ((t_sturm){NULL, -1});
	s[0] = p;
	s[1] = (t_poly6)
	{{p.a[1], 2 * p.a[2], 3 * p.a[3], 4 * p.a[4], 5 * p.a[5], 6 *p.a[6], 0},
	{0, 0, 0, 0, 0, 0}};
	i = 2;
	while (i < 8 && degree(s[i - 1]) != -1)
	{
		s[i] = poly_smult(division(s[i - 2], s[i - 1]).r, -1);
		fix_zeros(&s[i]);
		// printf("s[%d]", i);
		// print_poly(s[i], "");
		i++;
	}
	ret.s = s;
	ret.len = i - 1;
	return (ret);
}

double	eval_poly(t_poly6 p, double x)
{
	return (x == 0 ? p.a[0] :
			p.a[6] ? p.a[6] * x * x * x * x * x * x : 0 +
			p.a[5] ? p.a[5] * x * x * x * x * x : 0 +
			p.a[4] ? p.a[4] * x * x * x * x : 0 +
			p.a[3] ? p.a[3] * x * x * x : 0 +
			p.a[2] ? p.a[2] * x * x : 0 +
			p.a[1] ? p.a[1] * x : 0 +
			p.a[0]);
}

int		nombre_cs(double x, t_sturm suite)
{
	double		eval[8];
	int			i;
	int			ret;
	int			ps;

	i = 0;
	while (i < suite.len)
	{
		ps = degree(suite.s[i]);
		if (x == INFINITY)
			eval[i] = suite.s[i].a[ps];
		else
			eval[i] = eval_poly(suite.s[i], x);
		// printf("%c%f%s", i == 0 ? '(' : ' ', eval[i], i == suite.len - 1 ? ")\n" : " ");
		i++;
	}
	ret = 0;
	i = 1;
	ps = SIGN(eval[0]);
	// printf("(%d ", ps);
	while (i < suite.len)
	{
		if ((eval[i] < 0 && eval[i - 1] > 0) || (eval[i] > 0 && eval[i - 1] < 0))
		{
			// printf("|");
			ret++;
		}
		// else
			// ret++;
		// printf("%c%d%s", ' ', SIGN(eval[i]), i == suite.len - 1 ? ")\n" : " ");
		// ps = SIGN(eval[i]);
		i++;
	}
	return (ret);
}

int 	number_roots(t_poly6 p)
{
	t_sturm		suite;
	int			a;
	int 		b;

	suite = cree_suite_poly(p);
	if (p.a[0] != 0)
		a = nombre_cs(0, suite);
	else
		return (1);
	b = nombre_cs(INFINITY, suite);
	return (a - b);
}

// int		main(int ac, char **av)
// {
// 	t_poly6		p;
// 	t_poly6		pprime;
// 	t_sturm		suite;
// 	t_euclid	divi;
// 	int			i;
// 	int			a;
// 	int			b;
//
// 	i = 0;
// 	while (++i < ac)
// 		p.a[i - 1] = atof(av[i]);
// 	while (i++ < 7)
// 		p.a[i - 1] = 0;
// 	print_poly(p, "s[0]");
// 	pprime = (t_poly6)
// 	{{p.a[1], 2 * p.a[2], 3 * p.a[3], 4 * p.a[4], 5 * p.a[5], 6 *p.a[6], 0},
// 	{0, 0, 0, 0, 0, 0}};
// 	print_poly(pprime, "s[1]");
// 	suite = cree_suite_poly(p);
// 	a = nombre_cs(0, suite);
// 	b = nombre_cs(1, suite);
// 	printf("cs(0): %d\n", a);
// 	printf("cs(1): %d\n", b);
// 	printf("cs(0) - cs(inf) = %d\n", a - b);
// }
