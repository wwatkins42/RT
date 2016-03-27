/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 13:19:30 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/27 12:09:36 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	pthread
**	In order to implement multi-threaded calculs by parallelizing
**	ray tracing on differents CPU threads we must send copies of 't_env'
**	struct and assign lines or blocks of rays to cast  (pixels) for each thread.
**	At the end, get all mlx_images from the structs 't_env' sent to threads
**	and send their data (only the pixels they worked on) to the main mlx_image.
**	Put the final mlx_image to window.
*/

void	raytracing(t_env *e)
{
	int		x;
	int		y;
	t_vec3	color;

	init_cam(e, e->cam);
	color = (t_vec3) {0, 0, 0};
	y = -1;
	while (++y < e->win.h)
	{
		x = -1;
		while (++x < e->win.w)
			supersampling(e, x, y);
		y % 10 ? display_loading(e, x, y) : 0;
	}
}

void	raytracing_progressive(t_env *e)
{
	int		x;
	int		y;
	int		p;
	t_vec3	color;

	e->scene.inc = 32;
	p = e->scene.inc * 2;
	init_cam(e, e->cam);
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
					supersampling(e, x, y);
				x += e->scene.inc;
			}
			y % 10 ? display_loading(e, x, y) : 0;
			y += e->scene.inc;
		}
		mlx_put_image_to_window(e->mlx, e->win.adr, e->cam->img.adr, 0, 0);
		mlx_do_sync(e->mlx);
		p = e->scene.inc;
		e->scene.inc /= 2;
	}
}

void	raytracing_init(t_env *e, float x, float y)
{
	e->reflect.depth = 0;
	e->refract.depth = 0;
	e->cam->ray.pos = e->cam->pos;
	e->cam->ray.dir = e->cam->origin;
	e->cam->ray.hit = (t_vec3) {0, 0, 0};
	e->cam->ray.dir = vec3_add(e->cam->origin, vec3_sub(
		vec3_fmul(vec3_right(), e->cam->xa * x),
		vec3_fmul(vec3_up(), e->cam->ya * y)));
	vec3_rotate(&e->cam->ray.dir, e->cam->dir);
	vec3_normalize(&e->cam->ray.dir);
}

t_vec3	raytracing_draw(t_env *e, t_ray ray)
{
	t_obj	*obj;
	t_vec3	color;
	double	tmin;

	e->count.rps++;
	tmin = INFINITY;
	color = (t_vec3) {0, 0, 0};
	obj = intersect_object(e, &ray, &tmin);
	if (obj != NULL && tmin != INFINITY)
	{
		ray.hit = vec3_add(ray.pos, vec3_fmul(ray.dir, tmin));
		set_normal(&ray, obj);
		color = vec3_add(color, raytracing_color(e, &ray, obj));
		if (obj->mat.reflect > 0)
			color = vec3_add(color, raytracing_reflect(e, ray, obj));
		if (obj->mat.transparency > 0 && obj->mat.refract > 0)
		 	color = vec3_add(color, raytracing_refract(e, ray, obj));
	}
	return (color);
}
