/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_recursion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 15:55:04 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/23 17:46:32 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3		raytracing_reflect(t_env *e, t_ray ray, t_obj *obj)
{
	t_vec3	color;

	color = (t_vec3) {0, 0, 0};
	if (e->reflect.depth < e->reflect.depth_max)
	{
		e->reflect.depth++;
		ray.pos = ray.hit;
		if (obj->mat.texture.normal_map)
			ray.dir = vec3_reflect(ray.dir, obj->mat.texture.normal);
		else
			ray.dir = vec3_reflect(ray.dir, obj->normal);
		color = vec3_add(color, raytracing_draw(e, ray));
		color = vec3_fmul(color, obj->mat.reflect);
	}
	return (color);
}

static void	refract_dir(t_env *e, t_ray *ray, t_obj *obj)
{
	double	n;
	double	cosI;
	double	cosT;
	double	sinT2;
	t_vec3	normal;

	ray->pos = ray->hit;
	normal = obj->normal;
	cosI = vec3_dot(normal, ray->dir);
	if (cosI > 0.0)
	{
		e->refract.n1 = obj->mat.refract;
		e->refract.n2 = 1.0;
		normal = vec3_fmul(normal, -1.0);
	}
	else
	{
		e->refract.n1 = 1.0;
		e->refract.n2 = obj->mat.refract;
		cosI = -cosI;
	}
	n = e->refract.n1 / e->refract.n2;
	sinT2 = n * n * (1.0 - cosI * cosI);
	cosT = sqrt(1.0 - sinT2);
	ray->dir = vec3_add(vec3_fmul(ray->dir, n),
	vec3_fmul(normal, (n * cosI - cosT)));
	vec3_normalize(&ray->dir);
}

t_vec3		raytracing_refract(t_env *e, t_ray ray, t_obj *obj)
{
	t_vec3	color;

	color = (t_vec3) {0, 0, 0};
	if (e->refract.depth < e->refract.depth_max)
	{
		e->refract.depth++;
		refract_dir(e, &ray, obj);
		color = vec3_add(color, vec3_fmul(raytracing_draw(e, ray),
			obj->mat.transparency));
		if (obj->mat.absorbtion < 1.0)
			color = vec3_fmul(color, powf(obj->mat.absorbtion, obj->scale));
		// obj->scale * 2.0 is not correct, t is distance traced in object
	}
	return (color);
}
