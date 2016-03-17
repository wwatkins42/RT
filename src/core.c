/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 12:00:43 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/17 15:47:20 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	core(t_env *e)
{
	init_key(e);
	raytracing(e);
	mlx_hook(e->win.adr, 2, (1L << 0), key_pressed, e);
	mlx_hook(e->win.adr, 3, (1L << 1), key_released, e);
	mlx_expose_hook(e->win.adr, expose_hook, e);
	mlx_loop_hook(e->mlx, loop_hook, e);
	mlx_loop(e->mlx);
}

void	display_info(t_env *e, char *str)
{
	static int	y = -17;

	if (y < e->win.h)
		y += 17;
	else
	{
		mlx_clear_window(e->mlx, e->win.adr);
		y = 0;
	}
	mlx_string_put(e->mlx, e->win.adr, 0, y, 0x81E259, str);
	mlx_do_sync(e->mlx);
}
