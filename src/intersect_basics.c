/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_basics.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 11:43:17 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/28 14:02:43 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	compute_m(t_ray *ray, t_obj *obj, double tmp)
{
	double		m;

	m = vec3_dot(ray->dir, obj->dir) * tmp +
		vec3_dot(vec3_sub(ray->pos, obj->pos), obj->dir);
	if (m > obj->max)
	{
		tmp = obj->out;
		obj->in = INFINITY;
		m = vec3_dot(ray->dir, obj->dir) * tmp +
			vec3_dot(vec3_sub(ray->pos, obj->pos), obj->dir);
		if (m > obj->max && (obj->out = INFINITY))
			return (INFINITY);
	}
	else if (m < obj->min)
	{
		tmp = obj->out;
		obj->in = INFINITY;
		m = vec3_dot(ray->dir, obj->dir) * tmp + vec3_dot(vec3_sub(ray->pos,
			obj->pos), obj->dir);
		if (m < obj->min && (obj->out = INFINITY))
			return (INFINITY);
	}
	obj->m = m;
	return (tmp);
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

double	intersect_cylinder(t_ray *ray, t_obj *obj)
{
	t_calc		calc;
	double		ro;
	double		lo;
	double		tmp;

	obj->in = INFINITY;
	obj->out = INFINITY;
	vec3_normalize(&obj->dir);
	calc.len = vec3_sub(ray->pos, obj->pos);
	ro = vec3_dot(ray->dir, obj->dir);
	lo = vec3_dot(calc.len, obj->dir);
	calc.a = 1.0 - ro * ro;
	calc.b = vec3_dot(ray->dir, calc.len) - ro * lo;
	calc.c = vec3_dot(calc.len, calc.len) - lo * lo - obj->scale * obj->scale;
	calc.disc = calc.b * calc.b - calc.a * calc.c;
	if (calc.disc < EPSILON)
		return (INFINITY);
	tmp = (-calc.b - sqrt(calc.disc)) / calc.a;
	obj->in = tmp;
	obj->out = tmp + 2 * calc.disc;
	if (tmp < 0 && ((tmp = obj->out) || 1))
		if (tmp < 0)
			return (INFINITY);
	return (compute_m(ray, obj, tmp));
}

double	intersect_cone(t_ray *ray, t_obj *obj)
{
	t_calc		calc;
	double		lo;
	double		ro;
	double		tmp;

	obj->in = INFINITY;
	obj->out = INFINITY;
	calc.len = vec3_sub(ray->pos, obj->pos);
	lo = vec3_dot(calc.len, obj->dir);
	ro = vec3_dot(ray->dir, obj->dir);
	calc.a = 1.0 - (1 + obj->k) * ro * ro;
	calc.b = vec3_dot(ray->dir, calc.len) - (1 + obj->k) * ro * lo;
	calc.c = vec3_dot(calc.len, calc.len) - (1 + obj->k) * lo * lo;
	calc.disc = calc.b * calc.b - calc.a * calc.c;
	if (calc.disc < EPSILON)
		return (INFINITY);
	tmp = (-calc.b - sqrt(calc.disc)) / calc.a;
	obj->in = tmp;
	obj->out = tmp + 2 * calc.disc;
	if (tmp < 0 && ((tmp = obj->out) || 1))
		if (tmp < 0)
			return (INFINITY);
	return (compute_m(ray, obj, tmp));
}
