/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_quadric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 07:02:45 by tbeauman          #+#    #+#             */
/*   Updated: 2016/05/02 18:43:25 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_calc		init_quadric_calc(t_ray *ray, t_obj *obj)
{
	t_calc	c;

	c.len = ray->pos;
	c.a = obj->co.a * ray->dir.x * ray->dir.x + obj->co.b * ray->dir.y *
		ray->dir.y + obj->co.c * ray->dir.z * ray->dir.z + obj->co.d *
		ray->dir.x * ray->dir.y + obj->co.e * ray->dir.x * ray->dir.z +
		obj->co.f * ray->dir.y * ray->dir.z;
	c.b = 2 * (ray->dir.x * c.len.x * obj->co.a + ray->dir.y * c.len.y *
		obj->co.b + ray->dir.z * c.len.z * obj->co.c) + obj->co.d * (ray->dir.x
		* c.len.y + ray->dir.y * c.len.x) + obj->co.e * (ray->dir.x * c.len.z +
		ray->dir.z * c.len.x) + obj->co.f * (ray->dir.y * c.len.z + ray->dir.z
		* c.len.y) + obj->co.g * ray->dir.x + obj->co.h * ray->dir.y + obj->co.i
		* ray->dir.z;
	c.c = obj->co.a * c.len.x * c.len.x + obj->co.b * c.len.y * c.len.y +
		obj->co.c * c.len.z * c.len.z + obj->co.d * c.len.x * c.len.y +
		obj->co.e * c.len.x * c.len.z + obj->co.f * c.len.y * c.len.z
		+ obj->co.g * c.len.x + obj->co.h * c.len.y + obj->co.i * c.len.y
		+ obj->co.j;
	return (c);
}

double		intersect_quadric(t_ray *ray, t_obj *obj)
{
	t_calc	c;

	c = init_quadric_calc(ray, obj);
	if (c.a == 0)
	{
		if (c.b)
			obj->t = -c.c / c.b;
		else
			obj->t = c.c ? -1 : 0;
		return (obj->t);
	}
	c.disc = c.b * c.b - 4 * c.a * c.c;
	if (c.disc < EPSILON)
		return (INFINITY);
	c.disc = sqrt(c.disc);
	c.eq = -c.b - c.disc;
	if (c.eq < -EPSILON)
		c.eq = -c.b + c.disc;
	obj->t = c.eq;
	return (c.eq);
}

t_vec3		quadric_normal(t_vec3 *real, t_obj *q)
{
	t_vec3	ret;

	ret.x = 2 * q->co.a * real->x + q->co.d * real->y +
		q->co.e * real->z + q->co.g;
	ret.y = 2 * q->co.b * real->y + q->co.d * real->x +
		q->co.f * real->z + q->co.h;
	ret.z = 2 * q->co.c * real->z + q->co.e * real->x +
		q->co.f * real->y + q->co.i;
	return (ret);
}
