/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_quadric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 07:02:45 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/28 12:57:20 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_calc		init_quadric_calc(t_ray *ray, t_obj *obj)
{
	t_calc	c;

	c.len = vec3_sub(ray->pos, obj->pos);
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
