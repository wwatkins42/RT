/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:23:31 by wwatkins          #+#    #+#             */
/*   Updated: 2016/02/15 15:16:45 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

void	vec2_normalize(t_vec2 *v)
{
	double	magnitude;

	magnitude = vec2_magnitude(*v);
	v->x /= magnitude;
	v->y /= magnitude;
}
