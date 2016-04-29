/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_hyperboloid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 19:30:12 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/28 21:04:13 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
/*
double	intersect_hyperboloid1(t_ray *r, t_obj *o)
{
	t_calc	c;
	double	ac;
	double	bc;
	double	cc;

	ac = o->scale * o->scale;
	bc = o->scaleo->scale2;
	cc = o->scale3 * o->scale3;
	c.a = (bc * cc * r->dir.x * r->dir.x + ac * cc * r->dir.y * r->dir.y -
		ac * bc * r->dir.z * r->dir.z) * ac * bc * cc;
	c.b = (bc * cc * r->pos.x * r->dir.x + ac * cc * r->pos.y * r->dir.y -
		ac * bc * r->pos.z * r->pos.z) * ac * bc * cc * 2;
	c.c = (bc * cc * r->pos.x * r->pos.x + ac * cc * r->pos.y * r->pos.y -
		ac * bc * r->pos.z * r->pos.z - 1) * ac * bc * cc;
	c.disc = c.b * c.b - 4 * c.a * c.c;
	if (c.disc < EPSILON)
		return (INFINITY);
	c.disc = sqrt(c.disc);
	c.eq = (-c.b - sqrt(c.disc)) / 2 * c.a;
	if (c.eq < 0)
		return (INFINITY);
	return (c.eq);
}
*/
double	intersect_hyperboloid1(t_ray *ray, t_obj *obj)
{
	t_calc	calc;

	obj->in = INFINITY;
	obj->out = INFINITY;
	calc.len = vec3_sub(ray->pos, obj->pos);
	calc.a = ray->dir.x * ray->dir.x - ray->dir.y * ray->dir.y +
		ray->dir.z * ray->dir.z;
	calc.b = calc.len.x * ray->dir.x - calc.len.y * ray->dir.y +
		calc.len.z * ray->dir.z;
	calc.c = calc.len.x * calc.len.x - calc.len.y * calc.len.y +
		calc.len.z * calc.len.z - obj->scale * obj->scale;
	calc.disc = calc.b * calc.b - calc.a * calc.c;
	if (calc.disc < EPSILON)
		return (INFINITY);
	calc.disc = sqrt(calc.disc);
	calc.eq = (-calc.b - calc.disc) / calc.a;
	obj->in = calc.eq;
	obj->out = (-calc.b + calc.disc) / calc.a;
	if (calc.eq < -EPSILON)
	{
		calc.eq = obj->out;
		if (calc.eq < -EPSILON)
			return (INFINITY);
	}
	return (compute_m(ray, obj, calc.eq));
}

double	intersect_hyperboloid2(t_ray *ray, t_obj *obj)
{
	t_calc	calc;

	obj->in = INFINITY;
	obj->out = INFINITY;
	calc.len = vec3_sub(ray->pos, obj->pos);
	calc.a = ray->dir.x * ray->dir.x - ray->dir.y * ray->dir.y +
		ray->dir.z * ray->dir.z;
	calc.b = calc.len.x * ray->dir.x - calc.len.y * ray->dir.y +
		calc.len.z * ray->dir.z;
	calc.c = calc.len.x * calc.len.x - calc.len.y * calc.len.y +
		calc.len.z * calc.len.z + obj->scale * obj->scale;
	calc.disc = calc.b * calc.b - calc.a * calc.c;
	if (calc.disc < EPSILON)
		return (INFINITY);
	calc.disc = sqrt(calc.disc);
	calc.eq = (-calc.b - calc.disc) / calc.a;
	obj->in = calc.eq;
	obj->out = (-calc.b + calc.disc) / calc.a;
	if (calc.eq < -EPSILON)
	{
		calc.eq = obj->out;
		if (calc.eq < -EPSILON)
			return (INFINITY);
	}
	return (compute_m(ray, obj, calc.eq));
}
