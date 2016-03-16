/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_generator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 11:25:19 by scollon           #+#    #+#             */
/*   Updated: 2016/03/16 11:46:42 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3			noise_marble(t_noise *n, int x, int y)
{
	double f;
	t_vec3 color;

	f = 1 - sqrt(fabs(sin(2 * PI * noise(n, x, y, 0.7))));
	color.x = 1.0 * (1 - f) + 0.5 * f;
	color.y = 1.0 * (1 - f) + 0.5 * f;
	color.z = 1.0 * (1 - f) + 0.5 * f;
	return (color);
}

t_vec3			noise_atom(t_noise *n, int x, int y)
{
	double	f;
	double	valeur;
	t_vec3	color;

	valeur = noise(n, x, y, 0.7);
	if(valeur <= 0.25)
		color = (t_vec3) {1, 0 ,0};
	else if(valeur < 0.5)
	{
		f = (valeur - 0.25) / (0.5 - 0.25);
		color.x = 1 * (1 - f) + 0 * f;
		color.y = 0 * (1 - f) + 1 * f;
		color.z = 0 * (1 - f) + 0 * f;
	}
	else if(valeur < 0.75)
	{
		f = (valeur - 0.5) / (0.75 - 0.5);
		color.x = 0 * (1 - f) + 0 * f;
		color.y = 1 * (1 - f) + 0 * f;
		color.z = 0 * (1 - f) + 1 * f;
	}
	else
		color = (t_vec3) {0, 0, 1} ;
	return (color);
}

t_texture		texture_generator(int type, int width, int height)
{
	int			x;
	int			y;
	t_noise		noise;
	t_texture	text;

	text.w = width;
	text.h = height;
	text.defined = 1;
	noise = init_noise_structure(width, height, width / 2, 10);
	if (!(text.img = (t_vec3**)malloc(sizeof(t_vec3*) * height)))
		error(E_MALLOC, NULL, 1);
	y = -1;
	while (++y < height)
	{
		x = -1;
		if (!(text.img[y] = (t_vec3*)malloc(sizeof(t_vec3) * width)))
			error(E_MALLOC, NULL, 1);
		while (++x < width)
		{
			text.img[y][x] = type == 0 ? noise_atom(&noise, x, y) : noise_marble(&noise, x, y);
		}
	}
	return (text);
}
