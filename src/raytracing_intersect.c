/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_intersect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 14:42:27 by wwatkins          #+#    #+#             */
/*   Updated: 2016/04/30 19:44:20 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		is_non_directed_object(t_obj *obj)
{
	return (obj->type != SPHERE && obj->type != PLANE && obj->type != CONE
	&& obj->type != CYLINDER && obj->type != PARABOLOID && obj->type != CUBE &&
	obj->type != BBOX && obj->type != TRIANGLE && obj->type != PARALLELOGRAM &&
	obj->type != DISC);
	return (obj->type == MOEBIUS || obj->type == CUBE_TROUE || obj->type ==
	HYPERBOLOID_ONE || obj->type == HYPERBOLOID_TWO || obj->type == CHEWINGGUM
	|| obj->type == TORUS || obj->type == QUADRIC || obj->type == CSG);
}

t_obj	*intersect_object(t_env *e, t_ray *ray, double *tmin, t_obj *obj)
{
	t_obj	*out;
	double	t;
	t_obj	*r_value;
	t_ray	tray;

	out = NULL;
	while (obj != NULL)
	{
		tray = *ray;
		tray.pos = vec3_sub(ray->pos, obj->pos);
		// if (is_non_directed_object(obj))
		// {
			vec3_inverse_rotate(&tray.pos, obj->rot);
			vec3_inverse_rotate(&tray.dir, obj->rot);
		// }
		t = e->intersect[obj->type](&tray, obj);
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

t_vec3	get_quadric_normal(t_vec3 real, t_obj *q)
{
	t_vec3	ret;

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

static t_vec3 get_moebius_normal(t_vec3 real, t_obj *obj)
{
	t_vec3	ret;
	// t_vec3	real;

	// real = vec3_sub(ray->hit, obj->pos);
	ret.x = -2 * obj->scale * real.z + 2 * real.x * real.y - 2 * real.x * real.z;
	ret.y = -obj->scale2 + real.x * real.x + 3 * real.y * real.y - 4 * real.y *
		real.z + real.z * real.z;
	ret.z = -2 * obj->scale * real.x - 2 * real.x * real.x - 2 * real.y * real.y
		+ 2 * real.y * real.z;
	return (ret);
}

// TEMPORARY
void	set_normal(t_ray *ray, t_obj *obj)
{
	t_vec3	tr;

	tr = vec3_sub(ray->hit, obj->pos);
	// if (is_non_directed_object(obj))
		vec3_inverse_rotate(&tr, obj->rot);
	if (obj->type == PLANE || obj->type == TRIANGLE
		|| obj->type == PARALLELOGRAM || obj->type == DISC)
		obj->normal = obj->dir;
	if (obj->type == MOEBIUS)
		obj->normal = get_moebius_normal(tr, obj);
	if (obj->type == SPHERE)
		obj->normal = tr;
	if (obj->type == CHEWINGGUM)
	{
		obj->normal.x = 4 * pow(tr.x, 3);
		obj->normal.y = 4 * pow(tr.y, 3);
		obj->normal.z = 4 * pow(tr.z, 3);
	}
	if (obj->type == CYLINDER)
	{
		obj->normal = tr;
		/*
		**CA DOIT ETRE LA
		*/
		obj->normal = vec3_sub(obj->normal, vec3_fmul(obj->dir, obj->m));
	}
	if (obj->type == HYPERBOLOID_ONE ||
		obj->type == HYPERBOLOID_TWO)
	{
		obj->normal = (t_vec3){tr.x,
			-tr.y, tr.z};
	}
	if (obj->type == PARABOLOID)
	{
		// DO NOT... ERASE
		obj->normal = tr;
		/*
		**CA DOIT ETRE LA
		*/
		obj->normal = vec3_sub(obj->normal,
			vec3_fmul(obj->dir, obj->m + obj->scale));
		/*
		** SELLE DE CHEVAL Z=XY
		*/
		// obj->normal.x = ray->hit.z;
		// obj->normal.y = -1;
		// obj->normal.z = ray->hit.x;
		/*
		** SELLE DE CHEVAL Z=Y2-X2
		*/
		// obj->normal.x = 2 * ray->hit.x;
		// obj->normal.z = -2 * ray->hit.z;
		// obj->normal.y = 1;
	}
	if (obj->type == QUADRIC)
		obj->normal = get_quadric_normal(tr, obj);
	if (obj->type == CONE)
	{
		obj->normal = tr;
		/*
		**CA DOIT ETRE LA
		*/
		obj->normal = vec3_sub(obj->normal, vec3_fmul(obj->dir,
			(1 + obj->k) * obj->m));
	}
	if (obj->type == CUBE)
		obj->normal = obj->comp[obj->comp_hit].dir;
	if (obj->type == TORUS)
	{
		obj->normal.x = 4 * tr.x * (vec3_dot(tr, tr) -
			(obj->gr + obj->pr));
		obj->normal.y = 4 * tr.y * (vec3_dot(tr, tr) -
			(obj->gr + obj->pr) + 2 * obj->gr);
		obj->normal.z = 4 * tr.z * (vec3_dot(tr, tr) -
			(obj->gr + obj->pr));
	}
	if (obj->type == CUBE_TROUE)
	{
		obj->normal.x = 4 * ft_pow(tr.x, 3) - 10 * tr.x;
		obj->normal.y = 4 * ft_pow(tr.y, 3) - 10 * tr.y;
		obj->normal.z = 4 * ft_pow(tr.z, 3) - 10 * tr.z;
	}
	if (obj->mat.normal_perturbation)
		obj->normal = vec3(obj->normal.x + sin(ray->hit.x),
		obj->normal.y, obj->normal.z);
	// if (is_non_directed_object(obj))
		vec3_rotate(&obj->normal, obj->rot);
	// ray->pos = vec3_sub(ray->pos, obj->pos);
	// vec3_rotate(&ray->pos, obj->rot);
	// obj->normal = vec3_sub(obj->normal, ray->pos);
	vec3_normalize(&obj->normal);
	obj->mat.texture.normal = obj->normal;
}
