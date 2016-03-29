/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 11:59:26 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/29 11:00:20 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	fill_pixelated(t_env *e, int x, int y, t_vec3 color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < e->scene.inc)
	{
		j = -1;
		while (++j < e->scene.inc)
			img_pixel_put(&e->cam->img, x + i, y + j, color);
	}
}

void		supersampling(t_env *e, int x, int y)
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
	e->cam->filter.invert ? filter_invert(&color) : 0;
	e->cam->filter.gray_scale ? filter_gray_scale(&color) : 0;
	filter_gamma(e->cam->filter.gamma, &color);
	vec3_clamp(&color, 0, 1);
	img_pixel_put(&e->cam->img, x, y, color);
	e->scene.progressive_loading ? fill_pixelated(e, x, y, color) : 0;
}
