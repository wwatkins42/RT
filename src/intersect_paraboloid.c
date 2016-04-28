/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_paraboloid.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 22:32:06 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/28 22:26:38 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** DO NOT ERASE TEH COMMENT
*/

// double	intersect_paraboloid(t_ray *ray, t_obj *o)
// {
// 	t_calc	c;
// 	double	xv;
// 	double	dv;
//
// 	o->in = INFINITY;
// 	o->out = INFINITY;
// 	c.len = vec3_sub(ray->pos, o->pos);
// 	xv = vec3_dot(c.len, o->dir);
// 	dv = vec3_dot(ray->dir, o->dir);
// 	c.a = vec3_dot(ray->dir, ray->dir) - dv * dv;
// 	c.b = vec3_dot(ray->dir, c.len) - dv * (xv + 2 * o->scale);
// 	c.c = vec3_dot(c.len, c.len) - xv * (xv + 4 * o->scale);
// 	c.disc = c.b * c.b - c.a * c.c;
// 	if (c.disc < EPSILON)
// 		return (INFINITY);
// 	c.disc = sqrt(c.disc);
// 	c.eq = (-c.b - c.disc) / c.a;
// 	o->in = c.eq;
// 	o->out = (-c.b + c.disc) / c.a;
// 	if (c.eq < 0)
// 	{
// 		c.eq = o->out;
// 		if (c.eq < 0)
// 			return (INFINITY);
// 	}
// 	return (compute_m(ray, o, c.eq));
// }

// double	intersect_paraboloid(t_ray *ray, t_obj *o)
// {
// 	t_calc	c;
//
// 	o->in = INFINITY;
// 	o->out = INFINITY;
// 	c.len = vec3_sub(ray->pos, o->pos);
// 	c.a = ray->dir.x * ray->dir.z;
// 	c.b = ray->dir.x * c.len.z + ray->dir.z * c.len.x - ray->dir.y;
// 	c.c = c.len.x * c.len.z - c.len.y;
// 	c.disc = c.b * c.b - 4 * c.a * c.c;
// 	if (c.disc < EPSILON)
// 		return (INFINITY);
// 	c.disc = sqrt(c.disc);
// 	c.eq = (-c.b - c.disc) / (2 * c.a);
// 	o->in = c.eq;
// 	o->out = (-c.b + c.disc) / (2 * c.a);
// 	if (c.eq < 0)
// 	{
// 		c.eq = o->out;
// 		if (c.eq < 0)
// 			return (INFINITY);
// 	}
// 	// t_vec3 hit = vec3_add(ray->pos, vec3_fmul(ray->hit, c.eq));
// 	// if (hit.x > 1 || hit.y > 1 || hit.x < -1 || hit.y < -1 || hit.z < -1 || hit.z > 1)
// 		// return (INFINITY);
// 	return (c.eq);
// }

double	intersect_paraboloid(t_ray *ray, t_obj *o)
{
	t_calc	c;

	o->in = INFINITY;
	o->out = INFINITY;
	c.len = vec3_sub(ray->pos, o->pos);
	c.a = ray->dir.x * ray->dir.x - ray->dir.z * ray->dir.z;
	c.b = 2 * (ray->dir.x * c.len.x - ray->dir.z * c.len.z) + ray->dir.y;
	c.c = c.len.x * c.len.x - c.len.z * c.len.z + c.len.y;
	c.disc = c.b * c.b - 4 * c.a * c.c;
	if (c.disc < EPSILON)
		return (INFINITY);
	c.disc = sqrt(c.disc);
	c.eq = (-c.b - c.disc) / (2 * c.a);
	o->in = c.eq;
	o->out = (-c.b + c.disc) / (2 * c.a);
	if (c.eq < 0)
	{
		c.eq = o->out;
		if (c.eq < 0)
			return (INFINITY);
	}
	// t_vec3 hit = vec3_add(ray->pos, vec3_fmul(ray->hit, c.eq));
	// if (hit.x > 1 || hit.y > 1 || hit.x < -1 || hit.y < -1 || hit.z < -1 || hit.z > 1)
	// 	return (INFINITY);
	return (c.eq);
}
