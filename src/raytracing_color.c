/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 14:28:29 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/15 14:12:36 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
//
// static t_vec3	texture_mapping_sphere(t_vec3 hit, t_obj *obj)
// {
// 	t_vec3	color;
//
// 	color = (t_vec3) {0, 0, 0};
// 	//if (obj->mat.texture == NULL)
// 	//	color = obj->mat.color;
// 	//else
// //	{
// 	if (obj->type == SPHERE)
// 	{
// 		t_vec3	Vn = (t_vec3) {0, 1, 0};
// 		t_vec3	Ve = (t_vec3) {0, 0, 1};
// 		t_vec3	Vp = vec3_sub(hit, obj->pos);
// 		double	u;
// 		double	phi = acosf(-vec3_dot(Vn, Vp));
// 		double	v = phi / PI;
// 		double	theta = (acosf(vec3_dot(Vp, Ve) / sinf(phi))) / (2.0 * PI);
// 		if (vec3_dot(vec3_cross(Vn, Ve), Vp) > 0.0)
// 			u = theta;
// 		else
// 			u = 1.0 - theta;
// 		u = u * obj->mat.texture.w;
// 		v = v * obj->mat.texture.h;
// 		u > obj->mat.texture.w ? u = obj->mat.texture.w : 0;
// 		v > obj->mat.texture.h ? v = obj->mat.texture.h : 0;
// 		//printf("(%f, %f)\n", u, v);
// 		color = obj->mat.texture.img[(int)(u + v)];
// 	}
// 	return (color);
// }

t_vec3	raytracing_color(t_env *e, t_ray *ray, t_obj *obj)
{
	t_lgt	*light;
	t_vec3	color;
	t_vec3	diffuse;
	t_vec3	specular;

	color = (t_vec3) {0, 0, 0};
	light = e->lgt;
	while (light != NULL)
	{
		set_light(ray->hit, light);
		color = vec3_add(color, vec3_fmul(light->color,
				obj->mat.ambient));// - 0.005 * obj->t));
		diffuse = set_diffuse(obj, light);
		specular = set_specular(e, ray->hit, obj, light);
		color = vec3_add(color, vec3_add(diffuse, specular));
		color = vec3_mul(color, obj->mat.color);
		color = vec3_fmul(color, light->intensity);
		set_shadow(e, &color, light->ray, obj);
		light = light->next;
	}
	return (color);
}

t_vec3	set_diffuse(t_obj *obj, t_lgt *light)
{
	double	diff;

	diff = vec3_dot(light->ray.dir, obj->normal);
	diff < 0 ? diff = 0 : 0;
	return (vec3_fmul(light->color, diff * obj->mat.diffuse));
}

t_vec3	set_specular(t_env *e, t_vec3 hit, t_obj *obj, t_lgt *light)
{
	t_vec3	lighdir;
	t_vec3	viewdir;
	t_vec3	halfdir;
	float	spec;

	lighdir = vec3_norm(vec3_sub(light->pos, hit));
	viewdir = vec3_norm(vec3_sub(e->cam->pos, hit));
	halfdir = vec3_norm(vec3_add(lighdir, viewdir));
	spec = pow(vec3_dot(obj->normal, halfdir), obj->mat.shininess);
	return (vec3_fmul(light->color, spec * obj->mat.specular));
}

void	set_light(t_vec3 hit, t_lgt *light)
{
	light->ray.pos = light->pos;
	light->ray.dir = vec3_sub(hit, light->pos);
	vec3_normalize(&light->ray.dir);
}

void	set_shadow(t_env *e, t_vec3 *color, t_ray ray, t_obj *obj)
{
	double	tmin;

	tmin = INFINITY;
	if (intersect_object(e, &ray, &tmin) != obj)
		*color = vec3_fmul(*color, 0.5);
}
