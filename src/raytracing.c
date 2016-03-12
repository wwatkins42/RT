/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 13:19:30 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/12 10:31:52 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	raytracing(t_env *e)
{
	int		x;
	int		y;
	t_vec3	color;

	color = (t_vec3) {0, 0, 0};
	y = -1;
	while (++y < e->win.h)
	{
		x = -1;
		while (++x < e->win.w)
		{
			raytracing_init(e, x, y);
			color = raytracing_draw(e, e->cam->ray);
			img_pixel_put(e, x, y, color);
		}
	}
}

void	raytracing_init(t_env *e, int x, int y)
{
	e->reflect.depth = 0;
	e->refract.depth = 0;
	e->cam->ray.pos = e->cam->pos;
	e->cam->ray.dir = e->cam->origin;
	e->cam->ray.hit = (t_vec3) {0, 0, 0};
	e->cam->ray.dir = vec3_add(e->cam->origin, vec3_sub(
		vec3_fmul(vec3_right(), e->cam->xa * (double)x),
		vec3_fmul(vec3_up(), e->cam->ya * (double)y)));
//	vec3_rotate(&e->cam->ray.dir, e->cam->rot);
	vec3_normalize(&e->cam->ray.dir);
	// if (x == 500 && y == 500)
	// {
	// 	printf("pos:(%f, %f, %f)\n", e->cam->pos.x, e->cam->pos.y, e->cam->pos.z);
	// 	printf("ori:(%f, %f, %f)\n", e->cam->origin.x, e->cam->origin.y, e->cam->origin.z);
	// 	printf("cam:(%f, %f, %f)\n", e->cam->ray.dir.x, e->cam->ray.dir.y, e->cam->ray.dir.z);
	// }
}

t_vec3	raytracing_draw(t_env *e, t_ray ray)
{
	t_obj	*obj;
	t_vec3	color;
	double	tmin;

	tmin = INFINITY;
	color = (t_vec3) {0, 0, 0};
	obj = intersect_object(e, &ray, &tmin);
	if (obj != NULL && tmin != INFINITY)
	{
		ray.hit = vec3_add(ray.pos, vec3_fmul(ray.dir, tmin));
		set_normal(&ray, obj);
		color = vec3_add(color, raytracing_color(e, &ray, obj));
		if (obj->mat.reflect > 0.0)
			color = vec3_add(color, raytracing_reflect(e, ray, obj));
		if (obj->mat.refract > 0.0)
			color = vec3_add(color, raytracing_refract(e, ray, obj));
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
		ray.pos = ray.hit;
		// WIP
		color += raytracing_draw(e, ray);
	}
	else
		e->refract.depth = 0;
	return (color);
}
