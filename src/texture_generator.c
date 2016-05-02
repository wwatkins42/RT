/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_generator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 11:25:19 by scollon           #+#    #+#             */
/*   Updated: 2016/05/01 10:56:49 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_rgb	noise_marble(t_noise *n, int x, int y)
{
	double f;
	t_rgb color;

	f = 1 - sqrt(fabs(sin(2 * PI * noise(n, x, y))));
	color.x = (1.0 * (1 - f) + 0.7 * f) * 255;
	color.y = (1.0 * (1 - f) + 0.7 * f) * 255;
	color.z = (1.0 * (1 - f) + 0.7 * f) * 255;
	return (color);
}

static t_rgb	noise_wood(t_noise *n, int x, int y)
{
	double	f;
	double	value;
	t_rgb	color;
	t_vec3	c1;
	t_vec3	c2;

	c1 = vec3(1.0, 0.99, 0.98);
	c2 = vec3(0.2, 0.12, 0.02);
	value = fmod(noise(n, x, y), 0.2);
	if (value > 0.2 / 2)
		value = 0.2 - value;
	f = (1 - cos(PI * value / (0.2 / 2))) / 2;
	color.x = (c1.x * (1 - f) + c2.x * f) * 255;
	color.y = (c1.x * (1 - f) + c2.y * f) * 255;
	color.z = (c1.z * (1 - f) + c2.z * f) * 255;
	return (color);
}

static void		init_func(t_noise *noise)
{
	noise->noise_func[0] = NULL;
	noise->noise_func[1] = noise_marble;
	noise->noise_func[2] = noise_wood;
}

t_texture		texture_generator(t_env *e, int type, int width, int height)
{
	int			x;
	int			y;
	t_noise		noise;
	t_texture	text;

	text.w = width;
	text.h = height;
	text.defined = 1;
	text.normal_map = 0;
	noise = init_noise_structure(e, width, height);
	init_func(&noise);
	if (!(text.img = (t_rgb**)malloc(sizeof(t_rgb*) * height)))
		error(e, E_MALLOC, NULL, 1);
	y = -1;
	while (++y < height)
	{
		x = -1;
		if (!(text.img[y] = (t_rgb*)malloc(sizeof(t_rgb) * width)))
			error(e, E_MALLOC, NULL, 1);
		while (++x < width)
			if (type < 3 && type > 0)
				text.img[y][x] = noise.noise_func[type](&noise, x, y);
	}
	ft_memdel((void**)&noise.noise);
	return (text);
}
