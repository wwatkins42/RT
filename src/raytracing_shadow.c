/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_shadow.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 12:32:18 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/30 17:37:17 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


static t_vec3	random_sphere_sampling(t_ray ray, double ks, t_vec3 hit)
{
	t_vec3	ranv;
	t_vec3	ndir;

	ranv.x = rand() / (double)RAND_MAX * ks - (ks * 0.5);
	ranv.y = rand() / (double)RAND_MAX * ks - (ks * 0.5);
	ranv.z = rand() / (double)RAND_MAX * ks - (ks * 0.5);
	ndir = vec3_sub(hit, vec3_add(ray.pos, ranv));
	return (vec3_norm(ndir));
}

static void		set_softshadow(t_env *e, t_vec3 *color, t_lgt light, t_obj *obj)
{
	int		i;
	int		shadow;
	double	tmin;
	t_vec3	dir;
	t_vec3	hit;

	i = -1;
	shadow = 1;
	hit = light.ray.pos;
	light.ray.dir = vec3_norm(vec3_sub(hit, light.pos));
	light.ray.pos = light.pos;
	dir = light.ray.dir;
	while (++i < e->scene.sampling)
	{
		light.ray.dir = random_sphere_sampling(light.ray, light.scale, hit);
		tmin = INFINITY;
		if (intersect_object(e, &light.ray, &tmin) != obj)
			shadow++;
		light.ray.dir = dir;
	}
	*color = vec3_fmul(*color, 1 - (float)shadow /
		(float)e->scene.sampling * light.shadow_intensity);
}

static void		set_hardshadow(t_env *e, t_vec3 *color, t_lgt light, t_obj *obj)
{
	double	tmin;

	tmin = INFINITY;
	light.ray.dir = vec3_norm(vec3_sub(light.ray.pos, light.pos));
	light.ray.pos = light.pos;
	if (intersect_object(e, &light.ray, &tmin) != obj)
		*color = vec3_fmul(*color, 1.0 - light.shadow_intensity);
}

static t_vec3	get_shadow_color(t_env *e, t_lgt light, t_obj *this, t_obj *obj)
{
	t_vec3	color;
	t_vec3	hit;
	t_ray	ray;
	double	tmin;

	tmin = INFINITY;
	ray.dir = vec3_norm(vec3_sub(light.ray.pos, light.pos));
	ray.pos = light.pos;
	intersect_object(e, &ray, &tmin);
	hit = vec3_mul(vec3_fmul(light.ray.dir, tmin), obj->pos);
	color = texture_mapping(obj, obj->mat.texture.img, hit);
	color = vec3_mul(color, vec3_fmul(light.color, light.intensity));
	color = vec3_fmul(color, obj->mat.transparency / this->dist_attenuation);
	vec3_clamp(&color, 0, 1);
	return (vec3_add(vec3(1, 1, 1), color));
}

static void		set_projectionshadow(t_env *e, t_vec3 *color, t_lgt light, t_obj *obj)
{
	double	tmin;
	double	t;
	t_obj	*other;

	tmin = INFINITY;
	light.ray.dir = vec3_sub(light.pos, light.ray.pos);
	t = vec3_magnitude(light.ray.dir);
	vec3_normalize(&light.ray.dir);
	if ((other = intersect_object(e, &light.ray, &tmin)) == NULL)
		return ;
	if (obj->mat.transparency > 0 && other != obj && tmin < t)
		*color = vec3_mul(*color, get_shadow_color(e, light, obj, other));
}

void			set_shadow(t_env *e, t_vec3 *color, t_lgt light, t_obj *obj)
{
	if (light.shadow == HARD)
		set_hardshadow(e, color, light, obj);
	else if (light.shadow == SOFT)
		set_softshadow(e, color, light, obj);
	else if (light.shadow == PROJECTION)
		set_projectionshadow(e, color, light, obj);
}
