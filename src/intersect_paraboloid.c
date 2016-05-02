/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_paraboloid.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 22:32:06 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/29 16:55:20 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	intersect_paraboloid(t_ray *ray, t_obj *o)
{
	t_calc	c;
	double	xv;
	double	dv;

	o->in = INFINITY;
	o->out = INFINITY;
	c.len = vec3_sub(ray->pos, o->pos);
	xv = vec3_dot(c.len, o->dir);
	dv = vec3_dot(ray->dir, o->dir);
	c.a = vec3_dot(ray->dir, ray->dir) - dv * dv;
	c.b = vec3_dot(ray->dir, c.len) - dv * (xv + 2 * o->scale);
	c.c = vec3_dot(c.len, c.len) - xv * (xv + 4 * o->scale);
	c.disc = c.b * c.b - c.a * c.c;
	if (c.disc < EPSILON)
		return (INFINITY);
	c.disc = sqrt(c.disc);
	c.eq = (-c.b - c.disc) / c.a;
	o->in = c.eq;
	o->out = (-c.b + c.disc) / c.a;
	if (c.eq < 0 && ((c.eq = o->out) || 1))
		if (c.eq < 0)
			return (INFINITY);
	return (compute_m(ray, o, is_vec3_nul(o->cut) ? o->dir : o->cut, c.eq));
}
