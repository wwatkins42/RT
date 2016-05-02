/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 18:31:06 by wwatkins          #+#    #+#             */
/*   Updated: 2016/04/30 19:14:31 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

int		vec3_rotate(t_vec3 *v, t_vec3 r)
{
	if (r.x)
		vec3_rot(v, X, r.x);
	if (r.y)
		vec3_rot(v, Y, r.y);
	if (r.z)
		vec3_rot(v, Z, r.z);
	return (1);
}

int		vec3_inverse_rotate(t_vec3 *v, t_vec3 r)
{
	if (r.z)
		vec3_rot(v, Z, -r.z);
	if (r.y)
		vec3_rot(v, Y, -r.y);
	if (r.x)
		vec3_rot(v, X, -r.x);
	return (1);
}
