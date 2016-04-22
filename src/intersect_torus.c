/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_torus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 02:53:33 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/22 15:09:16 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

//
// double	choose_root(gsl_complex_packed_ptr roots)
// {
// 	double	ret;
// 	int		i;
//
// 	i = 1;
// 	while (i < 8)
// 	{
// 		if (roots[i] != 0)
// 			roots[i - 1] = INFINITY;
// 		i += 2;
// 	}
// 	roots[0] < 0 ? roots[0] = INFINITY : 0;
// 	roots[2] < 0 ? roots[2] = INFINITY : 0;
// 	roots[4] < 0 ? roots[4] = INFINITY : 0;
// 	roots[6] < 0 ? roots[6] = INFINITY : 0;
// 	ret = roots[0];
// 	i = 2;
// 	while (i < 8)
// 	{
// 		if (ret > roots[i])
// 			ret = roots[i];
// 		i += 2;
// 	}
// 	return (ret);
// }
double	choose_root(gsl_complex_packed_ptr roots)
{
	double	ret;
	int		i;

	if (!(roots[1] == 0. || roots[3] == 0. || roots[5] == 0. || roots[7] == 0.))
		return (INFINITY);
	roots[0] < 0 ? roots[0] = INFINITY : 0;
	roots[2] < 0 ? roots[2] = INFINITY : 0;
	roots[4] < 0 ? roots[4] = INFINITY : 0;
	roots[6] < 0 ? roots[6] = INFINITY : 0;
	ret = INFINITY;
	i = 0;
	while (i < 8)
	{
		if (roots[i + 1] != 0. && ret > roots[i])
			ret = roots[i];
		i += 2;
	}
	return (ret);
}

double		intersect_torus(t_ray *ray, t_obj *obj)
{
	double		a[5];
	double		roots[8];
	t_vec3		x;
	double		m;
	double		n;
	double		o;
	double		p;
	double		q;
	double		grgr;
	double		prpr;
	double 		mm;

	x = vec3_sub(ray->pos, obj->pos);
	grgr = obj->gr * obj->gr;
	prpr = obj->pr * obj->pr;
	m = vec3_dot(ray->dir, ray->dir);
	mm = m * m;
	n = vec3_dot(ray->dir, x);
	o = vec3_dot(x, x);
	p = vec3_dot(ray->dir, obj->dir);
	q = vec3_dot(x, obj->dir);

/*
** HUGI
*/
	a[4] = 1;
	a[3] = (4 * m * n) / mm;
	a[2] = (4 * mm + 2 * m * o - 2 * (grgr + prpr) * m + 4 * grgr * p * p) / mm;
	a[1] = (4 * n * o - 4 * (grgr + prpr) * n + 8 * grgr * p * q) / mm;
	a[0] = (o * o - 2 * (grgr + prpr) * o + 4 * grgr * q * q + (grgr - prpr) * (grgr - prpr)) / mm;

/*
** HEIGEAS
*/
	// a[4] = mm;
	// a[3] = 4 * m * n;
	// a[2] = 2 * m * (o + grgr - prpr) + n * n - 4 * grgr * (m - ray->dir.z * ray->dir.z);
	// a[1] = 4 * n * (o + grgr - prpr) - 8 * grgr * (m - ray->dir.z * ray->dir.z);
	// a[0] = (o + grgr - prpr) * (o + grgr - prpr) - 4 * grgr * (m - ray->dir.z * ray->dir.z);

	gsl_poly_complex_workspace *w =  gsl_poly_complex_workspace_alloc(5);
	gsl_poly_complex_solve(a, 5, w, roots);
	gsl_poly_complex_workspace_free(w);
	return (choose_root(roots));
}
