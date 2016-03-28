/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 10:41:39 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/28 14:12:35 by wwatkins         ###   ########.fr       */
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

void	filter_img_update(t_env *e)
{
	int		x;
	int		y;
	int		pos;
	t_vec3	color;

	y = -1;
	while (++y < e->win.h)
	{
		x = -1;
		while (++x < e->win.w)
		{
			pos = (x * e->cam->img.opp) + (y * e->cam->img.sl);
			color.x = (double)(e->cam->img.img[pos + 2] & 0xFF) / 255.0;
			color.y = (double)(e->cam->img.img[pos + 1] & 0xFF) / 255.0;
			color.z = (double)(e->cam->img.img[pos] & 0xFF) / 255.0;
			e->key.invert ? filter_invert(&color) : 0;
			e->key.gray_scale ? filter_gray_scale(&color) : 0;
			e->key.gamma_m || e->key.gamma_p ?
			filter_gamma(e->cam->filter.gamma, &color) : 0;
			img_pixel_put(&e->cam->img, x, y, color);
		}
	}
}
