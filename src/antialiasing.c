/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 11:59:26 by wwatkins          #+#    #+#             */
/*   Updated: 2016/04/26 14:45:09 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	fill_pixelated(t_env *e, t_cam *cam, t_vec3 color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < e->scene.inc)
	{
		j = -1;
		while (++j < e->scene.inc)
			img_pixel_put(&cam->img, cam->x + i, cam->y + j, color);
	}
}

void		supersampling(t_env *e, t_cam *cam)
{
	float	sx;
	float	sy;
	t_vec3	color;

	color = (t_vec3) {0, 0, 0};
	sx = (float)cam->x;
	while (sx < cam->x + 1.0)
	{
		sy = (float)cam->y;
		while (sy < cam->y + 1.0)
		{
			raytracing_init(e, cam, sx, sy);
			color = vec3_add(color, vec3_fmul(raytracing_draw(e, cam, cam->ray),
			cam->aa.coef));
			sy += cam->aa.inc;
		}
		sx += cam->aa.inc;
	}
	cam->filter.invert ? filter_invert(&color) : 0;
	cam->filter.gray_scale ? filter_gray_scale(&color) : 0;
	filter_gamma(cam->filter.gamma, &color);
	vec3_clamp(&color, 0, 1);
	img_pixel_put(&cam->img, cam->x, cam->y, color);
	e->scene.progressive_loading ? fill_pixelated(e, cam, color) : 0;
}
