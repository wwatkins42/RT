/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 12:00:43 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/10 10:28:12 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	core(t_env *e)
{
	mlx_put_image_to_window(e->mlx, e->win.adr, e->img.adr, 0, 0);
	mlx_hook(e->win.adr, 2, (1L << 0), key_pressed, e);
	mlx_expose_hook(e->win.adr, expose_hook, e);
	mlx_loop_hook(e->mlx, loop_hook, e);
	mlx_loop(e->mlx);
}
