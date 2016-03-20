/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solving_polyn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 08:04:55 by tbeauman          #+#    #+#             */
/*   Updated: 2016/03/20 11:12:20 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EPSILON 1e-9

typedef struct		s_poly6
{
	double			a[7];
	double			root[6];
}					t_poly6;

typedef struct		s_euclid
{
	t_poly6			q;
	t_poly6			r;
}					t_euclid;

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
	printf("%s: %f%s", name, p.a[0], d == 0 ? "\n" : " + ");
	while (++i < d + 1)
		printf("%f*X^%d%s", p.a[i], i, i == d ? "\n" : " + ");
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

t_poly6	*cree_suite_poly(t_poly6 p)
{
	t_poly6	*s;
	int		i;

	if (!(s = (t_poly6*)malloc(sizeof(t_poly6) * 7)))
		return (NULL);
	s[0] = p;
	s[1] = (t_poly6)
	{{p.a[1], 2 * p.a[2], 3 * p.a[3], 4 * p.a[4], 5 * p.a[5], 6 *p.a[6], 0},
	{0, 0, 0, 0, 0, 0}};
	i = 2;
	while (i < 7 && degree(s[i - 1]) != -1)
	{
		s[i] = poly_smult(division(s[i - 2], s[i - 1]).r, -1);
		i++;
	}
	return (s);
}

int		main(int ac, char **av)
{
	t_poly6		p;
	t_poly6		pprime;
	t_poly6		*suite;
	t_euclid	divi;
	int			i;

	i = 0;
	while (++i < ac)
		p.a[i - 1] = atof(av[i]);
	while (i++ < 7)
		p.a[i - 1] = 0;
	print_poly(p, "A");
	pprime = (t_poly6)
	{{p.a[1], 2 * p.a[2], 3 * p.a[3], 4 * p.a[4], 5 * p.a[5], 6 *p.a[6], 0},
	{0, 0, 0, 0, 0, 0}};
	print_poly(pprime, "B");
	divi = division(p, pprime);
	print_poly(divi.q, "Q");
	print_poly(divi.r, "R");
	suite = cree_suite_poly(p);
}
