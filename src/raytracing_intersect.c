/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_intersect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 14:42:27 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/20 09:10:52 by tbeauman         ###   ########.fr       */
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
	calc.c = vec3_dot(calc.len, calc.len) - lo * lo - obj->scale * obj->scale;
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
	if (obj->type == PLANE || obj->type == TRIANGLE)
		obj->normal = obj->dir;
	if (obj->type == SPHERE || obj->type == CUBE_TROUE)
		obj->normal = vec3_sub(ray->hit, obj->pos);
	if (obj->type == TORUS)
	{
		double	k = vec3_dot(vec3_sub(ray->hit, obj->pos), obj->dir);
		t_vec3	a = vec3_sub(ray->hit, vec3_fmul(obj->dir, k));
		double	m = sqrt(obj->pr * obj->pr - k * k);
		obj->normal = vec3_sub(vec3_sub(ray->hit, a),
			vec3_fmul(vec3_sub(obj->pos, a), m / (obj->gr + m)));
		// ray->hit = vec3_sub(ray->hit, obj->pos);
		// obj->normal.x = 4 * ray->hit.x * (vec3_dot(ray->hit, ray->hit) +
		// 	obj->gr * obj->gr - obj->pr * obj->pr) - 4 * obj->gr * obj->gr *
		// 	(vec3_dot(ray->hit, ray->hit) - ray->hit.y * ray->hit.y);
		// obj->normal.x = 4 * ray->hit.x * (vec3_dot(ray->hit, ray->hit) +
		// 	obj->gr * obj->gr - obj->pr * obj->pr);
		// obj->normal.x = 4 * ray->hit.x * (vec3_dot(ray->hit, ray->hit) +
		// 	obj->gr * obj->gr - obj->pr * obj->pr) - 4 * obj->gr * obj->gr *
		// 	(vec3_dot(ray->hit, ray->hit) - ray->hit.y * ray->hit.y);
		// ray->hit = vec3_add(ray->hit, obj->pos);
	}
	if (obj->type == CYLINDER || obj->type == CONE ||
		obj->type == HYPERBOLOID_ONE || obj->type == HYPERBOLOID_TWO)
	{
		double	m = vec3_dot(ray->dir, obj->dir) * ray->t +
			vec3_dot(vec3_sub(obj->pos, ray->pos), obj->dir);
		obj->normal = (t_vec3){ray->hit.x - obj->pos.x,
							   ray->hit.y - obj->pos.y,
						   	   -ray->hit.z + obj->pos.z};
	}
	if (obj->type == TRIANGLE)
		obj->normal = vec3_norm(vec3_cross(obj->pos2, obj->pos3));
	// if (obj->type == CUBE_TROUE)
	// {
	// 	t_vec3	x = vec3_sub(ray->hit, obj->pos);
	// 	obj->normal = (t_vec3){4 * ft_pow(x.x, 3) - 10 * x.x,
	// 		4 * ft_pow(x.y, 3) - 10 * x.y,
	// 		4 * ft_pow(x.z, 3) - 10 * x.z};
	// }
	vec3_normalize(&obj->normal);
}
