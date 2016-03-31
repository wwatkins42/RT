/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 14:08:22 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/31 16:47:10 by wwatkins         ###   ########.fr       */
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
	double	v;
	t_vec3	axis[3];

	if (obj != NULL)
	{
		v = 0.5;
		axis[0] = vec3(1, 0, 0);
		axis[1] = vec3(0, 1, 0);
		axis[2] = vec3(0, 0, 1);
		vec3_rotate(&axis[0], e->cam->dir);
		vec3_rotate(&axis[1], e->cam->dir);
		vec3_rotate(&axis[2], e->cam->dir);
		if (e->key.of)
			obj->pos = vec3_add(obj->pos, vec3_mul(axis[2], vec3(v, 0, v)));
		if (e->key.ob)
			obj->pos = vec3_sub(obj->pos, vec3_mul(axis[2], vec3(v, 0, v)));
		if (e->key.ou)
			obj->pos = vec3_add(obj->pos, vec3_mul(axis[1], vec3(0, v, 0)));
		if (e->key.od)
			obj->pos = vec3_sub(obj->pos, vec3_mul(axis[1], vec3(0, v, 0)));
		if (e->key.ol)
			obj->pos = vec3_sub(obj->pos, vec3_fmul(axis[0], v));
		if (e->key.or)
			obj->pos = vec3_add(obj->pos, vec3_fmul(axis[0], v));
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
