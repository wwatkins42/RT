/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 13:11:54 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/25 13:46:35 by wwatkins         ###   ########.fr       */
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
	e->mouse.kp = 0;
	e->mouse.km = 0;
	expose_hook(e);
	return (0);
}

int		expose_hook(t_env *e)
{
	e->tick.frame_start = clock();
	raytracing(e);
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
	keycode == 46 ? kswitch(&e->key.mouse) : 0;
	keycode == 50 ? kswitch(&e->key.stats) : 0;
	keycode == 47 ? e->cam = e->cam->prev : 0;
	keycode == 126 ? e->key.ku = 1 : 0;
	keycode == 125 ? e->key.kd = 1 : 0;
	keycode == 123 ? e->key.kl = 1 : 0;
	keycode == 124 ? e->key.kr = 1 : 0;
	keycode == 69 ? e->key.kp = 1 : 0;
	keycode == 78 ? e->key.km = 1 : 0;
	keycode == 34 ? e->key.i = 1 : 0;
	keycode == 40 ? e->key.k = 1 : 0;
	keycode == 38 ? e->key.j = 1 : 0;
	keycode == 37 ? e->key.l = 1 : 0;
	if (keycode == 43 || keycode == 47) // TMP
		raytracing(e);
	return (0);
}

int		key_released(int keycode, t_env *e)
{
	keycode == 126 ? e->key.ku = 0 : 0;
	keycode == 125 ? e->key.kd = 0 : 0;
	keycode == 123 ? e->key.kl = 0 : 0;
	keycode == 124 ? e->key.kr = 0 : 0;
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
	int			diff;

	e->count.fps++;
	e->tick.current = clock();
	diff = e->tick.current - e->tick.last;
	if (diff >= CLOCKS_PER_SEC)
	{
		e->tick.last = e->tick.current;
		fps == NULL ? fps = ft_strnew(8) : 0;
		rps == NULL ? rps = ft_strnew(32) : 0;
		sprintf(fps, "fps:%d\n", e->count.fps);
		sprintf(rps, "rps:%d\n", e->count.rps);
		e->count.rps = 0;
		e->count.fps = 0;
	}
	irt == NULL ? irt = ft_strnew(12) : 0;
	sprintf(irt, "%.3fs\n", e->tick.frame);
	fps != NULL ? mlx_string_put(e->mlx, e->win.adr, 0, 0, 0xFFFFFF, fps) : 0;
	rps != NULL ? mlx_string_put(e->mlx, e->win.adr, 0, 15, 0xFFFFFF, rps) : 0;
	irt != NULL ? mlx_string_put(e->mlx, e->win.adr, 0, 30, 0xFFFFFF, irt) : 0;
}
