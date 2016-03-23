/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 14:28:29 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/23 15:47:05 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	raytracing_color(t_env *e, t_ray *ray, t_obj *obj)
{
	t_lgt	*light;
	t_vec3	color;
	t_vec3	diffuse;
	t_vec3	specular;

	color = (t_vec3) {0, 0, 0};
	light = e->lgt;
	obj->mat.texture.normal = obj->normal;
	while (light != NULL)
	{
		set_light(ray->hit, obj, light);
		if (obj->mat.texture.defined)
		{
			obj->mat.color = texture_mapping(obj, obj->mat.texture.img, ray->hit);
			if (obj->mat.texture.normal_map)
				obj->mat.texture.normal = bump_normal(obj, ray);
		}
		color = vec3_add(color, vec3_fmul(light->color, obj->mat.ambient));
		diffuse = set_diffuse(obj, light);
		specular = set_specular(e, ray->hit, obj, light);
		color = vec3_add(color, vec3_add(diffuse, specular));
		color = vec3_mul(color, obj->mat.color);
		obj->mat.receive_shadow ? set_shadow(e, &color, *light, obj) : 0;
		light = light->next;
	}
	return (color);
}

t_vec3	set_diffuse(t_obj *obj, t_lgt *light)
{
	double	theta;
	double	res;

	theta = ft_clampf(vec3_dot(light->ray.dir, obj->mat.texture.normal), 0, 1);
	res = obj->mat.diffuse * light->intensity * theta / obj->dist_attenuation;
	return (vec3_fmul(light->color, res));
}

t_vec3	set_specular(t_env *e, t_vec3 hit, t_obj *obj, t_lgt *light)
{
	t_vec3	lighdir;
	t_vec3	viewdir;
	t_vec3	halfdir;
	float	theta;
	float	res;

	lighdir = vec3_norm(vec3_sub(light->pos, hit));
	viewdir = vec3_norm(vec3_sub(e->cam->pos, hit));
	halfdir = vec3_norm(vec3_add(lighdir, viewdir));
	theta = ft_clampf(vec3_dot(obj->mat.texture.normal, halfdir), 0, 1);
	res = pow(theta, obj->mat.shininess);
	res = res * obj->mat.specular * light->intensity / obj->dist_attenuation;
	return (vec3_fmul(light->color, res));
}

void	set_light(t_vec3 hit, t_obj *obj, t_lgt *light)
{
	light->ray.pos = hit;
	light->ray.dir = vec3_sub(light->pos, hit);
	obj->t = vec3_magnitude(light->ray.dir);
	obj->dist_attenuation = (1.0 + obj->t * obj->t * light->attenuation);
	vec3_normalize(&light->ray.dir);
}

void	set_shadow(t_env *e, t_vec3 *color, t_lgt light, t_obj *obj)
{
	double	tmin;

	tmin = INFINITY;
	light.ray.dir = vec3_norm(vec3_sub(light.ray.pos, light.pos));
	light.ray.pos = light.pos;
	if (intersect_object(e, &light.ray, &tmin) != obj)
		*color = vec3_fmul(*color, 0.5);
}
