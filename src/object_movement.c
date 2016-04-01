/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 14:08:22 by wwatkins          #+#    #+#             */
/*   Updated: 2016/04/01 10:38:33 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	object_select(t_env *e)
{
	double	tmin;

	if (e->mouse.lmb)
	{
		tmin = INFINITY;
		raytracing_init(e, e->mouse.pos.x, e->mouse.pos.y);
		e->cam->selection = intersect_object(e, &e->cam->ray, &tmin);
	}
}

void	object_move(t_env *e, t_obj *obj)
{
	t_vec3	axis[3];

	if (obj != NULL)
	{
		axis[0] = (t_vec3) {1, 0, 0};
		axis[1] = (t_vec3) {0, 1, 0};
		axis[2] = (t_vec3) {0, 0, 1};
		vec3_rotate(&axis[0], e->cam->dir);
		vec3_rotate(&axis[1], e->cam->dir);
		vec3_rotate(&axis[2], e->cam->dir);
		if (e->key.of)
			obj->pos = vec3_add(obj->pos, vec3_mul(axis[2], vec3(0.5, 0, 0.5)));
		if (e->key.ob)
			obj->pos = vec3_sub(obj->pos, vec3_mul(axis[2], vec3(0.5, 0, 0.5)));
		if (e->key.ou)
			obj->pos = vec3_add(obj->pos, vec3_mul(axis[1], vec3(0, 0.5, 0)));
		if (e->key.od)
			obj->pos = vec3_sub(obj->pos, vec3_mul(axis[1], vec3(0, 0.5, 0)));
		if (e->key.ol)
			obj->pos = vec3_sub(obj->pos, vec3_fmul(axis[0], 0.5));
		if (e->key.or)
			obj->pos = vec3_add(obj->pos, vec3_fmul(axis[0], 0.5));
	}
}

void	object_mouse_move(t_env *e, t_obj *obj)
{
	double			d;
	double			v;
	t_vec3			dif;
	t_vec3			axis[2];
	static t_vec3	old;

	dif = vec3_sub(old, e->mouse.pos);
	old = e->mouse.pos;
	if (e->key.ctrl && obj != NULL)
	{
		d = vec3_magnitude(vec3_sub(obj->pos, e->cam->pos));
		v = e->mouse.sensibility * d * 0.01;
		axis[0] = (t_vec3) {1, 0, 0};
		axis[1] = (t_vec3) {0, 1, 0};
		vec3_rotate(&axis[0], e->cam->dir);
		vec3_rotate(&axis[1], e->cam->dir);
		dif = vec3_fmul(dif, v);
		obj->pos = vec3_sub(obj->pos, vec3_mul(axis[0], vec3(dif.x, 0, dif.x)));
		obj->pos = vec3_add(obj->pos, vec3_fmul(axis[1], dif.y));
	}
}

void	object_mouse_rotate(t_env *e, t_obj *obj)
{
	t_vec3			angle;
	t_vec3			axis;
	t_vec3			dif;
	static t_vec3	old;

	dif = vec3_sub(old, e->mouse.pos);
	old = e->mouse.pos;
	if (e->key.cmd && obj != NULL)
	{
		angle = vec3_fmul(dif, 0.5);
		axis = vec3(angle.y, 0, angle.x);
		vec3_rotate(&obj->dir, axis);
	}
}
