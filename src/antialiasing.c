/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 11:59:26 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/14 12:25:40 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	supersampling(t_env *e, int x, int y)
{
	float	sx;
	float	sy;
	t_vec3	color;
	t_vec3	fragc;

	color = (t_vec3) {0, 0, 0};
	fragc = (t_vec3) {0, 0, 0};
	sx = (float)x;
	while (sx < x + 1.0)
	{
		sy = (float)y;
		while (sy < y + 1.0)
		{
			raytracing_init(e, sx, sy);
			fragc = vec3_fmul(raytracing_draw(e, e->cam->ray), e->cam->aa.supersampling_coeff);
			color = vec3_add(color, fragc);
			sy += e->cam->aa.supersampling_inc;
		}
		sx += e->cam->aa.supersampling_inc;
	}
	e->cam->filter.invert ? filter_invert(&color) : 0;
	e->cam->filter.gray_scale ? filter_gray_scale(&color) : 0;
	filter_gamma(e->cam->filter.gamma, &color);
	vec3_clamp(&color, 0, 1);
	img_pixel_put(e, x, y, color);
}
