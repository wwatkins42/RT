/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 13:19:30 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/11 14:10:25 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	raytracing(t_env *e)
{
	int		x;
	int		y;
	t_vec3	color;

	color = vec3_zero();
	y = -1;
	while (++y < e->win.h)
	{
		x = -1;
		while (++x < e->win.w)
		{
			raytracing_init(e);
			color = raytracing_draw(e, &e->cam.ray);
			img_pixel_put(e, x, y, color);
		}
	}
}

void	raytracing_init(t_env *e)
{
	e->reflect.depth = 0;
	e->refract.depth = 0;
	e->cam.ray.pos = e->cam.pos;
	e->cam.ray.dir = e->cam.origin;
	e->cam.ray.hit = vec3_zero();
	e->cam.ray.dir = vec3_add(e->cam.origin, vec3_sub(
			vec3_fmul(vec3_right(), e->cam.xi * e->i),
			vec3_fmul(vec3_up(), e->cam.yi * e->j)));
	vec3_rotate(&e->cam.ray.dir, e->cam.rot);
	vec3_normalize(&e->cam.ray.dir);
}

t_vec3	raytracing_draw(t_env *e, t_ray ray)
{
	t_obj	*obj;
	t_vec3	color;

	tmin = INFINITY;
	color = (t_vec3) {0, 0, 0};
	obj = intersect_object(e, &tmin);
	if (obj != NULL && tmin != INFINITY)
	{
		ray.hit = vec3_add(ray.pos, vec3_fmul(ray.dir, tmin));
		color = vec3_fmul(obj->color, obj->mat.ambient);
		color += raytracing_color(e, ray, obj, tmin);
		if (obj->mat.reflect > 0)
			color += raytracing_reflect(e, ray, obj);
		if (obj->mat.refract > 0)
			color += raytracing_refract(e, ray, obj);
	}
	vec3_clamp(&color, 0, 1);
	return (color);
}

t_vec3	raytracing_reflect(t_env *e, t_ray ray, t_obj *obj)
{
	t_vec3	color;

	color = (t_vec3) {0, 0, 0};
	if (e->reflect.depth < e->reflect.depth_max)
	{
		set_normal(e, obj);
		ray.dir = vec3_reflect(ray.dir, obj->normal);
		color += raytracing_draw(e, ray);
		e->reflect.depth++;
	}
	else
		e->reflect.depth = 0;
	return (color);
}

t_vec3	raytracing_refract(t_env *e, t_ray ray, t_obj *obj)
{
	t_vec3	color;

	color = (t_vec3) {0, 0, 0};
	if (e->refract.depth < e->refract.depth_max)
	{
		set_normal(e, obj);
		// WIP
		color += raytracing_draw(e, ray);
		e->refract.depth++;
	}
	else
		e->refract.depth = 0;
	return (color);
}
