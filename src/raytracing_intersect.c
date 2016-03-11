/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_intersect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 14:42:27 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/11 17:02:09 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj	*intersect_object(t_env *e, t_ray ray, double *tmin)
{
	t_obj	*obj;
	t_obj	*out;
	double	t;

	out = NULL;
	obj = e->obj;
	while ((obj = obj->next) != NULL)
	{
		t = e->intersect[obj->type](ray, obj);
		if (t > EPSILON && t < *tmin)
		{
			out = obj;
			*tmin = t;
		}
	}
	return (out);
}

double	intersect_plane(t_ray ray, t_obj *obj)
{
	double	t;

	t = -((vec3_dot(obj->dir, ray.pos) - vec3_dot(obj->dir, obj->pos)) /
		vec3_dot(obj->dir, ray.dir));
	if (t < EPSILON)
		return (-1.0);
	return (t);
}

double	intersect_sphere(t_ray ray, t_obj *obj)
{
	double	a;
	double	b;
	double	c;
	double	disc;
	t_vec3	len;

	len = vec3_sub(ray.pos, obj->pos);
	a = vec3_dot(ray.dir, ray.dir);
	b = vec3_dot(len, ray.dir);
	c = vec3_dot(len, len) - obj->scale;
	disc = b * b - a * c;
	if (disc < EPSILON)
		return (-1.0);
	return ((-b - sqrt(disc)) / a);
}

double	intersect_cone(t_ray ray, t_obj *obj)
{
	double	a;
	double	b;
	double	c;
	double	disc;
	t_vec3	len;

	len = vec3_sub(ray.pos, obj->pos);
	a = ray.dir.x * ray.dir.x - ray.dir.y * ray.dir.y + ray.dir.z * ray.dir.z;
	b = ray.dir.x * len.x - ray.dir.y * len.y + ray.dir.z * len.z;
	c = len.x * len.x + len.z * len.z - len.y * len.y;
	disc = b * b - a * c;
	if (disc < EPSILON)
		return (-1.0);
	return ((-b - sqrt(disc)) / a);
}

double	intersect_cylinder(t_ray ray, t_obj *obj)
{
	double	a;
	double	b;
	double	c;
	double	disc;
	t_vec3	len;

	len = vec3_sub(ray.pos, obj->pos);
	a = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
	b = (ray.dir.x * len.x + ray.dir.z * len.z);
	c = len.x * len.x + len.z * len.z - obj->scale;
	disc = b * b - a * c;
	if (disc < EPSILON)
		return (-1.0);
	return ((-b - sqrt(disc)) / a);
}

// TEMPORARY
void	set_normal(t_ray ray, t_obj *obj)
{
	if (obj->type == PLANE)
		obj->normal = vec3_sub(obj->pos, obj->dir);
	if (obj->type == SPHERE)
		obj->normal = vec3_sub(obj->pos, ray.hit);
	if (obj->type == CYLINDER || obj->type == CONE)
		obj->normal = vec3(obj->pos.x - ray.hit.x, 0.0, obj->pos.z - ray.hit.z);
	vec3_normalize(&obj->normal);
}
