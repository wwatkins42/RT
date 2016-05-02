/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 13:19:30 by wwatkins          #+#    #+#             */
/*   Updated: 2016/05/02 11:06:51 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	raytracing_shell(t_env *e, t_cam *cam)
{
	char	*buffer;
	int		cursor;
	int		pos;
	int		moy;

	cam->y = -1;
	cursor = 0;
	buffer = (char*)malloc(sizeof(char) * (e->win.w * 2 * e->win.h + e->win.h));
	!buffer ? error(e, E_MALLOC, NULL, 1) : 0;
	while (++cam->y < e->win.h && (cam->x = -1))
	{
		while (++cam->x < e->win.w)
		{
			pos = (cam->x * cam->img.opp) + (cam->y * cam->img.sl);
			moy = ((cam->img.img[pos] & 0xFF) + (cam->img.img[pos + 1] & 0xFF) +
				(cam->img.img[pos + 2] & 0xFF)) / 3.0;
			buffer[cursor++] = ASCII[ft_clamp(((255 - moy) * 16 / 255), 0, 16)];
			buffer[cursor++] = ASCII[ft_clamp(((255 - moy) * 16 / 255), 0, 16)];
		}
		buffer[cursor++] = '\n';
	}
	buffer[cursor++] = '\0';
	system("clear");
	ft_printf("\033[37;40m%s\033[0m", buffer);
	ft_strdel(&buffer);
}

void	raytracing(t_env *e, t_cam *cam)
{
	t_vec3	color;

	init_cam(e, cam);
	color = (t_vec3) {0, 0, 0};
	cam->y = -1;
	while (++cam->y < e->win.h)
	{
		cam->x = -1;
		while (++cam->x < e->win.w)
			supersampling(e, cam);
		cam->y % 10 ? display_loading(e, cam->x, cam->y) : 0;
	}
	e->arg.shell ? raytracing_shell(e, cam) : 0;
}

void	raytracing_progressive(t_env *e, t_cam *cam)
{
	t_vec3	color;

	init_cam(e, cam);
	color = (t_vec3) {0, 0, 0};
	while (e->scene.inc > 0)
	{
		cam->y = 0;
		while (cam->y < e->win.h)
		{
			cam->x = 0;
			while (cam->x < e->win.w)
			{
				if (!(e->scene.inc * 2 != 64 && cam->x % (e->scene.inc * 2) == 0
				&& cam->y % (e->scene.inc * 2) == 0))
					supersampling(e, cam);
				cam->x += e->scene.inc;
			}
			cam->y % 10 ? display_loading(e, cam->x, cam->y) : 0;
			cam->y += e->scene.inc;
		}
		mlx_put_image_to_window(e->mlx, e->win.adr, cam->img.adr, 0, 0);
		mlx_do_sync(e->mlx);
		e->scene.inc /= 2;
		e->arg.shell ? raytracing_shell(e, cam) : 0;
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
			color = vec3_add(color, raytracing_reflect_gloss(e, ray, cam, obj));
		if (obj->mat.transparency > 0)
			color = vec3_add(color, raytracing_refract(e, ray, cam, obj));
	}
	return (color);
}
