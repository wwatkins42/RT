/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_hyperboloid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 19:30:12 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/30 17:58:09 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	intersect_hyperboloid1(t_ray *ray, t_obj *o)
{
	double	a[3];
	double	roots[2];
	int		ret;
	t_vec3	x;

	o->in = INFINITY;
	o->out = INFINITY;
	x = ray->pos;
 	a[2] = ray->dir.x * ray->dir.x - ray->dir.y * ray->dir.y +
		ray->dir.z * ray->dir.z;
	a[1] = 2 * (x.x * ray->dir.x - x.y * ray->dir.y +
		x.z * ray->dir.z);
	a[0] = x.x * x.x - x.y * x.y +
		x.z * x.z - o->scale2;
	if (!(ret = solve_quadratic(a, roots)))
		return (INFINITY);
	o->in = roots[0];
	o->out = roots[1];
	if (o->in < EPSILON)
	{
		o->in = o->out;
		if (o->in < EPSILON)
			return (INFINITY);
	}
	return (compute_m(ray, o, is_vec3_nul(o->cut) ? o->dir : o->cut));
}

double	intersect_hyperboloid2(t_ray *ray, t_obj *o)
{
	double	a[3];
	double	roots[2];
	int		ret;
	t_vec3	x;

	o->in = INFINITY;
	o->out = INFINITY;
	x = ray->pos;
	a[2] = ray->dir.x * ray->dir.x - ray->dir.y * ray->dir.y +
		ray->dir.z * ray->dir.z;
	a[1] = 2 * (x.x * ray->dir.x - x.y * ray->dir.y +
		x.z * ray->dir.z);
	a[0] = x.x * x.x - x.y * x.y +
		x.z * x.z + o->scale2;
	if (!(ret = solve_quadratic(a, roots)))
		return (INFINITY);
	o->in = roots[0];
	o->out = roots[1];
	if (o->in < EPSILON)
	{
		o->in = o->out;
		if (o->in < EPSILON)
			return (INFINITY);
	}
	return (compute_m(ray, o, is_vec3_nul(o->cut) ? o->dir : o->cut));
}
