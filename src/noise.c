/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:55:16 by scollon           #+#    #+#             */
/*   Updated: 2016/04/18 10:55:01 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_noise				init_noise_structure(int w, int h, int pas, int octave)
{
	int		i;
	int		poctave;
	t_noise	noise;

	i = -1;
	noise.octave = octave;
	noise.pas = pas;
	poctave = pow(2, noise.octave - 1);
	noise.w_max = (int)ceil(w * poctave / noise.pas);
	noise.h_max = (int)ceil(h * poctave / noise.pas);
	noise.len = noise.w_max * noise.h_max;
	if (!(noise.noise = (double*)malloc(sizeof(double) * noise.len)))
		error(E_MALLOC, NULL, 1);
	while (++i < noise.len)
		noise.noise[i] = ((double)rand()) / RAND_MAX;
	return (noise);
}

static double		interpolate(double a, double b, double x)
{
	return (a * (1 - x) + b * x);
}

static double		get_value(t_noise *n, int i, int j)
{
	return (n->noise[(i % n->w_max) + (j % n->h_max) * n->w_max]);
}

static double		noise_generator(t_noise *n, double x, double y)
{
	int		i;
	int		j;
	double	y[2];
	double	xpas;
	double	ypas;

	xpas = x / n->pas;
	ypas = y / n->pas;
	i = (int)(xpas);
	j = (int)(ypas);
	y[0] = interpolate(get_value(n, i, j), get_value(n, i + 1, j),
					fmod(xpas, 1));
	y[1] = interpolate(get_value(n, i, j + 1), get_value(n, i + 1, j + 1),
					fmod(xpas, 1));
	return (interpolate(y[0], y[1], fmod(ypas, 1)));
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
