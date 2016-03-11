/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 15:32:14 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/11 15:52:53 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_img			img_init(t_env *e, int w, int h)
{
	t_img	img;

	if (!(img.adr = mlx_new_image(e->mlx, w, h)))
		error(E_IMG_INIT, NULL, 1);
	if (!(img.img = mlx_get_data_addr(img.adr, &img.bpp, &img.sl,
		&img.endian)))
		error(E_IMG_INIT, NULL, 1);
	img.opp = img.bpp / 8;
	return (img);
}

void	img_pixel_put_hex(t_env *e, int x, int y, int hex)
{
	int pos;

	if (x >= 0 && x < e->win.w && y >= 0 && y < e->win.h)
	{
		pos = (x * e->cam->img.opp) + (y * e->cam->img.sl);
		e->cam->img.img[pos] = hex % 256 / 255.0;
		e->cam->img.img[pos + 1] = (hex >> 8) % 256 / 255.0;
		e->cam->img.img[pos + 2] = (hex >> 16) % 256 / 255.0;
		e->cam->img.img[pos + 3] = 0;
	}
}

void	img_pixel_put(t_env *e, int x, int y, t_vec3 color)
{
	int pos;

	if (x >= 0 && x < e->win.w && y >= 0 && y < e->win.h)
	{
		pos = (x * e->cam->img.opp) + (y * e->cam->img.sl);
		e->cam->img.img[pos] = color.z * 255;
		e->cam->img.img[pos + 1] = color.y * 255;
		e->cam->img.img[pos + 2] = color.x * 255;
		e->cam->img.img[pos + 3] = 0;
	}
}

t_vec3	hex_vec3(const int hex)
{
	t_vec3	color;

	color.z = hex % 256 / 255.0;
	color.y = (hex >> 8) % 256 / 255.0;
	color.x = (hex >> 16) % 256 / 255.0;
	return (color);
}
