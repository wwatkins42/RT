/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_selle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 16:54:28 by tbeauman          #+#    #+#             */
/*   Updated: 2016/05/03 12:29:51 by tbeauman         ###   ########.fr       */
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
	double	a[5];
	int		ret;

	o->in = INFINITY;
	o->out = INFINITY;
	a[2] = ray->dir.x * ray->dir.x - ray->dir.z * ray->dir.z;
	a[1] = 2 * (ray->dir.x * ray->pos.x - ray->dir.z * ray->pos.z) + ray->dir.y;
	a[0] = ray->pos.x * ray->pos.x - ray->pos.z * ray->pos.z + ray->pos.y;
	if (!(ret = solve_quadratic(a, &a[3])))
		return (INFINITY);
	o->in = a[3];
	o->out = a[4];
	if (o->in < 0)
	{
		o->in = o->out;
		if (o->in < 0)
			return (INFINITY);
	}
	return (cut_selle(ray, o, o->in));
}

t_vec3			selle_normal(t_vec3 *hit, t_obj *o)
{
	t_vec3	ret;

	(void)o;
	ret.x = 2 * hit->x;
	ret.z = -2 * hit->z;
	ret.y = 1;
	return (ret);
}
