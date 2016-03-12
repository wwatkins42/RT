/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_recursion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 15:55:04 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/12 16:14:18 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


t_vec3	raytracing_reflect(t_env *e, t_ray ray, t_obj *obj)
{
	t_vec3	color;

	color = (t_vec3) {0, 0, 0};
	if (e->reflect.depth < e->reflect.depth_max)
	{
		e->reflect.depth++;
		ray.pos = ray.hit;
		ray.dir = vec3_reflect(ray.dir, obj->normal);
		color = vec3_add(color, raytracing_draw(e, ray));
		color = vec3_fmul(color, obj->mat.reflect);
	}
	return (color);
}

t_vec3	raytracing_refract(t_env *e, t_ray ray, t_obj *obj)
{
	t_vec3	color;

	color = (t_vec3) {0, 0, 0};
	if (e->refract.depth < e->refract.depth_max)
	{
		e->refract.depth++;
		refract_dir(e, &ray, obj);
		color = vec3_add(color, vec3_fmul(raytracing_draw(e, ray),
				obj->mat.transparency));
		color = vec3_fmul(color, powf(obj->mat.absorbtion, obj->scale * 2.0));
		// obj->scale * 2.0 is not correct, t is distance traced in object
	}
	return (color);
}

void	refract_dir(t_env *e, t_ray *ray, t_obj *obj)
{
	double	n;
	double	cosI;
	double	cosT;
	double	sinT2;

	ray->pos = ray->hit;
	cosI = -vec3_dot(obj->normal, ray->dir);
	if (cosI > 0)
	{
		e->refract.n1 = obj->mat.refract;
		e->refract.n2 = 1;
		obj->normal = vec3_sub(vec3_zero(), obj->normal);
	}
	else
	{
		e->refract.n1 = 1;
		e->refract.n2 = obj->mat.refract;
		cosI = -cosI;
	}
	n = e->refract.n1 / e->refract.n2;
	sinT2 = n * n * (1.0 - cosI * cosI);
	cosT = sqrt(1.0 - sinT2);
	ray->dir = vec3_add(vec3_fmul(ray->dir, n),
	vec3_fmul(obj->normal, (n * cosI - cosT)));
}
