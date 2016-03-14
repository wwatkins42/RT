/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_intersect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 14:42:27 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/14 07:52:37 by scollon          ###   ########.fr       */
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
	//calc.a = vec3_dot(ray->dir, ray->dir);
	calc.b = vec3_dot(calc.len, ray->dir);
	calc.c = vec3_dot(calc.len, calc.len) - obj->scale2;
	calc.disc = calc.b * calc.b - /*calc.a **/ calc.c;
	if (calc.disc < EPSILON)
		return (INFINITY);
	calc.disc = sqrt(calc.disc);
	calc.eq = (-calc.b - calc.disc)/* / calc.a*/;
	if (calc.eq < -EPSILON)
		calc.eq = (-calc.b + calc.disc)/* / calc.a*/;
	return (calc.eq);
}

double	intersect_cylinder(t_ray *ray, t_obj *obj)
{
	t_calc		calc;
	double		ro; //TMP
	double		lo; //TMP

	vec3_normalize(&obj->dir);
	calc.len = vec3_sub(ray->pos, obj->pos);
	ro = vec3_dot(ray->dir, obj->dir);
	lo = vec3_dot(calc.len, obj->dir);
	calc.a = vec3_dot(ray->dir, ray->dir) - ro * ro;
	calc.b = vec3_dot(ray->dir, calc.len) - ro * lo;
	calc.c = vec3_dot(calc.len, calc.len) - lo * lo - obj->scale2; // can be done only at each modification of value.
	calc.disc = calc.b * calc.b - calc.a * calc.c;
	if (calc.disc < EPSILON)
		return (INFINITY);
	return ((-calc.b - sqrt(calc.disc)) / calc.a);
}

double	intersect_cone(t_ray *ray, t_obj *obj)
{
	t_calc		calc;
	double		k;
	double		lo; // tmp
	double		ro; // tmp

	calc.len = vec3_sub(ray->pos, obj->pos);
	k = tan(obj->scale);	// tan(obj->scale) can be done at each modification of obj-scale value
	k *= k;			// instead of each ray for each frame.
	lo = vec3_dot(calc.len, obj->dir);
	ro = vec3_dot(ray->dir, obj->dir);
	calc.a = /*vec3_dot(ray->dir, ray->dir)*/ 1.0 - (1 + k) * ro * ro;
	calc.b = vec3_dot(ray->dir, calc.len) - (1 + k) * ro * lo;
	calc.c = vec3_dot(calc.len, calc.len) - (1 + k) * lo * lo; // redondant calcul, can be done once and re-used
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
