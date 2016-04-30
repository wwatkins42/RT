/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_rot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 10:57:57 by wwatkins          #+#    #+#             */
/*   Updated: 2016/04/30 14:45:11 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

void	vec3_rot(t_vec3 *v, int axis, double theta)
{
	t_vec3	r;

	theta *= DEG2RAD;
	if (axis == Z)
	{
		r.x = v->x * cos(theta) - v->y * sin(theta);
		r.y = v->x * sin(theta) + v->y * cos(theta);
		r.z = v->z;
	}
	if (axis == Y)
	{
		r.y = v->y;
		r.x = v->x * cos(theta) - v->z * sin(theta);
		r.z = v->x * sin(theta) + v->z * cos(theta);
	}
	if (axis == X)
	{
		r.x = v->x;
		r.y = v->y * cos(theta) - v->z * sin(theta);
		r.z = v->y * sin(theta) + v->z * cos(theta);
	}
	*v = r;
}
