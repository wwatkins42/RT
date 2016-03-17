/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 13:11:54 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/17 18:08:39 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	loop_hook(t_env *e)
{
	e->key.up ? e->obj->pos.z += 0.5 : 0;
	e->key.down ? e->obj->pos.z -= 0.5 : 0;
	e->key.left ? e->obj->pos.x -= 0.5 : 0;
	e->key.right ? e->obj->pos.x += 0.5 : 0;
	e->key.invert ? kswitch(&e->cam->filter.invert) : 0;
	e->key.gray_scale ? kswitch(&e->cam->filter.gray_scale) : 0;
	e->key.gamma_m ? e->cam->filter.gamma += 0.05 : 0;
	e->key.gamma_p ? e->cam->filter.gamma -= 0.05 : 0;
	expose_hook(e);
	return (0);
}

int	expose_hook(t_env *e)
{
	if (e->key.up || e->key.down || e->key.left || e->key.right ||
		e->key.invert || e->key.gray_scale || e->key.gamma_m || e->key.gamma_p)
		raytracing(e);
	mlx_put_image_to_window(e->mlx, e->win.adr, e->cam->img.adr, 0, 0);
	return (0);
}

int	key_pressed(int keycode, t_env *e)
{
	keycode == KEY_ESC ? exit(0) : 0;
	keycode == KEY_1 ? e->key.invert = 1 : 0;
	keycode == KEY_2 ? e->key.gray_scale = 1 : 0;
	keycode == KEY_MOINS ? e->key.gamma_m = 1 : 0;
	keycode == KEY_PLUS ? e->key.gamma_p = 1 : 0;
	keycode == KEY_BSLASH ? viewer_export(e, &e->cam->img) : 0;
	keycode == KEY_BRACK_OUV ? bmp_exporter(e->cam->img, e->arg.file) : 0;
	keycode == KEY_BRACK_FER ? yml_exporter(e, e->arg.file) : 0;
	keycode == KEY_COMMA ? e->cam = e->cam->next : 0;
	keycode == KEY_DOT ? e->cam = e->cam->prev : 0;
	keycode == UP ? e->key.up = 1 : 0;
	keycode == DOWN ? e->key.down = 1 : 0;
	keycode == LEFT ? e->key.left = 1 : 0;
	keycode == RIGHT ? e->key.right = 1 : 0;
	if (keycode == KEY_COMMA || keycode == KEY_DOT) // TMP
		raytracing(e);
		printf("pos(%f; %f; %f) "    , e->obj->pos.x , e->obj->pos.y , e->obj->pos.z);
		printf("dir(%f; %f; %f) "    , e->obj->pos2.x , e->obj->pos2.y , e->obj->pos2.z);
		printf("dir2(%f; %f; %f)\n\n", e->obj->pos3.x, e->obj->pos3.y, e->obj->pos3.z);
	return (0);
}

int	key_released(int keycode, t_env *e)
{
	keycode == UP ? e->key.up = 0 : 0;
	keycode == DOWN ? e->key.down = 0 : 0;
	keycode == LEFT ? e->key.left = 0 : 0;
	keycode == RIGHT ? e->key.right = 0 : 0;
	keycode == KEY_1 ? e->key.invert = 0 : 0;
	keycode == KEY_2 ? e->key.gray_scale = 0 : 0;
	keycode == KEY_MOINS ? e->key.gamma_m = 0 : 0;
	keycode == KEY_PLUS ? e->key.gamma_p = 0 : 0;
	return (0);
}
