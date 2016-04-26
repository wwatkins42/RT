/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_intersect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 14:42:27 by wwatkins          #+#    #+#             */
/*   Updated: 2016/04/26 20:41:30 by tbeauman         ###   ########.fr       */
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
	{
		obj->in = INFINITY;
		return (INFINITY);
	}
	calc.eq = -calc.b / calc.a;
	if (calc.eq > EPSILON)
	{
		obj->in = calc.eq;
		return (calc.eq);
	}
	return (INFINITY);
}

double	intersect_sphere(t_ray *ray, t_obj *obj)
{
	t_calc	calc;

	obj->in = INFINITY;
	obj->out = INFINITY;
	calc.len = vec3_sub(ray->pos, obj->pos);
	calc.b = vec3_dot(calc.len, ray->dir);
	calc.c = vec3_dot(calc.len, calc.len) - obj->scale2;
	calc.disc = calc.b * calc.b - calc.c;
	if (calc.disc < EPSILON)
		return (INFINITY);
	calc.disc = sqrt(calc.disc);
	calc.eq = -calc.b - calc.disc;
	obj->in = calc.eq;
	obj->out = calc.eq + 2 * calc.disc;
	if (calc.eq < -EPSILON)
		calc.eq = obj->out;
	return (calc.eq);
}
double	intersect_cylinder(t_ray *ray, t_obj *obj)
{
	t_calc		calc;
	double		ro;
	double		lo;
	double		m;
	double		tmp;

	vec3_normalize(&obj->dir);
	calc.len = vec3_sub(ray->pos, obj->pos);
	ro = vec3_dot(ray->dir, obj->dir);
	lo = vec3_dot(calc.len, obj->dir);
	calc.a = 1.0 - ro * ro;
	calc.b = vec3_dot(ray->dir, calc.len) - ro * lo;
	calc.c = vec3_dot(calc.len, calc.len) - lo * lo - obj->scale * obj->scale;
	calc.disc = calc.b * calc.b - calc.a * calc.c;
	if (calc.disc < EPSILON)
	{
		obj->in = INFINITY;
		obj->out = INFINITY;
		return (INFINITY);
	}
	tmp = (-calc.b - sqrt(calc.disc)) / calc.a;
	obj->in = tmp;
	obj->out = tmp + 2 * sqrt(calc.disc);
	if (tmp < 0)
	{
		tmp = obj->out;
		if (tmp < 0){
			return (INFINITY);
		}
	}
	m = vec3_dot(ray->dir, obj->dir) * tmp +
			vec3_dot(vec3_sub(ray->pos, obj->pos), obj->dir);
	if (m > obj->y_max)
	{
		obj->in = INFINITY;
		obj->in = obj->out;
		tmp = obj->out;
		m = vec3_dot(ray->dir, obj->dir) * obj->out +
		vec3_dot(vec3_sub(ray->pos, obj->pos), obj->dir);
		obj->out = INFINITY;
		if (m > obj->y_max)
		{
			obj->in = INFINITY;
			return (INFINITY);
		}
	}
	else if (m < obj->y_min)
	{
		obj->in = INFINITY;
		obj->in = obj->out;
		tmp = obj->out;
		m = vec3_dot(ray->dir, obj->dir) * obj->out + vec3_dot(vec3_sub(ray->pos,
			obj->pos), obj->dir);
		obj->out = INFINITY;
		if (m < obj->y_min)
		{
			obj->in = INFINITY;
			return (INFINITY);
		}
	}
	obj->m = m;
	return (tmp);
}

double	intersect_cone(t_ray *ray, t_obj *obj)
{
	t_calc		calc;
	double		lo;
	double		ro;
	double		m;
	double		tmp;

	calc.len = vec3_sub(ray->pos, obj->pos);
	lo = vec3_dot(calc.len, obj->dir);
	ro = vec3_dot(ray->dir, obj->dir);
	calc.a = 1.0 - (1 + obj->k) * ro * ro;
	calc.b = vec3_dot(ray->dir, calc.len) - (1 + obj->k) * ro * lo;
	calc.c = vec3_dot(calc.len, calc.len) - (1 + obj->k) * lo * lo;
	calc.disc = calc.b * calc.b - calc.a * calc.c;
	if (calc.disc < EPSILON)
	{
		obj->in = INFINITY;
		obj->out = INFINITY;
		return (INFINITY);
	}
	tmp = (-calc.b - sqrt(calc.disc)) / calc.a;
	obj->in = tmp;
	obj->out = tmp + 2 * sqrt(calc.disc);
	if (tmp < 0)
	{
		tmp = obj->out;
		if (tmp < 0)
			return (INFINITY);
	}
	m = vec3_dot(ray->dir, obj->dir) * tmp +
			vec3_dot(vec3_sub(ray->pos, obj->pos), obj->dir);
	if (m > obj->y_max)
	{
		tmp = (-calc.b + sqrt(calc.disc)) / calc.a;
		m = vec3_dot(ray->dir, obj->dir) * tmp +
		vec3_dot(vec3_sub(ray->pos, obj->pos), obj->dir);
		if (m > obj->y_max)
			return (INFINITY);
	}
	else if (m < obj->y_min)
	{
		tmp = (-calc.b + sqrt(calc.disc)) / calc.a;
		m = vec3_dot(ray->dir, obj->dir) * tmp + vec3_dot(vec3_sub(ray->pos,
			obj->pos), obj->dir);
		if (m < obj->y_min)
			return (INFINITY);
	}
	obj->m = m;
	return (tmp);
}

t_vec3	get_quadric_normal(t_ray *ray, t_obj *q)
{
	t_vec3	ret;

	ret.x = 2 * q->co.a * ray->hit.x + q->co.d * ray->hit.y +
		q->co.e * ray->hit.z + q->co.g;
	ret.y = 2 * q->co.b * ray->hit.y + q->co.d * ray->hit.x +
		q->co.f * ray->hit.z + q->co.h;
	ret.z = 2 * q->co.c * ray->hit.z + q->co.e * ray->hit.x +
		q->co.f * ray->hit.y + q->co.i;
	if (vec3_dot(ray->hit, ray->dir) > 0)
		ret = vec3_fmul(ret, -1);
	return (ret);
}

static t_vec3 get_moebius_normal(t_ray *ray, t_obj *obj)
{
	t_vec3	ret;

	(void)obj;
	ret.x = -2 * ray->hit.z + 2 * ray->hit.x * ray->hit.y - 2 * ray->hit.x * ray->hit.z;
	ret.y = -1 + ray->hit.x * ray->hit.x + 3 * ray->hit.y * ray->hit.y - 4 * ray->hit.y * ray->hit.z + ray->hit.z * ray->hit.z;
	ret.z = -2 * ray->hit.x - 2 * ray->hit.x * ray->hit.x - 2 * ray->hit.y * ray->hit.y + 2 * ray->hit.y * ray->hit.z;
	// if (vec3_dot(ray->hit, ray->dir) > 0)
	// 	ret = vec3_fmul(ret, -1);
	return (ret);
}

// TEMPORARY
void	set_normal(t_ray *ray, t_obj *obj)
{
	if (obj->type == PLANE || obj->type == TRIANGLE
		|| obj->type == PARALLELOGRAM || obj->type == DISC)
		obj->normal = obj->dir;
	if (obj->type == MOEBIUS)
		obj->normal = get_moebius_normal(ray, obj);
	if (obj->type == SPHERE)
		obj->normal = vec3_sub(ray->hit, obj->pos);
	if (obj->type == CYLINDER ||
		obj->type == HYPERBOLOID_ONE || obj->type == HYPERBOLOID_TWO || obj->type == PARABOLOID
		)
	{
		obj->normal = vec3_sub(ray->hit, obj->pos);
		obj->normal = vec3_sub(obj->normal, vec3_fmul(obj->dir, obj->m));
	}
	// if (obj->type == PARABOLOID)
	// {
	// 	obj->normal = vec3_sub(ray->hit, obj->pos);
	// 	obj->normal = vec3_sub(obj->normal, vec3_fmul(obj->dir,
	// 			obj->scale + obj->m));
	// }
	if (obj->type == QUADRIC)
		obj->normal = get_quadric_normal(ray, obj);
	if (obj->type == CONE)
	{
		obj->normal = vec3_sub(ray->hit, obj->pos);
		obj->normal = vec3_sub(obj->normal, vec3_fmul(obj->dir,
			(1 + obj->k) * obj->m));
	}
	if (obj->type == CUBE)
		obj->normal = obj->comp[obj->comp_hit].dir;
	if (obj->type == TORUS)
	{
		// double	k = vec3_dot(vec3_sub(ray->hit, obj->pos), obj->dir);
		// t_vec3	a = vec3_sub(ray->hit, vec3_fmul(obj->dir, k));
		// double	m = sqrt(obj->pr * obj->pr - k * k);
		// obj->normal = vec3_sub(vec3_sub(ray->hit, a),
		// 	vec3_fmul(vec3_sub(obj->pos, a), m / (obj->gr + m)));
		obj->normal.x = 4 * ray->hit.x * (vec3_dot(ray->hit, ray->hit) -
			(obj->gr * obj->gr + obj->pr * obj->pr));
		obj->normal.y = 4 * ray->hit.y * (vec3_dot(ray->hit, ray->hit) -
			(obj->gr * obj->gr + obj->pr * obj->pr) + 2 * obj->gr * obj->gr);
		obj->normal.z = 4 * ray->hit.z * (vec3_dot(ray->hit, ray->hit) -
			(obj->gr * obj->gr + obj->pr * obj->pr));
	}
	vec3_normalize(&obj->normal);
}
