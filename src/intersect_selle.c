/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_selle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 16:54:28 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/29 17:56:58 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	cut_selle(t_ray *ray, t_obj *o, double tmp)
{
	t_vec3	hit;

	hit = vec3_add(ray->pos, vec3_fmul(ray->dir, tmp));
	if (hit.x > o->max || hit.x < o->min || hit.y > o->max || hit.y < o->min ||
		hit.z > o->max || hit.z < o->min)
	{
		hit = vec3_add(ray->pos, vec3_fmul(ray->dir, o->out));
		if (hit.x > o->max || hit.x < o->min || hit.y > o->max ||
			hit.y < o->min || hit.z > o->max || hit.z < o->min)
			return (INFINITY);
		tmp = o->out;
	}
	return (tmp);
}

double			intersect_selle(t_ray *ray, t_obj *o)
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
	return (cut_selle(ray, o, c.eq));
}
