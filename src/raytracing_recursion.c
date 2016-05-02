/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_recursion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 15:55:04 by wwatkins          #+#    #+#             */
/*   Updated: 2016/05/02 11:42:22 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3			raytracing_reflect(t_env *e, t_ray ray, t_cam *cam, t_obj *obj)
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
		color = vec3_add(color, raytracing_draw(e, cam, ray));
		color = vec3_fmul(color, obj->mat.reflect);
		if (obj->mat.fresnel.defined)
			color = vec3_fmul(color, get_fresnel(vec3_fmul(cam->ray.dir, -1),
			obj->normal, obj->mat.fresnel.reflect));
	}
	return (color);
}

static t_vec3	glossy_reflection_direction(t_ray ray, t_obj *obj)
{
	t_vec3	cone;
	t_vec3	ranv;
	double	kg;

	kg = obj->mat.glossiness;
	ranv.x = rand() / (double)RAND_MAX * kg - (kg * 0.5);
	ranv.y = rand() / (double)RAND_MAX * kg - (kg * 0.5);
	ranv.z = rand() / (double)RAND_MAX * kg - (kg * 0.5);
	cone = vec3_add(vec3_add(ray.pos, ray.dir), ranv);
	return (vec3_norm(vec3_sub(cone, ray.pos)));
}

t_vec3			raytracing_reflect_gloss(t_env *e, t_ray ray, t_cam *cam,
	t_obj *obj)
{
	t_vec3	color;
	t_vec3	dir;
	int		i;

	color = (t_vec3) {0, 0, 0};
	if (e->reflect.depth < e->reflect.depth_max)
	{
		e->reflect.depth++;
		ray.pos = ray.hit;
		if (obj->mat.texture.normal_map)
			ray.dir = vec3_reflect(ray.dir, obj->mat.texture.normal);
		else
			ray.dir = vec3_reflect(ray.dir, obj->normal);
		dir = ray.dir;
		i = -1;
		while (++i < e->scene.sampling)
		{
			ray.dir = glossy_reflection_direction(ray, obj);
			color = vec3_add(color, raytracing_draw(e, cam, ray));
			ray.dir = dir;
		}
		color = vec3_fmul(color, 1.0 / (double)e->scene.sampling);
		color = vec3_fmul(color, obj->mat.reflect);
	}
	return (color);
}

static void		refract_dir(t_env *e, t_ray *ray, t_obj *obj)
{
	double	n;
	double	calc[3];
	t_vec3	norm;

	ray->pos = ray->hit;
	norm = obj->mat.texture.normal_map ? obj->mat.texture.normal : obj->normal;
	calc[0] = vec3_dot(norm, ray->dir);
	if (calc[0] > 0.0)
	{
		e->refract.n1 = obj->mat.refract;
		e->refract.n2 = 1.0;
		norm = vec3_fmul(norm, -1.0);
	}
	else
	{
		e->refract.n1 = 1.0;
		e->refract.n2 = obj->mat.refract;
		calc[0] = -calc[0];
	}
	n = e->refract.n1 / e->refract.n2;
	calc[2] = n * n * (1.0 - calc[0] * calc[0]);
	calc[1] = sqrt(1.0 - calc[2]);
	ray->dir = vec3_add(vec3_fmul(ray->dir, n),
	vec3_fmul(norm, (n * calc[0] - calc[1])));
	vec3_normalize(&ray->dir);
}

t_vec3			raytracing_refract(t_env *e, t_ray ray, t_cam *cam, t_obj *obj)
{
	t_vec3	color;
	t_vec3	tex_color;

	color = (t_vec3) {0, 0, 0};
	if (obj->mat.texture.transparency_mapping)
	{
		tex_color = texture_mapping(obj, obj->mat.texture.img, ray.hit);
		obj->mat.transparency = (tex_color.x + tex_color.y + tex_color.z) / 3.0;
	}
	if (e->refract.depth < e->refract.depth_max)
	{
		e->refract.depth++;
		refract_dir(e, &ray, obj);
		color = vec3_add(color, vec3_fmul(raytracing_draw(e, cam, ray),
			obj->mat.transparency));
		if (obj->mat.absorbtion < 1.0)
			color = vec3_fmul(color, powf(obj->mat.absorbtion, obj->scale));
		if (obj->mat.fresnel.defined)
			color = vec3_fmul(color, get_fresnel(vec3_fmul(cam->ray.dir, -1),
			obj->normal, obj->mat.fresnel.refract));
	}
	return (color);
}
