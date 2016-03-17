/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_generator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 11:25:19 by scollon           #+#    #+#             */
/*   Updated: 2016/03/17 10:13:27 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3			noise_marble(t_noise *n, int x, int y)
{
	double f;
	t_vec3 color;

	f = 1 - sqrt(fabs(sin(2 * PI * noise(n, x, y))));
	color.x = 1.0 * (1 - f) + 0.7 * f;
	color.y = 1.0 * (1 - f) + 0.7 * f;
	color.z = 1.0 * (1 - f) + 0.7 * f;
	return (color);
}

t_vec3			noise_wood(t_noise *n, int x, int y)
{
	double	f;
	double	value;
	t_vec3	color;
	t_vec3	c1;
	t_vec3	c2;

	c1 = vec3(1.0, 0.99, 0.98);
	c2 = vec3(0.2, 0.12, 0.02);
	value = fmod(noise(n, x, y), 0.2);
	if (value > 0.2 / 2)
		value = 0.2 - value;
	f = (1 - cos(PI * value / (0.2 / 2))) / 2;
	color.x = c1.x * (1 - f) + c2.x * f;
	color.y = c1.x * (1 - f) + c2.y * f;
	color.z = c1.z * (1 - f) + c2.z * f;
	return (color);
}

t_vec3			noise_atom(t_noise *n, int x, int y)
{
	double	f;
	double	valeur;
	t_vec3	color;
	t_vec3	c0;
	t_vec3	c1;
	t_vec3	c2;
	t_vec3	c3;
	t_vec3	c4;
	t_vec3	c5;

	c0 = vec3(0.01, 0.02, 0.25);
	c1 = vec3(0.02, 0.03, 0.36);
	c2 = vec3(0.02, 0.27, 0.28);
	c3 = vec3(0.1, 0.29, 0.03);
	c4 = vec3(0.29, 0.15, 0.02);
	c5 = vec3(1.0, 1.0, 1.0);
	valeur = noise(n, x, y);
	if(valeur <= 0.20)
		color = c0;
	else if(valeur < 0.35)
	{
		f = (valeur - 0.20) / (0.35 - 0.20);
		color.x = c0.x * (1 - f) + c1.x * f;
		color.y = c0.x * (1 - f) + c1.y * f;
		color.z = c0.z * (1 - f) + c1.z * f;
	}
	else if(valeur < 0.55)
	{
		f = (valeur - 0.35) / (0.65 - 0.35);
		color.x = c1.x * (1 - f) + c2.x * f;
		color.y = c1.x * (1 - f) + c2.y * f;
		color.z = c1.z * (1 - f) + c2.z * f;
	}
	else if(valeur < 0.65)
	{
		f = (valeur - 0.55) / (0.65 - 0.55);
		color.x = c2.x * (1 - f) + c3.x * f;
		color.y = c2.y * (1 - f) + c3.y * f;
		color.z = c2.z * (1 - f) + c3.z * f;
	}
	else if(valeur < 0.90)
	{
		f = (valeur - 0.65) / (0.90 - 0.65);
		color.x = c3.x * (1 - f) + c4.x * f;
		color.y = c3.y * (1 - f) + c4.y * f;
		color.z = c3.z * (1 - f) + c4.z * f;
	}
	else if(valeur < 0.95)
	{
		f = (valeur - 0.90) / (0.95 - 0.90);
		color.x = c4.x * (1 - f) + c5.x * f;
		color.y = c4.y * (1 - f) + c5.y * f;
		color.z = c4.z * (1 - f) + c5.z * f;
	}
	else
		color = c4 ;
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
	noise = init_noise_structure(width, height, 100, 7);
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
			if (type == 1)
				text.img[y][x] = noise_marble(&noise, x, y);
			if (type == 2)
				text.img[y][x] = noise_wood(&noise, x, y);
			if (type == 3)
				text.img[y][x] = noise_atom(&noise, x, y);
		}
	}
	free(noise.noise);
	noise.noise = NULL;
	return (text);
}
