/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_intersect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 14:42:27 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/17 18:54:19 by tbeauman         ###   ########.fr       */
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
	calc.b = vec3_dot(calc.len, ray->dir);
	calc.c = vec3_dot(calc.len, calc.len) - obj->scale2;
	calc.disc = calc.b * calc.b - calc.c;
	if (calc.disc < EPSILON)
		return (INFINITY);
	calc.disc = sqrt(calc.disc);
	calc.eq = -calc.b - calc.disc;
	if (calc.eq < -EPSILON)
		calc.eq = -calc.b + calc.disc;
	return (calc.eq);
}

double	intersect_cylinder(t_ray *ray, t_obj *obj)
{
	t_calc		calc;
	double		ro;
	double		lo;

	vec3_normalize(&obj->dir);
	calc.len = vec3_sub(ray->pos, obj->pos);
	ro = vec3_dot(ray->dir, obj->dir);
	lo = vec3_dot(calc.len, obj->dir);
	calc.a = 1.0 - ro * ro;
	calc.b = vec3_dot(ray->dir, calc.len) - ro * lo;
	calc.c = vec3_dot(calc.len, calc.len) - lo * lo - obj->scale2;
	calc.disc = calc.b * calc.b - calc.a * calc.c;
	if (calc.disc < EPSILON)
		return (INFINITY);
	return ((-calc.b - sqrt(calc.disc)) / calc.a);
}

double	intersect_cone(t_ray *ray, t_obj *obj)
{
	t_calc		calc;
	double		lo;
	double		ro;

	calc.len = vec3_sub(ray->pos, obj->pos);
	lo = vec3_dot(calc.len, obj->dir);
	ro = vec3_dot(ray->dir, obj->dir);
	calc.a = 1.0 - (1 + obj->k) * ro * ro;
	calc.b = vec3_dot(ray->dir, calc.len) - (1 + obj->k) * ro * lo;
	calc.c = vec3_dot(calc.len, calc.len) - (1 + obj->k) * lo * lo;
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
		obj->normal = vec3_sub(ray->hit, obj->pos);
	if (obj->type == CYLINDER || obj->type == CONE)
		obj->normal = vec3(obj->pos.x - ray->hit.x, 0.0,
		obj->pos.z - ray->hit.z);
	if (obj->type == TRIANGLE)
		obj->normal = vec3_norm(vec3_cross(obj->pos2, obj->pos3));
	vec3_normalize(&obj->normal);
}
