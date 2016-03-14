/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 10:41:39 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/14 11:24:28 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	invert(t_filter *filter, t_vec3 *color)
{
	if (filter->invert)
	{
		color->x = 1.0 - color->x;
		color->y = 1.0 - color->y;
		color->z = 1.0 - color->z;
	}
}

void	grey_scale(t_filter *filter, t_vec3 *color)
{
	char	m;

	if (filter->grey_scale)
	{
		m = (color->x + color->y + color->z) / 3;
		*color = vec3(m, m, m);
		vec3_clamp(color, 0, 1);
	}
}
