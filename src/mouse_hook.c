/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 18:42:23 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/31 10:17:09 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	mouse_pos(int x, int y, t_env *e)
{
	e->mouse.pos.x = x;
	e->mouse.pos.y = y;
	return (0);
}

int	mouse_hook(int button, int x, int y, t_env *e)
{
	(void)x;
	(void)y;
	button == 1 ? e->mouse.lmb = 1 : 0;
	button == 2 ? e->mouse.rmb = 1 : 0;
	button == 4 ? e->mouse.kp = 1 : 0;
	button == 5 ? e->mouse.km = 1 : 0;
	return (0);
}
