/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 10:56:58 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/22 18:24:48 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	move_translate(t_env *e)
{
	t_vec3	dir;
	t_vec3	pln;

	dir = vec3(0, 0, 1);
	pln = vec3(1, 0, 0);
	vec3_rotate(&dir, e->cam->dir);
	vec3_rotate(&pln, e->cam->dir);
	if (e->key.ku)
		e->cam->pos = vec3_add(e->cam->pos, vec3_fmul(dir, e->scene.velocity));
	if (e->key.kd)
		e->cam->pos = vec3_sub(e->cam->pos, vec3_fmul(dir, e->scene.velocity));
	if (e->key.kl)
		e->cam->pos = vec3_sub(e->cam->pos, vec3_fmul(pln, e->scene.velocity));
	if (e->key.kr)
		e->cam->pos = vec3_add(e->cam->pos, vec3_fmul(pln, e->scene.velocity));
}

void	move_rotate(t_env *e)
{
	e->key.i ? e->cam->dir.x += 5 : 0;
	e->key.k ? e->cam->dir.x -= 5 : 0;
	e->key.j ? e->cam->dir.y += 5 : 0;
	e->key.l ? e->cam->dir.y -= 5 : 0;
}

void	move_zoom(t_env *e)
{
	double	w;
	double	h;
	double	coeff;

	e->key.kp ? e->cam->fov -= 3 : 0;
	e->key.km ? e->cam->fov += 3 : 0;
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
