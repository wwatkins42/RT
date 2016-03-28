/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 10:41:39 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/28 14:33:51 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	filter_invert(t_vec3 *color)
{
	color->x = 1.0 - color->x;
	color->y = 1.0 - color->y;
	color->z = 1.0 - color->z;
}

void	filter_gray_scale(t_vec3 *color)
{
	double	m;

	m = (color->x + color->y + color->z) / 3.0;
	*color = vec3(m, m, m);
}

void	filter_gamma(double gamma, t_vec3 *color)
{
	if (gamma != 1.0)
	{
		color->x = powf(color->x, gamma);
		color->y = powf(color->y, gamma);
		color->z = powf(color->z, gamma);
	}
}
