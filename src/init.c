/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 14:46:31 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/22 10:46:56 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_env(t_env *e)
{
	e->arg.w = ft_clamp(e->arg.w, 300, 10000);
	e->arg.h = ft_clamp(e->arg.h, 300, 10000);
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
	e->count.cam = 0;
	e->count.lgt = 0;
	e->count.obj = 0;
	e->scene.resync = 0;
	e->scene.percent = 0;
	e->reflect.depth_max = 1;
	e->refract.depth_max = 1;
}

void	init_cam(t_env *e, t_cam *cam)
{
	double	w;
	double	h;
	double  coeff;

	e->cam->aa.inc = 1.0 / e->cam->aa.supersampling;
	e->cam->aa.coef = 1.0 / powf(e->cam->aa.supersampling, 2);
	coeff = (e->win.w < e->win.h ? e->win.w : e->win.h);
	w = e->win.w / coeff;
	h = e->win.h / coeff;
	cam->dist = 1.0 / tan(cam->fov / 2.0 * DEG2RAD);
	cam->origin = vec3_sub(vec3_add(vec3(0, 0, 0),
				vec3_add(vec3_fmul(vec3(0, 0, 1), cam->dist),
				vec3_fmul(vec3_up(), h / 2.0))),
				vec3_fmul(vec3_right(), w / 2.0));
	cam->xa = w / (double)e->win.w;
	cam->ya = h / (double)e->win.h;
}

void	init_key(t_env *e)
{
	e->key.ku = 0;
	e->key.kd = 0;
	e->key.kl = 0;
	e->key.kr = 0;
	e->key.i = 0;
	e->key.k = 0;
	e->key.j = 0;
	e->key.l = 0;
	e->key.invert = 0;
	e->key.gray_scale = 0;
	e->key.gamma_m = 0;
	e->key.gamma_p = 0;
}
