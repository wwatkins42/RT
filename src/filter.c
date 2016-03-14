/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 10:41:39 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/14 11:38:00 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	filter_invert(t_filter *filter, t_vec3 *color)
{
	if (filter->invert)
	{
		color->x = 1.0 - color->x;
		color->y = 1.0 - color->y;
		color->z = 1.0 - color->z;
	}
}

void	filter_gray_scale(t_filter *filter, t_vec3 *color)
{
	double	m;

	if (filter->gray_scale)
	{
		m = (color->x + color->y + color->z) / 3.0;
		*color = vec3(m, m, m);
		vec3_clamp(color, 0, 1);
	}
}

void	filter_gamma(t_filter *filter, t_vec3 *color)
{
	if (filter->gamma != 1.0)
	{
		color->x = powf(color->x, filter->gamma);
		color->y = powf(color->y, filter->gamma);
		color->z = powf(color->z, filter->gamma);
	}
}
