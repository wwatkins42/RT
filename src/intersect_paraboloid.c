/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_paraboloid.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 22:32:06 by tbeauman          #+#    #+#             */
/*   Updated: 2016/03/23 11:51:54 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	intersect_paraboloid(t_ray *ray, t_obj *o)
{
	t_calc	c;
	double	xv;
	double	dv;
	double	m;
	t_vec3	hit;

	c.len = vec3_sub(ray->pos, o->pos);
	xv = vec3_dot(c.len, o->dir);
	dv = vec3_dot(ray->dir, o->dir);

	c.a = 1 - dv * dv;
	c.b = 2 * (vec3_dot(ray->dir, c.len) - dv * (xv + 2 * o->scale));
	c.c = vec3_dot(c.len, c.len) - xv * (xv + 4 * o->scale);
	c.disc = c.b * c.b - 4 * c.a * c.c;
	if (c.disc < EPSILON)
		return (INFINITY);
	c.disc = sqrt(c.disc);
	c.eq = (-c.b - c.disc) / 2 * c.a;
	if (c.eq < 0)
	{
		c.eq += c.disc / c.a;
		if (c.eq < 0)
			return (INFINITY);
	}
	hit = vec3_add(vec3_fmul(ray->dir, c.eq), ray->pos);
	m = vec3_dot(vec3_sub(hit, o->pos), o->dir);
	// m = vec3_dot(ray->dir, o->dir) * c.eq +
	// 		vec3_dot(vec3_sub(ray->pos, o->pos), o->dir);
	if (m > o->y_max)
	{
		c.eq = (-c.b + c.disc) / c.a;
		hit = vec3_add(vec3_fmul(ray->dir, c.eq), ray->pos);
		m = vec3_dot(vec3_sub(hit, o->pos), o->dir);

		// m = vec3_dot(ray->dir, o->dir) * c.eq +
		// vec3_dot(vec3_sub(ray->pos, o->pos), o->dir);
		if (m > o->y_max)
			return (INFINITY);
	}
	else if (m < o->y_min)
	{
		c.eq = (-c.b + c.disc) / c.a;
		hit = vec3_add(vec3_fmul(ray->dir, c.eq), ray->pos);
		m = vec3_dot(vec3_sub(hit, o->pos), o->dir);
// m = vec3_dot(ray->dir, o->dir) * c.eq + vec3_dot(vec3_sub(ray->pos,
// 			o->pos), o->dir);
		if (m < o->y_min)
			return (INFINITY);
	}
	o->m = m;
	return (c.eq);
}
