/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 13:11:54 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/09 14:23:53 by wwatkins         ###   ########.fr       */
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
	mlx_put_image_to_window(e->mlx, e->win.adr, e->img.adr, 0, 0);
	return (0);
}

int	key_pressed(int keycode)
{
	keycode == 53 ? exit(0) : 0;
	return (0);
}
