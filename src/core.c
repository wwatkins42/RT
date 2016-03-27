/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 12:00:43 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/27 09:33:22 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	core(t_env *e)
{
	if (!(e->win.adr = mlx_new_window(e->mlx, e->win.w, e->win.h, e->arg.file)))
		error(E_WIN_INIT, NULL, 1);
	init_key(e);
	raytracing(e);
	ft_printf("lolo");
	mlx_hook(e->win.adr, 2, (1L << 0), key_pressed, e);
	mlx_hook(e->win.adr, 3, (1L << 1), key_released, e);
	mlx_hook(e->win.adr, 6, (1L << 6), mouse_pos, e);
	mlx_mouse_hook(e->win.adr, mouse_hook, e);
	mlx_expose_hook(e->win.adr, expose_hook, e);
	mlx_loop_hook(e->mlx, loop_hook, e);
	mlx_loop(e->mlx);

}
