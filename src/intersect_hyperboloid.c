/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_hyperboloid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 19:30:12 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/29 16:53:44 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	intersect_hyperboloid1(t_ray *ray, t_obj *o)
{
	t_calc	calc;

	o->in = INFINITY;
	o->out = INFINITY;
	calc.len = vec3_sub(ray->pos, o->pos);
	calc.a = ray->dir.x * ray->dir.x - ray->dir.y * ray->dir.y +
		ray->dir.z * ray->dir.z;
	calc.b = calc.len.x * ray->dir.x - calc.len.y * ray->dir.y +
		calc.len.z * ray->dir.z;
	calc.c = calc.len.x * calc.len.x - calc.len.y * calc.len.y +
		calc.len.z * calc.len.z - o->scale * o->scale;
	calc.disc = calc.b * calc.b - calc.a * calc.c;
	if (calc.disc < EPSILON)
		return (INFINITY);
	calc.disc = sqrt(calc.disc);
	calc.eq = (-calc.b - calc.disc) / calc.a;
	o->in = calc.eq;
	o->out = (-calc.b + calc.disc) / calc.a;
	if (calc.eq < EPSILON)
	{
		calc.eq = o->out;
		if (calc.eq < EPSILON)
			return (INFINITY);
	}
	return (compute_m(ray, o, is_vec3_nul(o->cut) ? o->dir : o->cut, calc.eq));
}

double	intersect_hyperboloid2(t_ray *ray, t_obj *o)
{
	t_calc	calc;

	o->in = INFINITY;
	o->out = INFINITY;
	calc.len = vec3_sub(ray->pos, o->pos);
	calc.a = ray->dir.x * ray->dir.x - ray->dir.y * ray->dir.y +
		ray->dir.z * ray->dir.z;
	calc.b = calc.len.x * ray->dir.x - calc.len.y * ray->dir.y +
		calc.len.z * ray->dir.z;
	calc.c = calc.len.x * calc.len.x - calc.len.y * calc.len.y +
		calc.len.z * calc.len.z + o->scale * o->scale;
	calc.disc = calc.b * calc.b - calc.a * calc.c;
	if (calc.disc < EPSILON)
		return (INFINITY);
	calc.disc = sqrt(calc.disc);
	calc.eq = (-calc.b - calc.disc) / calc.a;
	o->in = calc.eq;
	o->out = (-calc.b + calc.disc) / calc.a;
	if (calc.eq < EPSILON)
	{
		calc.eq = o->out;
		if (calc.eq < EPSILON)
			return (INFINITY);
	}
	return (compute_m(ray, o, is_vec3_nul(o->cut) ? o->dir : o->cut, calc.eq));
}
