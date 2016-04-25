/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_moebius.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 11:01:19 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/25 22:00:29 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	calculate_third_equation(double a, double b, double c, double d)
{
	double f;
	double g;
	double h;

	f = ((3 * (c / a)) - (b * b / (a * a))) / 3;
	g = (((2 * b * b * b) / (a * a * a)) - ((9 * b * c) / (a * a)) + (27 * d / a)) / 27;
	h = (g * g / 4) + (f * f * f / 27);
	if (h > 0)
		return (1);
	else if (h <= 0)
		return (3);
	return (0);
}

double	min(double a, double b, double c)
{
	if (a < b)
	{
		if (b < c)
			return (a);
		else
		{
			if (a < c)
				return (a);
			else
				return (c);
		}
	}
	return (b);
}

double solve_three_solutions(double a, double b, double g, double h)
{
	double i;
	double j;
	double k;
	double l;
	double m;
	double n;
	double p;
	double x1;
	double x2;
	double x3;

	i = sqrt((g * g / 4) - h);
	j = cbrt(i);
	k = acos(-g / (2 * i));
	l = -j;
	m = cos(k / 3);
	n = sqrt(3) * sin(k / 3);
	p = -b / (3 * a);
	x1 = 2 * j * cos(k / 3) - (b / (3 * a));
	x2 = l * (m + n) + p;
	x3 = l * (m - n) + p;
	x1 = (x1 < EPSILON ? INFINITY : x1);
	x2 = (x2 < EPSILON ? INFINITY : x2);
	x3 = (x3 < EPSILON ? INFINITY : x3);

	return (min(x1, x2, x3));
	/*if ((x2 < x1 && x2 > 0) || x1 <= 0)
		x1 = x2;
	if ((x3 < x1 && x3 > 0) || x1 <= 0)
		x1 = x3;*/
/*	if (x1 > x2)
	{
		if (x1 > x3)
			return (x1);
		else
			return (x3);
	}
	else
	{
		if (x2 > x3)
			return (x2);
		else
			return (x3);
	}*/
	//return (x3);
/*	if (x1 < x2)
	{
		if (x1 < x3)
			return (x1);
		else
			return (x3);
	}
	else
	{
		if (x2 < x3)
			return (x2);
		else
			return (x3);
	}*/
//	return (x2);
	//printf("x1 = %f\n", x1);
	//printf("x2 = %f\n", x2);
	//printf("x3 = %f\n", x3);
//	return (x3);
}

double solve_one_solution(double a, double b, double c, double d)
{
	double f;
	double g;
	double h;
	double r;
	double s;
	double t;
	double u;
	double x1;

	f = ((3 * c / a) - (b * b / (a * a))) / 3;
	g = ((2 * b * b * b / (a * a * a)) - (9 * b * c / (a * a)) + (27 * d / a)) / 27;
	h = (g * g / 4) + (f * f * f / 27);
	r = -g / 2 + sqrt(h);
	s = cbrt(r);
	t = -g / 2 - sqrt(h);
	u = cbrt(t);
	x1 = (s + u) - b / (3 * a);
	//other result will be unreal, so useless for the raytracing?
	//printf("x1 = %f\n", x1);
	return (x1);
}

double solve_same_solution(double a, double b, double c, double d)
{
	double f;
	double g;
	double h;
	double x1;

	f = (3 * c / a - b * b / (a * a)) / 3;
	g = (2 * b * b * b / (a * a * a) - 9 * b * c / (a * a) + 27 * d / a) / 27;
	h = g * g / 4 + f * f * f / 27;
	x1 = -cbrt(d / a);
	//printf("x1-1 = %f\n", x1);
	return (x1);
}

double calculate_cubic_equation(double a, double b, double c, double d)
{
		double f;
		double g;
		double h;

	f = ((3 * (c / a)) - (b * b / (a * a))) / 3;
	g = (((2 * b * b * b) / (a * a * a)) - ((9 * b * c) / (a * a)) + (27 * d / a)) / 27;
	h = (g * g / 4) + (f * f * f / 27);
	if (h > 0)
	    return (solve_one_solution(a, b, c, d));
	if (f == 0 && g == 0 && h == 0){
	    return (solve_same_solution(a, b, c, d));}
	else if (h <= 0)
	    return (solve_three_solutions(a, b, g, h));
	return (-1);
}

double		intersect_moebius(t_ray *ray, t_obj *obj)
{
	t_calc		calc;
//	t_calc		calc2;
	double		a;
	double		b;
	double		c;
	double		d;
	double		e;
	double		f;
	double		g;
	double		result;

//t^3 * (-2 * c^2 * g+e * c^2+e * g^2-2 * e^2 * g+e^3)
//t^2 (-2* a* c *g+2 *b *c *e-4 *b *c *g+c^2 *d-2 *c^2 *f+3 *d *e^2-4 *d *e *g-2 *e^2 *f + d *g^2+2* e *f *g)
//t*(a^2 * (-e) - 2 *a* b *g-2* a *c *f+b^2 *e-2 *b^2 *g+2 *b *c* d-4 *b *c *f+3 *d^2* e-2 *d^2 *g + 2 *d *f*g-4*e*d*f+e*f^2)
//-a^2 *d -2 *a *b* f +b^2 *d -2 *b^2 *f +d^3 -2 *d^2* f  + d* f^2
	t_vec3 x = vec3_sub(ray->pos, obj->pos);
	a = 1;
	b = x.x;
	c = ray->dir.x;
	d = x.y;
	e = ray->dir.y;
	f = x.z;
	g = ray->dir.z;
	calc.a = (-2 * c * c * g + e * c * c + e * g * g - 2 * e * e * g + e * e * e);
	calc.b = (-2 * a * c * g + 2 * b * c * e -4 * b * c * g + c * c * d -2 * c * c * f + 3 * d * e * e -4 * d * e * g-2 * e * e * f + d * g * g + 2 * e * f * g);
	calc.c = (a * a * (-e) - 2 * a * b * g -2 * a * c * f + b * b * e -2 * b * b * g + 2 * b * c * d - 4 * b * c * f + 3 * d * d * e -2 * d * d * g + 2 * d * g * f -4 * e * d * f + e * f * f);
	calc.d = -(a * a) * d - 2 * a * b * f + b * b * d -2 * b * b * f + d * d * d -2 * d * d * f + d * f * f;
	result = calculate_cubic_equation(calc.a, calc.b, calc.c, calc.d);
	/*if (calc.d > 0)
	{
		printf("ray direction x = %f, y = %f, z = %f\n", ray->dir.x, ray->dir.y, ray->dir.z);
		printf("a = %f, b = %f, c = %f, d = %f, result = %f\n", calc.a, calc.b, calc.c, calc.d, result);
	}*/
	t_vec3 hit = vec3_add(vec3_fmul(ray->dir, result), ray->pos);
	double	dist = vec3_magnitude(hit);
	if (dist > 1 && dist < 3)
		return (result < EPSILON ? INFINITY : result);
	else
		return (INFINITY);
	//a y ^ 3 + (c - (b^2 / 3a)) * y + (d + (2b^3 / 27 * a^2) - (bc / 3a)) = 0
/*	calc2.a = calc.a;
	calc2.b = (calc.c - (calc.b * calc.b / (3 * calc.a)));
	calc2.c = (calc.d + (2 * calc.b * calc.b * calc.b / (27 * calc.a * calc.a) - (calc.b * calc.c / (3 * calc.a))));*/
//	return (0);
/*	calc.len = vec3_sub(ray->pos, obj->pos);
	lo = vec3_dot(calc.len, obj->dir);
	ro = vec3_dot(ray->dir, obj->dir);
	calc.a = 1.0 - (1 + obj->k) * ro * ro;
	calc.b = vec3_dot(ray->dir, calc.len) - (1 + obj->k) * ro * lo;
	calc.c = vec3_dot(calc.len, calc.len) - (1 + obj->k) * lo * lo;
	calc.disc = calc.b * calc.b - calc.a * calc.c;
	if (calc.disc < EPSILON)
		return (INFINITY);
	return ((-calc.b - sqrt(calc.disc)) / calc.a);*/
}
