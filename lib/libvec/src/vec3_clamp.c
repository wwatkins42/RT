/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 18:31:06 by wwatkins          #+#    #+#             */
/*   Updated: 2016/02/15 15:38:09 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

void	vec3_clamp(t_vec3 *v, double min, double max)
{
	v->x > max ? v->x = max : 0;
	v->y > max ? v->y = max : 0;
	v->z > max ? v->z = max : 0;
	v->x < min ? v->x = min : 0;
	v->y < min ? v->y = min : 0;
	v->z < min ? v->z = min : 0;
}
