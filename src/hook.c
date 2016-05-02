/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 13:11:54 by wwatkins          #+#    #+#             */
/*   Updated: 2016/05/01 10:25:45 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		loop_hook(t_env *e)
{
	e->tick.frame_start = clock();
	move_translate(e);
	move_rotate(e);
	e->key[KP] || e->key[KM] || e->mouse.kp || e->mouse.km ? move_zoom(e) : 0;
	e->key[MOUSE] ? mouse_orientation(e) : 0;
	e->key[FI] ? kswitch(&e->cam->filter.invert) : 0;
	e->key[FG] ? kswitch(&e->cam->filter.gray_scale) : 0;
	e->key[FGM] ? e->cam->filter.gamma += 0.05 : 0;
	e->key[FGP] ? e->cam->filter.gamma -= 0.05 : 0;
	e->mouse.lmb ? object_select(e) : 0;
	object_move(e, e->cam->selection);
	object_mouse_move(e, e->cam->selection);
	object_mouse_rotate(e, e->cam->selection);
	e->key[DEL] ? object_delete(e, e->cam->selection) : 0;
	e->mouse.kp = 0;
	e->mouse.km = 0;
	e->mouse.lmb = 0;
	e->mouse.rmb = 0;
	expose_hook(e);
	e->tick.frame = (clock() - e->tick.frame_start) / (float)CLOCKS_PER_SEC;
	return (0);
}

int		expose_hook(t_env *e)
{
	if (ispressed(e->key))
		e->scene.progressive_loading ? raytracing_progressive(e, e->cam) :
		start_raytracing(e);
	if (e->cam->type == STEREOSCOPIC)
		mlx_put_image_to_window(e->mlx, e->win.adr, e->cam->stereo.adr, 0, 0);
	else
		mlx_put_image_to_window(e->mlx, e->win.adr, e->cam->img.adr, 0, 0);
	e->key[STAT] ? display_stats(e) : 0;
	return (0);
}

int		key_pressed(int keycode, t_env *e)
{
	keycode == 53 ? quit(e, EXIT_SUCCESS) : 0;
	keycode == 75 ? e->stereo_nb += 0.001 : 0;
	keycode == 67 ? e->stereo_nb -= 0.001 : 0;
	if (keycode != MOUSE && keycode != STAT)
		e->key[keycode] = 1;
	keycode == 30 ? bmp_exporter(e, e->cam, e->arg.file) : 0;
	keycode == 33 ? yml_exporter(e, e->arg.file) : 0;
	keycode == 43 ? e->cam = e->cam->next : 0;
	keycode == 47 ? e->cam = e->cam->prev : 0;
	keycode == MOUSE ? kswitch(&e->key[MOUSE]) : 0;
	keycode == STAT ? kswitch(&e->key[STAT]) : 0;
	keycode == 43 || keycode == 47 ? start_raytracing(e) : 0;
	return (0);
}

int		key_released(int keycode, t_env *e)
{
	if (keycode != MOUSE && keycode != STAT)
		e->key[keycode] = 0;
	return (0);
}

void	display_stats(t_env *e)
{
	static char	*fps = NULL;
	static char	*rps = NULL;
	static char	*irt = NULL;

	e->count.fps++;
	e->tick.current = clock();
	if (e->tick.current - e->tick.last >= CLOCKS_PER_SEC)
	{
		e->tick.last = e->tick.current;
		fps == NULL ? fps = ft_strnew(10) : 0;
		rps == NULL ? rps = ft_strnew(32) : 0;
		sprintf(fps, "fps:%d\n", e->count.fps);
		sprintf(rps, "rps:%d\n", e->count.rps);
		e->count.rps = 0;
		e->count.fps = 0;
	}
	irt == NULL ? irt = ft_strnew(16) : 0;
	sprintf(irt, "%.3fs\n", e->tick.frame);
	fps != NULL ? mlx_string_put(e->mlx, e->win.adr, 0, 0, 0xFFFFFF, fps) : 0;
	rps != NULL ? mlx_string_put(e->mlx, e->win.adr, 0, 15, 0xFFFFFF, rps) : 0;
	irt != NULL ? mlx_string_put(e->mlx, e->win.adr, 0, 30, 0xFFFFFF, irt) : 0;
}
