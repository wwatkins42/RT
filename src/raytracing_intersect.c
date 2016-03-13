/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_intersect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 14:42:27 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/13 13:08:34 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj	*intersect_object(t_env *e, t_ray *ray, double *tmin)
{
	t_obj	*obj;
	t_obj	*out;
	double	t;

	out = NULL;
	obj = e->obj;
	while (obj != NULL)
	{
		t = e->intersect[obj->type](ray, obj);
		if (t > EPSILON && t < *tmin)
		{
			out = obj;
			*tmin = t;
			out->t = t;
		}
		obj = obj->next;
	}
	return (out);
}

double	intersect_plane(t_ray *ray, t_obj *obj)
{
	t_calc	calc;

	calc.a = vec3_dot(obj->dir, ray->dir);
	calc.b = vec3_dot(obj->dir, vec3_sub(ray->pos, obj->pos));
	if (calc.a == 0)
		return (INFINITY);
	return (-calc.b / calc.a > 0 ? -calc.b / calc.a : -1);
}

double	intersect_sphere(t_ray *ray, t_obj *obj)
{
	t_calc	calc;

	calc.len = vec3_sub(ray->pos, obj->pos);
	calc.a = vec3_dot(ray->dir, ray->dir);
	calc.b = 2.0 * vec3_dot(calc.len, ray->dir);
	calc.c = vec3_dot(calc.len, calc.len) - obj->scale * obj->scale;
	calc.disc = calc.b * calc.b - 4.0 * calc.a * calc.c;
	if (calc.disc < EPSILON)
		return (INFINITY);
	calc.eq = (-calc.b - sqrt(calc.disc)) / (2.0 * calc.a);
	if (calc.eq < -EPSILON)
		calc.eq = (-calc.b + sqrt(calc.disc)) / (2.0 * calc.a);
	return (calc.eq);
}

double	intersect_cylinder(t_ray *ray, t_obj *obj)
{
	t_calc		calc;

	vec3_normalize(&obj->dir);
	calc.len = vec3_sub(ray->pos, obj->pos);
	calc.a = vec3_dot(ray->dir, ray->dir) - vec3_dot(ray->dir, obj->dir) *
		vec3_dot(ray->dir, obj->dir);
	calc.b = vec3_dot(ray->dir, calc.len) - vec3_dot(ray->dir, obj->dir) *
		vec3_dot(calc.len, obj->dir);
	calc.c = vec3_dot(calc.len, calc.len) - vec3_dot(calc.len, obj->dir) *
		vec3_dot(calc.len, obj->dir) - obj->scale * obj->scale;
	calc.disc = calc.b * calc.b - calc.a * calc.c;
	if (calc.disc < EPSILON)
		return (INFINITY);
	return ((-calc.b - sqrt(calc.disc)) / calc.a);
}

double	intersect_cone(t_ray *ray, t_obj *obj)
{
	t_calc		calc;
	double		k;

	calc.len = vec3_sub(ray->pos, obj->pos);
	k = tan(obj->scale) * tan(obj->scale);
	calc.a = vec3_dot(ray->dir, ray->dir) - (1 + k) *
		vec3_dot(ray->dir, obj->dir) * vec3_dot(ray->dir, obj->dir);
	calc.b = vec3_dot(ray->dir, calc.len) - (1 + k) *
		vec3_dot(ray->dir, obj->dir) * vec3_dot(calc.len, obj->dir);
	calc.c = vec3_dot(calc.len, calc.len) - (1 + k) *
		vec3_dot(calc.len, obj->dir) * vec3_dot(calc.len, obj->dir);
	calc.disc = calc.b * calc.b - calc.a * calc.c;
	if (calc.disc < EPSILON)
		return (INFINITY);
	return ((-calc.b - sqrt(calc.disc)) / calc.a);
}

// TEMPORARY
void	set_normal(t_ray *ray, t_obj *obj)
{
	if (obj->type == PLANE)
		obj->normal = obj->dir;
	if (obj->type == SPHERE)
		obj->normal = vec3_sub(obj->pos, ray->hit);
	if (obj->type == CYLINDER || obj->type == CONE)
		obj->normal = vec3(obj->pos.x - ray->hit.x, 0.0,
		obj->pos.z - ray->hit.z);
	vec3_normalize(&obj->normal);
}
