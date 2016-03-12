/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 14:46:31 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/12 14:29:58 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_env(t_env *e)
{
	e->reflect.depth_max = 2;
	e->refract.depth_max = 2;
	e->arg.w = (e->arg.w < 320 || e->arg.w > 10000 ? 1000 : e->arg.w);
	e->arg.h = (e->arg.h < 200 || e->arg.h > 5000 ? 900 : e->arg.h);
	e->win.w = e->arg.w;
	e->win.h = e->arg.h;
	e->win.dw = e->win.w / 2;
	e->win.dh = e->win.h / 2;
	if (!(e->win.adr = mlx_new_window(e->mlx, e->win.w, e->win.h, e->arg.file)))
		error(E_WIN_INIT, NULL, 1);
	e->intersect[0] = intersect_sphere;
	e->intersect[1] = intersect_cone;
	e->intersect[2] = intersect_plane;
	e->intersect[3] = intersect_cylinder;
}

void	init_cam(t_env *e, t_cam *cam)
{
	double	w;
	double	h;
	double  coeff;

	coeff = (e->win.w < e->win.h ? e->win.w : e->win.h);
	w = e->win.w / coeff;
	h = e->win.h / coeff;
	cam->dist = 1.0 / tan(cam->fov / 2.0 * DEG2RAD);
	cam->origin = vec3_sub(vec3_add(vec3(0, 0, 0),
				vec3_add(vec3_fmul(cam->dir, cam->dist),
				vec3_fmul(vec3_up(), h / 2.0))),
				vec3_fmul(vec3_right(), w / 2.0));
	cam->xa = w / (double)e->win.w;
	cam->ya = h / (double)e->win.h;
}

void	init_key(t_env *e)
{
	e->key.up = 0;
	e->key.down = 0;
	e->key.left = 0;
	e->key.right = 0;
}
