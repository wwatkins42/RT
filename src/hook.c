/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 13:11:54 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/12 09:11:49 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	loop_hook(t_env *e)
{
	expose_hook(e);
	return (0);
}

int	expose_hook(t_env *e)
{
	mlx_put_image_to_window(e->mlx, e->win.adr, e->cam->img.adr, 0, 0);
	return (0);
}

int	key_pressed(int keycode, t_env *e)
{
	keycode == 53 ? exit(0) : 0;
	keycode == 42 ? viewer_export(e, &e->cam->img) : 0;

	keycode == 43 ? e->cam = e->cam->next, raytracing(e) : 0;
	keycode == 47 ? e->cam = e->cam->prev, raytracing(e) : 0;
	return (0);
}
