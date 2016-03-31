/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 13:11:54 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/31 11:39:15 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		loop_hook(t_env *e)
{
	move_translate(e);
	move_rotate(e);
	e->key.kp || e->key.km || e->mouse.kp || e->mouse.km ? move_zoom(e) : 0;
	e->key.mouse ? mouse_orientation(e) : 0;
	e->key.invert ? kswitch(&e->cam->filter.invert) : 0;
	e->key.gray_scale ? kswitch(&e->cam->filter.gray_scale) : 0;
	e->key.gamma_m ? e->cam->filter.gamma += 0.05 : 0;
	e->key.gamma_p ? e->cam->filter.gamma -= 0.05 : 0;
	move_object(e);
	e->mouse.kp = 0;
	e->mouse.km = 0;
	e->mouse.lmb = 0;
	e->mouse.rmb = 0;
	expose_hook(e);
	return (0);
}

int		expose_hook(t_env *e)
{
	e->tick.frame_start = clock();
	if (e->key.mouse || e->key.i || e->key.k || e->key.j || e->key.l ||
		e->key.kp || e->key.km || e->key.cu || e->key.cd || e->key.cl ||
		e->key.cr || e->key.cf || e->key.cb || e->key.ou || e->key.od ||
		e->key.ol || e->key.or || e->key.of || e->key.ob ||
		e->key.invert || e->key.gamma_p || e->key.gamma_m ||
		e->key.gray_scale)
		e->scene.progressive_loading ? raytracing_progressive(e) : raytracing(e);
	// display_texture(e, e->obj->mat.texture.bump, e->obj->mat.texture);
	mlx_put_image_to_window(e->mlx, e->win.adr, e->cam->img.adr, 0, 0);
	e->tick.frame = (clock() - e->tick.frame_start) / (float)CLOCKS_PER_SEC;
	e->key.stats ? display_stats(e) : 0;
	return (0);
}

int		key_pressed(int keycode, t_env *e)
{
	keycode == 53 ? exit(0) : 0;
	keycode == 18 ? e->key.invert = 1 : 0;
	keycode == 19 ? e->key.gray_scale = 1 : 0;
	keycode == 27 ? e->key.gamma_m = 1 : 0;
	keycode == 24 ? e->key.gamma_p = 1 : 0;
	keycode == 42 ? viewer_export(e, &e->cam->img) : 0;
	keycode == 30 ? bmp_exporter(e->cam->img, e->arg.file) : 0;
	keycode == 33 ? yml_exporter(e, e->arg.file) : 0;
	keycode == 43 ? e->cam = e->cam->next : 0;
	keycode == 47 ? e->cam = e->cam->prev : 0;
	keycode == 46 ? kswitch(&e->key.mouse) : 0;
	keycode == 50 ? kswitch(&e->key.stats) : 0;
	keycode == 13 ? e->key.cf = 1 : 0;
	keycode == 1 ? e->key.cb = 1 : 0;
	keycode == 0 ? e->key.cl = 1 : 0;
	keycode == 2 ? e->key.cr = 1 : 0;
	keycode == 49 ? e->key.cu = 1 : 0;
	keycode == 257 ? e->key.cd = 1 : 0;
	keycode == 126 ? e->key.of = 1 : 0;
	keycode == 125 ? e->key.ob = 1 : 0;
	keycode == 116 ? e->key.ou = 1 : 0;
	keycode == 121 ? e->key.od = 1 : 0;
	keycode == 123 ? e->key.ol = 1 : 0;
	keycode == 124 ? e->key.or = 1 : 0;
	keycode == 69 ? e->key.kp = 1 : 0;
	keycode == 78 ? e->key.km = 1 : 0;
	keycode == 34 ? e->key.i = 1 : 0;
	keycode == 40 ? e->key.k = 1 : 0;
	keycode == 38 ? e->key.j = 1 : 0;
	keycode == 37 ? e->key.l = 1 : 0;
	keycode == 43 || keycode == 47 ? raytracing(e) : 0;
	return (0);
}

int		key_released(int keycode, t_env *e)
{
	keycode == 13 ? e->key.cf = 0 : 0;
	keycode == 1 ? e->key.cb = 0 : 0;
	keycode == 0 ? e->key.cl = 0 : 0;
	keycode == 2 ? e->key.cr = 0 : 0;
	keycode == 49 ? e->key.cu = 0 : 0;
	keycode == 257 ? e->key.cd = 0 : 0;
	keycode == 126 ? e->key.of = 0 : 0;
	keycode == 125 ? e->key.ob = 0 : 0;
	keycode == 116 ? e->key.ou = 0 : 0;
	keycode == 121 ? e->key.od = 0 : 0;
	keycode == 123 ? e->key.ol = 0 : 0;
	keycode == 124 ? e->key.or = 0 : 0;
	keycode == 69 ? e->key.kp = 0 : 0;
	keycode == 78 ? e->key.km = 0 : 0;
	keycode == 34 ? e->key.i = 0 : 0;
	keycode == 40 ? e->key.k = 0 : 0;
	keycode == 38 ? e->key.j = 0 : 0;
	keycode == 37 ? e->key.l = 0 : 0;
	keycode == 18 ? e->key.invert = 0 : 0;
	keycode == 19 ? e->key.gray_scale = 0 : 0;
	keycode == 27 ? e->key.gamma_m = 0 : 0;
	keycode == 24 ? e->key.gamma_p = 0 : 0;
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
