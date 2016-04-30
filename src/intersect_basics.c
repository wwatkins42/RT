/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_basics.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 11:43:17 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/30 19:40:51 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	compute_m(t_ray *r, t_obj *o, t_vec3 d)
{
	double		m;

	o->m = 0;
	m = vec3_dot(r->dir, d) * o->in + vec3_dot(r->pos, d);
	if (m > o->max || m < o->min)
	{
		o->in = o->out;
		o->out = INFINITY;
		m = vec3_dot(r->dir, d) * o->in + vec3_dot(r->pos, d);
		if (m < o->max && m > o->min && ((o->m = m) || 1))
			return (o->in);
		else if ((o->in = INFINITY))
			return (INFINITY);
	}
	o->m = m;
	return (o->in);
}

double	intersect_cylinder(t_ray *ray, t_obj *obj)
{
	double		a[3];
	double		roots[2];
	double		ro;
	double		lo;
	t_vec3		x;
	int			ret;

	obj->in = INFINITY;
	obj->out = INFINITY;
	vec3_normalize(&obj->dir);
	x = ray->pos;
	ro = vec3_dot(ray->dir, obj->dir);
	lo = vec3_dot(x, obj->dir);
	a[2] = 1.0 - ro * ro;
	a[1] = 2 * (vec3_dot(ray->dir, x) - ro * lo);
	a[0] = vec3_dot(x, x) - lo * lo - obj->scale * obj->scale;
	if (!(ret = solve_quadratic(a, roots)))
		return (INFINITY);
	obj->in = roots[0];
	obj->out = roots[1];
	if (obj->in < 0 && ((obj->in = obj->out) || 1))
		if (obj->in < 0)
			return (INFINITY);
	return (compute_m(ray, obj, is_vec3_nul(obj->cut) ? obj->dir : obj->cut));
}

double	intersect_cone(t_ray *ray, t_obj *obj)
{
	double		lo;
	double		ro;
	double		a[3];
	double		roots[2];
	t_vec3		x;
	int			ret;

	obj->in = INFINITY;
	obj->out = INFINITY;
	x = ray->pos;
	lo = vec3_dot(x, obj->dir);
	ro = vec3_dot(ray->dir, obj->dir);
	a[2] = 1.0 - (1 + obj->k) * ro * ro;
	a[1] = 2 * (vec3_dot(ray->dir, x) - (1 + obj->k) * ro * lo);
	a[0] = vec3_dot(x, x) - (1 + obj->k) * lo * lo;
	if (!(ret = solve_quadratic(a, roots)))
		return (INFINITY);
	obj->in = roots[0];
	obj->out = roots[1];
	if (obj->in < 0 && ((obj->in = obj->out) || 1))
		if (obj->in < 0)
			return (INFINITY);
	return (compute_m(ray, obj, is_vec3_nul(obj->cut) ? obj->dir : obj->cut));
}

double	intersect_plane(t_ray *ray, t_obj *obj)
{
	t_calc	calc;

	obj->in = INFINITY;
	obj->out = INFINITY;
	calc.a = vec3_dot(obj->dir, ray->dir);
	calc.b = vec3_dot(obj->dir, vec3_sub(ray->pos, obj->pos));
	if (calc.a == 0)
		return (INFINITY);
	calc.eq = -calc.b / calc.a;
	if (calc.eq > 0 && (obj->in = calc.eq))
		return (calc.eq);
	else
		return (INFINITY);
}

double	intersect_sphere(t_ray *ray, t_obj *obj)
{
	t_calc	calc;

	obj->in = INFINITY;
	obj->out = INFINITY;
	calc.len = vec3_sub(ray->pos, obj->pos);
	calc.b = vec3_dot(calc.len, ray->dir);
	calc.c = vec3_dot(calc.len, calc.len) - obj->scale2;
	calc.disc = calc.b * calc.b - calc.c;
	if (calc.disc < EPSILON)
		return (INFINITY);
	calc.disc = sqrt(calc.disc);
	calc.eq = -calc.b - calc.disc;
	obj->in = calc.eq;
	obj->out = calc.eq + 2 * calc.disc;
	if (calc.eq < -EPSILON)
		calc.eq = obj->out;
	return (calc.eq);
}
