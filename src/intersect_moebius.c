/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_moebius.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 11:01:19 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/29 15:55:32 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			choose_root3(double *roots, int ret)
{
	if (ret == 1)
		return (roots[0] < 0 ? INFINITY : roots[0]);
	ret = 0;
	while (ret < 3)
	{
		if (roots[ret] > 0)
			return (roots[ret]);
		ret++;
	}
	return (INFINITY);
}

static double	choose_mobi_root(double *roots, int ret, t_ray *ray, t_obj *obj)
{
	int			i;
	t_vec3		hit;
	double		norme;

	i = 0;
	while (i < ret)
	{
		if (roots[i] > EPSILON)
		{
			hit = vec3_add(vec3_fmul(ray->dir, roots[i]), ray->pos);
			norme = vec3_magnitude(hit);
			if (norme > obj->min && norme < obj->max)
				return (roots[i]);
		}
		i++;
	}
	return (INFINITY);
}

static void		init_coeffs(t_moebius m, double *a)
{
	a[3] = (-2 * m.c * m.c * m.g + m.e * m.c * m.c + m.e * m.g * m.g - 2 * m.e *
		m.e * m.g + m.e * m.e * m.e);
	a[2] = (-2 * m.c * m.g + 2 * m.b * m.c * m.e - 4 * m.b * m.c * m.g + m.c *
		m.c * m.d - 2 * m.c *
		m.c * m.f + 3 * m.d * m.e * m.e - 4 * m.d * m.e * m.g - 2 * m.e * m.e *
		m.f + m.d * m.g * m.g + 2 *
		m.e * m.f * m.g) / a[3];
	a[1] = (-m.e - 2 * m.b * m.g - 2 * m.c * m.f + m.b * m.b * m.e - 2 * m.b *
		m.b * m.g + 2 * m.b * m.c * m.d - 4 * m.b * m.c * m.f + 3 * m.d * m.d *
		m.e - 2 * m.d * m.d * m.g + 2
		* m.d * m.g * m.f - 4 * m.e * m.d * m.f + m.e * m.f * m.f) / a[3];
	a[0] = (-m.d - 2 * m.b * m.f + m.b * m.b * m.d - 2 * m.b * m.b * m.f + m.d *
		m.d * m.d - 2 * m.d * m.d
		* m.f + m.d * m.f * m.f) / a[3];
}

double			intersect_moebius(t_ray *ray, t_obj *obj)
{
	double		a[4];
	double		root[3];
	t_moebius	m;
	t_vec3		x;
	int			ret;

	x = vec3_sub(ray->pos, obj->pos);
	m.b = x.x;
	m.c = ray->dir.x;
	m.d = x.y;
	m.e = ray->dir.y;
	m.f = x.z;
	m.g = ray->dir.z;
	init_coeffs(m, a);
	ret = solve_cubic(a, root);
	return (choose_mobi_root(root, ret, ray, obj));
}
