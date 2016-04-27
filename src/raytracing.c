/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aacuna <aacuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 13:19:30 by wwatkins          #+#    #+#             */
/*   Updated: 2016/04/25 14:53:34 by aacuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	raytracing(t_env *e, t_cam *cam)
{
	int		x;
	int		y;
	t_vec3	color;

	init_cam(e, cam);
	color = (t_vec3) {0, 0, 0};
	y = -1;
	while (++y < e->win.h)
	{
		x = -1;
		while (++x < e->win.w)
			supersampling(e, cam, x, y);
		y % 10 ? display_loading(e, x, y) : 0;
	}
}

void	raytracing_progressive(t_env *e, t_cam *cam)
{
	int		x;
	int		y;
	int		p;
	t_vec3	color;

	e->scene.inc = 32;
	p = e->scene.inc * 2;
	init_cam(e, cam);
	color = (t_vec3) {0, 0, 0};
	while (e->scene.inc > 0)
	{
		y = 0;
		while (y < e->win.h)
		{
			x = 0;
			while (x < e->win.w)
			{
				if (!(p != 64 && x % p == 0 && y % p == 0))
					supersampling(e, cam, x, y);
				x += e->scene.inc;
			}
			y % 10 ? display_loading(e, x, y) : 0;
			y += e->scene.inc;
		}
		mlx_put_image_to_window(e->mlx, e->win.adr, cam->img.adr, 0, 0);
		mlx_do_sync(e->mlx);
		p = e->scene.inc;
		e->scene.inc /= 2;
	}
}

void	raytracing_init(t_env *e, t_cam *cam, float x, float y)
{
	e->reflect.depth = 0;
	e->refract.depth = 0;
	cam->ray.pos = cam->pos;
	cam->ray.dir = cam->origin;
	cam->ray.hit = (t_vec3) {0, 0, 0};
	cam->ray.dir = vec3_add(cam->origin, vec3_sub(
		vec3_fmul(vec3_right(), cam->xa * x),
		vec3_fmul(vec3_up(), cam->ya * y)));
	vec3_rotate(&cam->ray.dir, cam->dir);
	vec3_normalize(&cam->ray.dir);
}

t_vec3	raytracing_draw(t_env *e, t_cam *cam, t_ray ray)
{
	t_obj	*obj;
	t_vec3	color;
	double	tmin;

	e->count.rps++;
	tmin = INFINITY;
	color = (t_vec3) {0, 0, 0};
	obj = intersect_object(e, &ray, &tmin, e->obj);
	if (obj != NULL && tmin != INFINITY)
	{
		ray.hit = vec3_add(ray.pos, vec3_fmul(ray.dir, tmin));
		set_normal(&ray, obj);
		color = vec3_add(color, raytracing_color(e, &ray, cam, obj));
		if (obj->mat.reflect > 0 && obj->mat.glossiness == 0)
			color = vec3_add(color, raytracing_reflect(e, ray, cam, obj));
		if (obj->mat.reflect > 0 && obj->mat.glossiness > 0)
			color = vec3_add(color, raytracing_reflect_glossy(e, ray, cam, obj));
		if (obj->mat.transparency > 0)
			color = vec3_add(color, raytracing_refract(e, ray, cam, obj));
	}
	return (color);
}
