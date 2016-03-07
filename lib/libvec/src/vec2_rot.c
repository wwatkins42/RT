/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 10:57:57 by wwatkins          #+#    #+#             */
/*   Updated: 2016/02/15 15:18:47 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

void	vec2_rot(t_vec2 *v, double theta)
{
	t_vec2	r;

	theta *= DEG2RAD;
	r.x = v->x * cos(theta) - v->y * sin(theta);
	r.y = v->x * sin(theta) + v->y * cos(theta);
	*v = r;
}
