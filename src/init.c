/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 14:46:31 by wwatkins          #+#    #+#             */
/*   Updated: 2016/04/28 10:20:32 by scollon          ###   ########.fr       */
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
	e->count.cam = 0;
	e->count.lgt = 0;
	e->count.obj = 0;
	e->scene.velocity = 0.6;
	e->reflect.depth_max = 1;
	e->refract.depth_max = 1;
	e->mouse.sensibility = 0.3;
	e->mouse.lerp = 0;
	e->scene.resync = 0;
	e->scene.percent = 0;
	e->scene.progressive_loading = 0;
	e->scene.sampling = 0;
	e->tick.last = clock();
	e->count.fps = 0;
	e->count.rps = 0;
	e->tick.frame = 1.0;
	e->stereo_nb = -0.057;
}

void	init_intersect(t_env *e)
{
	e->intersect[SPHERE] = intersect_sphere;
	e->intersect[CONE] = intersect_cone;
	e->intersect[PLANE] = intersect_plane;
	e->intersect[CYLINDER] = intersect_cylinder;
	e->intersect[TRIANGLE] = intersect_triangle;
	e->intersect[PARALLELOGRAM] = intersect_parallelogram;
	e->intersect[HYPERBOLOID_ONE] = intersect_hyperboloid1;
	e->intersect[HYPERBOLOID_TWO] = intersect_hyperboloid2;
	e->intersect[PARABOLOID] = intersect_paraboloid;
	e->intersect[TORUS] = intersect_torus;
	e->intersect[CUBE] = intersect_cube;
	e->intersect[BBOX] = intersects_bbox;
}

void	init_cam(t_env *e, t_cam *cam)
{
	double	w;
	double	h;
	double	coeff;

	cam->aa.inc = 1.0 / cam->aa.supersampling;
	cam->aa.coef = 1.0 / powf(cam->aa.supersampling, 2);
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
	ft_bzero((void*)e->key, 280);
	e->mouse.km = 0;
	e->mouse.kp = 0;
	e->mouse.lmb = 0;
	e->mouse.rmb = 0;
	e->mouse.pos = (t_vec3) {e->win.dw, e->win.dh, 0};
}
