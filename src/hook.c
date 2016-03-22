/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 13:11:54 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/21 17:49:03 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	disp_texture(t_env *e, t_vec3 **img, t_texture texture)
{
	int		x;
	int		y;

	y = -1;
	while (++y < texture.h)
	{
		x = -1;
		while (++x < texture.w)
			img_pixel_put(&e->cam->img, x, y, img[y][x]);
	}
}

int	loop_hook(t_env *e)
{
	e->key.up ? e->lgt->pos.z += 0.5 : 0;
	e->key.down ? e->lgt->pos.z -= 0.5 : 0;
	e->key.left ? e->lgt->pos.x -= 0.5 : 0;
	e->key.right ? e->lgt->pos.x += 0.5 : 0;
	e->key.rot_up ? e->cam->dir.x += 5 : 0;
	e->key.rot_down ? e->cam->dir.x -= 5 : 0;
	e->key.rot_left ? e->cam->dir.y += 5 : 0;
	e->key.rot_right ? e->cam->dir.y -= 5 : 0;
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
		e->key.rot_up || e->key.rot_down || e->key.rot_left || e->key.rot_right ||
		e->key.invert || e->key.gray_scale || e->key.gamma_m || e->key.gamma_p)
		raytracing(e);
	// disp_texture(e, e->obj->mat.texture.bump, e->obj->mat.texture);
	mlx_put_image_to_window(e->mlx, e->win.adr, e->cam->img.adr, 0, 0);
	return (0);
}

int	key_pressed(int keycode, t_env *e)
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
	keycode == 126 ? e->key.up = 1 : 0;
	keycode == 125 ? e->key.down = 1 : 0;
	keycode == 123 ? e->key.left = 1 : 0;
	keycode == 124 ? e->key.right = 1 : 0;
	keycode == 34 ? e->key.rot_up = 1 : 0;
	keycode == 40 ? e->key.rot_down = 1 : 0;
	keycode == 38 ? e->key.rot_left = 1 : 0;
	keycode == 37 ? e->key.rot_right = 1 : 0;
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
	keycode == 34 ? e->key.rot_up = 0 : 0;
	keycode == 40 ? e->key.rot_down = 0 : 0;
	keycode == 38 ? e->key.rot_left = 0 : 0;
	keycode == 37 ? e->key.rot_right = 0 : 0;
	keycode == 18 ? e->key.invert = 0 : 0;
	keycode == 19 ? e->key.gray_scale = 0 : 0;
	keycode == 27 ? e->key.gamma_m = 0 : 0;
	keycode == 24 ? e->key.gamma_p = 0 : 0;
	return (0);
}
