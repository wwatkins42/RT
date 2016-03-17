/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:55:16 by scollon           #+#    #+#             */
/*   Updated: 2016/03/17 09:55:39 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

t_noise				init_noise_structure(int w, int h, int pas, int octave)
{
	int		i;
	t_noise	noise;

	i = -1;
	noise.octave = octave;
	noise.pas = pas;
	noise.w_max = (int)ceil(w * pow(2, noise.octave - 1) / noise.pas);
	noise.h_max = (int)ceil(h * pow(2, noise.octave - 1) / noise.pas);
	noise.len = noise.w_max * noise.h_max;
	if (!(noise.noise = (double*)malloc(sizeof(double) * noise.len)))
		error(E_MALLOC, NULL, 1);
	srand(time(NULL));
	while (++i < noise.len)
		noise.noise[i] = ((double)rand()) / RAND_MAX;
	return (noise);
}

static double		interpolate(double a, double b, double x)
{
	return (a * (1 - x) + b * x);
}

static double		get_value(t_noise *noise, int i, int j)
{
	return (noise->noise[(i % noise->w_max) + (j % noise->h_max) * noise->w_max]);
}

static double		noise_generator(t_noise *n, double x, double y)
{
	int		i;
	int		j;
	double	y1;
	double	y2;

	i = (int)(x / n->pas);
	j = (int)(y / n->pas);
	y1 = interpolate(get_value(n, i, j), get_value(n, i + 1, j),
					fmod(x / n->pas, 1));
	y2 = interpolate(get_value(n, i, j + 1), get_value(n, i + 1, j + 1),
					fmod(x / n->pas, 1));
	return (interpolate(y1, y2, fmod(y / n->pas, 1)));
}

double				noise(t_noise *noise, double x, double y)
{
	int		i;
	int		f;
	double	p;
	double	ret;


	i = -1;
	f = 1;
	p = 1.0;
	ret = 0.0;
	while (++i < noise->octave)
	{
		ret += p * noise_generator(noise, x * f, y * f);
		p *= 0.6;
		f *= 2;
	}
	return (ret * (1 - 0.6) / (1 - p));
}
