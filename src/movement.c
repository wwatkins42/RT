/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 10:56:58 by wwatkins          #+#    #+#             */
/*   Updated: 2016/04/25 14:42:46 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	move_translate(t_env *e)
{
	double	v;
	t_vec3	axis[3];

	v = e->scene.velocity * 0.1;
	axis[0] = (t_vec3) {1, 0, 0};
	axis[1] = (t_vec3) {0, 1, 0};
	axis[2] = (t_vec3) {0, 0, 1};
	e->key[CL] || e->key[CR] ? vec3_rotate(&axis[0], e->cam->dir) : 0;
	e->key[CU] || e->key[CD] ? vec3_rotate(&axis[1], e->cam->dir) : 0;
	e->key[CF] || e->key[CB] ? vec3_rotate(&axis[2], e->cam->dir) : 0;
	axis[2] = vec3_norm(vec3(axis[2].x, 0, axis[2].z));
	axis[1] = vec3_norm(vec3(0, axis[1].y, 0));
	if (e->key[CF])
		e->cam->pos = vec3_add(e->cam->pos, vec3_fmul(axis[2], v));
	if (e->key[CB])
		e->cam->pos = vec3_sub(e->cam->pos, vec3_fmul(axis[2], v));
	if (e->key[CU])
		e->cam->pos = vec3_add(e->cam->pos, vec3_fmul(axis[1], v));
	if (e->key[CD])
		e->cam->pos = vec3_sub(e->cam->pos, vec3_fmul(axis[1], v));
	if (e->key[CL])
		e->cam->pos = vec3_sub(e->cam->pos, vec3_fmul(axis[0], v));
	if (e->key[CR])
		e->cam->pos = vec3_add(e->cam->pos, vec3_fmul(axis[0], v));
}

void	move_rotate(t_env *e)
{
	e->key[I] ? e->cam->dir.x += 5 : 0;
	e->key[K] ? e->cam->dir.x -= 5 : 0;
	e->key[J] ? e->cam->dir.y += 5 : 0;
	e->key[L] ? e->cam->dir.y -= 5 : 0;
}

void	move_zoom(t_env *e)
{
	double	w;
	double	h;
	double	coeff;

	e->key[KP] || e->mouse.kp ? e->cam->fov -= 3 : 0;
	e->key[KM] || e->mouse.km ? e->cam->fov += 3 : 0;
	e->cam->fov = ft_clampf(e->cam->fov, 1, 180);
	coeff = (e->win.w < e->win.h ? e->win.w : e->win.h);
	w = e->win.w / coeff;
	h = e->win.h / coeff;
	e->cam->dist = 1.0 / tan(e->cam->fov / 2.0 * DEG2RAD);
	e->cam->origin = vec3_sub(vec3_add(vec3(0, 0, 0),
		vec3_add(vec3_fmul(vec3(0, 0, 1), e->cam->dist),
		vec3_fmul(vec3_up(), h / 2.0))),
		vec3_fmul(vec3_right(), w / 2.0));
}

void	mouse_orientation(t_env *e)
{
	t_vec3			angle;
	t_vec3			dif;
	static t_vec3	old = (t_vec3) {0, 0, 0};
	static t_vec3	old_angle = (t_vec3) {0, 0, 0};

	dif = vec3_add(e->mouse.pos, old);
	old = e->mouse.pos;
	angle = vec3_fmul(dif, PIOVER4 * e->mouse.sensibility);
	if (e->mouse.lerp)
	{
		angle = vec3_fmul(vec3_add(angle, old_angle), 0.5);
		old_angle = angle;
	}
	e->cam->dir.x = angle.y;
	e->cam->dir.y = -angle.x;
}
