/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 15:32:14 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/15 09:16:03 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_img			img_init(t_env *e)
{
	t_img	img;

	if (!(img.adr = mlx_new_image(e->mlx, e->win.w, e->win.h)))
		error(E_IMG_INIT, NULL, 1);
	if (!(img.img = mlx_get_data_addr(img.adr, &img.bpp, &img.sl,
		&img.endian)))
		error(E_IMG_INIT, NULL, 1);
	img.opp = img.bpp / 8;
	img.h = e->win.h;
	img.w = e->win.w;
	return (img);
}

void	img_pixel_put_hex(t_img *img, int x, int y, int hex)
{
	int pos;

	if (x >= 0 && x < img->w && y >= 0 && y < img->h)
	{
		pos = (x * img->opp) + (y * img->sl);
		img->img[pos] = hex % 256 / 255.0;
		img->img[pos + 1] = (hex >> 8) % 256 / 255.0;
		img->img[pos + 2] = (hex >> 16) % 256 / 255.0;
	}
}

void	img_pixel_put(t_img *img, int x, int y, t_vec3 color)
{
	int pos;

	if (x >= 0 && x < img->w && y >= 0 && y < img->h)
	{
		pos = (x * img->opp) + (y * img->sl);
		img->img[pos] = color.z * 255;
		img->img[pos + 1] = color.y * 255;
		img->img[pos + 2] = color.x * 255;
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

int		vec3_hex(const t_vec3 vec)
{
	int		hex;

	hex = (vec.z * 255);
	hex += (vec.y * 255) * 256;
	hex += (vec.x * 255) * 256 * 256;
	return (hex);
}
