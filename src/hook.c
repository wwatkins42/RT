/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 13:11:54 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/14 08:27:04 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	loop_hook(t_env *e)
{
	// e->key.up ? e->lgt->pos.z += 0.5 : 0;
	// e->key.down ? e->lgt->pos.z -= 0.5 : 0;
	// e->key.left ? e->lgt->pos.x -= 0.5 : 0;
	// e->key.right ? e->lgt->pos.x += 0.5 : 0;
	e->key.up ? e->obj->pos.z += 0.5 : 0;
	e->key.down ? e->obj->pos.z -= 0.5 : 0;
	e->key.left ? e->obj->pos.x -= 0.5 : 0;
	e->key.right ? e->obj->pos.x += 0.5 : 0;
	expose_hook(e);
	return (0);
}

int	expose_hook(t_env *e)
{
	if (e->key.up || e->key.down || e->key.left || e->key.right)
		raytracing(e);
	mlx_put_image_to_window(e->mlx, e->win.adr, e->cam->img.adr, 0, 0);
	return (0);
}

int	key_pressed(int keycode, t_env *e)
{
	keycode == 53 ? exit(0) : 0;
	keycode == 42 ? viewer_export(e, &e->cam->img) : 0;
	keycode == 30 ? bmp_exporter(e->cam->img, e->arg.file) : 0;
	keycode == 33 ? yml_exporter(e, e->arg.file) : 0;
	keycode == 43 ? e->cam = e->cam->next : 0;
	keycode == 47 ? e->cam = e->cam->prev : 0;
	keycode == 126 ? e->key.up = 1 : 0;
	keycode == 125 ? e->key.down = 1 : 0;
	keycode == 123 ? e->key.left = 1 : 0;
	keycode == 124 ? e->key.right = 1 : 0;
	if (keycode == 43 || keycode == 47) // TMP
		raytracing(e);
	return (0);
}

int	key_released(int keycode, t_env *e)
{
	keycode == 126 ? e->key.up = 0 : 0;
	keycode == 125 ? e->key.down = 0 : 0;
	keycode == 123 ? e->key.left = 0 : 0;
	keycode == 124 ? e->key.right = 0 : 0;
	return (0);
}
