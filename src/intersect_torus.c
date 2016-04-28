/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_torus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 02:53:33 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/28 14:26:22 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		fonction_relativement_assez_nulle(double *r, double *zarr)
{
	r[0] = zarr[0];
	r[1] = zarr[1];
	r[2] = zarr[2];
	r[3] = zarr[3];
}

static void	compute_coeffs(t_ray *ray, t_obj *obj, double *a)
{
	t_vec3	x;
	double	dd;
	double	e;
	double	f;
	double	four_aa;

	x = vec3_sub(ray->pos, obj->pos);
	dd = vec3_dot(ray->dir, ray->dir);
	e = vec3_dot(x, x) - obj->gr - obj->pr;
	f = vec3_dot(x, ray->dir);
	four_aa = 4 * obj->gr;
	a[0] = (e * e - four_aa * (obj->pr - x.y * x.y)) / dd * dd;
	a[1] = (4 * f * e + 2 * four_aa * x.y * ray->dir.y) / dd * dd;
	a[2] = (2 * dd * e + 4 * f * f + four_aa * ray->dir.y * ray->dir.y) /
		dd * dd;
	a[3] = (4 * dd * f) / dd * dd;
}

double		intersect_torus(t_ray *ray, t_obj *obj)
{
	double	a[4];
	double	roots[4];
	int		num_real_roots;

	compute_coeffs(ray, obj, a);
	num_real_roots = solve_quartic(a, roots);
	if (num_real_roots == 0)
		return (INFINITY);
	if (num_real_roots == 2)
	{
		if (roots[0] < 0)
			return (roots[1] < 0 ? INFINITY : roots[1]);
		else
			return (roots[0]);
	}
	num_real_roots = 0;
	while (num_real_roots < 4)
	{
		if (roots[num_real_roots] > 0)
			return (roots[num_real_roots]);
		num_real_roots++;
	}
	return (INFINITY);
}
