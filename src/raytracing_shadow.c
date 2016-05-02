/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_shadow.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 12:32:18 by wwatkins          #+#    #+#             */
/*   Updated: 2016/05/02 11:15:45 by wwatkins         ###   ########.fr       */
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

	tmin = INFINITY;
	i = -1;
	shadow = 1;
	hit = light.ray.pos;
	light.ray.dir = vec3_norm(vec3_sub(hit, light.pos));
	light.ray.pos = light.pos;
	dir = light.ray.dir;
	while (++i < e->scene.sampling)
	{
		light.ray.dir = random_sphere_sampling(light.ray, light.scale, hit);
		if (intersect_object(e, &light.ray, &tmin, e->obj) != obj)
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
	if (intersect_object(e, &light.ray, &tmin, e->obj) != obj)
		*color = vec3_fmul(*color, 1.0 - light.shadow_intensity);
}

void			set_shadow(t_env *e, t_vec3 *color, t_lgt light, t_obj *obj)
{
	if (light.shadow == HARD)
		set_hardshadow(e, color, light, obj);
	else if (light.shadow == SOFT)
		set_softshadow(e, color, light, obj);
}
