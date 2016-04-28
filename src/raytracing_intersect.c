/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_intersect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 14:42:27 by wwatkins          #+#    #+#             */
/*   Updated: 2016/04/28 15:48:32 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj	*intersect_object(t_env *e, t_ray *ray, double *tmin, t_obj *obj)
{
	t_obj	*out;
	double	t;
	t_obj	*r_value;

	out = NULL;
	while (obj != NULL)
	{
		t = e->intersect[obj->type](ray, obj);
		if (t > EPSILON && t < *tmin)
		{
			if (obj->type == BBOX)
			{
				if ((r_value = intersect_object(e, ray, tmin, obj->comp)))
					out = r_value;
			}
			else
			{
				out = obj;
				*tmin = t;
				out->t = t;
			}
		}
		obj = obj->next;
	}
	return (out);
}

t_vec3	get_quadric_normal(t_ray *ray, t_obj *q)
{
	t_vec3	ret;
	t_vec3	real;

	real = vec3_sub(ray->hit, q->pos);
	ret.x = 2 * q->co.a * real.x + q->co.d * real.y +
		q->co.e * real.z + q->co.g;
	ret.y = 2 * q->co.b * real.y + q->co.d * real.x +
		q->co.f * real.z + q->co.h;
	ret.z = 2 * q->co.c * real.z + q->co.e * real.x +
		q->co.f * real.y + q->co.i;
	// if (vec3_dot(real, ray->dir) > 0)
	// 	ret = vec3_fmul(ret, -1);
	return (ret);
}

static t_vec3 get_moebius_normal(t_ray *ray, t_obj *obj)
{
	t_vec3	ret;
	t_vec3	real;

	real = vec3_sub(ray->hit, obj->pos);
	ret.x = -2 * real.z + 2 * real.x * real.y - 2 * real.x * real.z;
	ret.y = -1 + real.x * real.x + 3 * real.y * real.y - 4 * real.y * real.z + real.z * real.z;
	ret.z = -2 * real.x - 2 * real.x * real.x - 2 * real.y * real.y + 2 * real.y * real.z;
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
	if (obj->type == CHEWINGGUM)
	{
		obj->normal.x = 4 * pow(ray->hit.x - obj->pos.x, 3);
		obj->normal.y = 4 * pow(ray->hit.y - obj->pos.y, 3);
		obj->normal.z = 4 * pow(ray->hit.z - obj->pos.z, 3);
	}
	if (obj->type == CYLINDER || obj->type == HYPERBOLOID_ONE ||
		obj->type == HYPERBOLOID_TWO || obj->type == PARABOLOID)
	{
		obj->normal = vec3_sub(ray->hit, obj->pos);
		obj->normal = vec3_sub(obj->normal, vec3_fmul(obj->dir, obj->m));
	}
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
		obj->normal.x = 4 * ray->hit.x * (vec3_dot(ray->hit, ray->hit) -
			(obj->gr + obj->pr));
		obj->normal.y = 4 * ray->hit.y * (vec3_dot(ray->hit, ray->hit) -
			(obj->gr + obj->pr) + 2 * obj->gr);
		obj->normal.z = 4 * ray->hit.z * (vec3_dot(ray->hit, ray->hit) -
			(obj->gr + obj->pr));
	}
	if (obj->mat.normal_perturbation)
		obj->normal = vec3(obj->normal.x + sin(ray->hit.x),
		obj->normal.y, obj->normal.z);
	vec3_normalize(&obj->normal);
	obj->mat.texture.normal = obj->normal;
}
