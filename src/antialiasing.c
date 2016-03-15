/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 11:59:26 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/15 08:16:35 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	supersampling(t_env *e, int x, int y)
{
	float	sx;
	float	sy;
	t_vec3	color;

	color = (t_vec3) {0, 0, 0};
	sx = (float)x;
	while (sx < x + 1.0)
	{
		sy = (float)y;
		while (sy < y + 1.0)
		{
			raytracing_init(e, sx, sy);
			color = vec3_add(color, vec3_fmul(raytracing_draw(e, e->cam->ray),
			e->cam->aa.coef));
			sy += e->cam->aa.inc;
		}
		sx += e->cam->aa.inc;
	}
	//e->cam->filter.invert ? filter_invert(&color) : 0;
	//e->cam->filter.gray_scale ? filter_gray_scale(&color) : 0;
	//filter_gamma(e->cam->filter.gamma, &color);
	vec3_clamp(&color, 0, 1);
	img_pixel_put(&e->cam->img, x, y, color);
}
