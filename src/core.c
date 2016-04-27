/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 12:00:43 by wwatkins          #+#    #+#             */
/*   Updated: 2016/04/27 14:25:42 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	start_raytracing(t_env *e)
{
	if (e->cam->type == STEREOSCOPIC)
	{
		e->cam->twin->pos = vec3_add(e->cam->pos, vec3(-0.15, 0, 0));
		e->cam->twin->dir = e->cam->dir;
		raytracing(e, e->cam);
		raytracing(e, e->cam->twin);
		generate_stereoscopy(e);
	}
	else
	{
		if (e->scene.progressive_loading)
			raytracing_progressive(e, e->cam);
		else
			raytracing(e, e->cam);
	}
}

void	core(t_env *e)
{
	init_key(e);
	start_raytracing(e);
	mlx_hook(e->win.adr, 2, (1L << 0), key_pressed, e);
	mlx_hook(e->win.adr, 3, (1L << 1), key_released, e);
	mlx_hook(e->win.adr, 6, (1L << 6), mouse_pos, e);
	mlx_mouse_hook(e->win.adr, mouse_hook, e);
	mlx_expose_hook(e->win.adr, expose_hook, e);
	mlx_loop_hook(e->mlx, loop_hook, e);
	mlx_loop(e->mlx);
}
