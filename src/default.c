/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 10:20:15 by scollon           #+#    #+#             */
/*   Updated: 2016/03/08 10:24:51 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	default_camera(t_cam *current)
{
	if (current != NULL)
	{
		current->pos = vec3_zero();
		current->dir = vec3(0, 0, 1);
		current->rot = vec3_zero();
		current->index = 0;
		current->fov = 60;
	}
}

void	default_light(t_lgt *current)
{
	if (current != NULL)
	{
		current->type = POINT;
		current->pos = vec3_zero();
		current->color = vec3(1, 1, 1);
		current->intensity = 1.0;
	}
}
