/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_paraboloid.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 22:32:06 by tbeauman          #+#    #+#             */
/*   Updated: 2016/05/02 11:27:10 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	intersect_paraboloid(t_ray *ray, t_obj *o)
{
	double	a[5];
	double	xv;
	double	dv;
	t_vec3	x;
	int		ret;

	o->in = INFINITY;
	o->out = INFINITY;
	x = ray->pos;
	xv = vec3_dot(x, o->dir);
	dv = vec3_dot(ray->dir, o->dir);
	a[2] = vec3_dot(ray->dir, ray->dir) - dv * dv;
	a[1] = 2 * (vec3_dot(ray->dir, x) - dv * (xv + 2 * o->scale));
	a[0] = vec3_dot(x, x) - xv * (xv + 4 * o->scale);
	if (!(ret = solve_quadratic(a, &a[3])))
		return (INFINITY);
	o->in = a[3];
	o->out = a[4];
	if (o->in < 0 && ((o->in = o->out) || 1))
		if (o->in < 0)
			return (INFINITY);
	return (compute_m(ray, o, is_vec3_nul(o->cut) ? o->dir : o->cut));
}

t_vec3	paraboloid_normal(t_vec3 *hit, t_obj *obj)
{
	t_vec3	ret;

	ret = *hit;
	ret = vec3_sub(ret, vec3_fmul(obj->dir, obj->m + obj->scale));
	return (ret);
}
