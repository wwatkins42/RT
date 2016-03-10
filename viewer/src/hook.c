/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 16:41:18 by scollon           #+#    #+#             */
/*   Updated: 2016/03/10 16:42:22 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

int		loop_hook(t_env *e)
{
	expose_hook(e);
	return (0);
}

int		expose_hook(t_env *e)
{
	int	ofx;
	int	ofy;

	ofx = (e->win.w - e->current->img.w) / 2.0;
	ofy = (e->win.h - e->current->img.h) / 2.0;
	mlx_clear_window(e->mlx, e->win.adr);
	mlx_put_image_to_window(e->mlx, e->win.adr, e->current->img.adr, ofx, ofy);
	return (0);
}

int		key_pressed(int kc, t_env *e)
{
	kc == 53 ? exit(0) : 0;
	if (kc == 43 || kc == 123)
	{
		e->current = e->current->next != NULL ?
		e->current->next : e->head_viewer;
	}
	if (kc == 47 || kc == 124)
	{
		e->current = e->current->prev != NULL ?
		e->current->prev : e->tail_viewer;
	}
	return (0);
}
