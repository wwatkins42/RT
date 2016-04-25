/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_torus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 02:53:33 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/25 23:40:05 by tbeauman         ###   ########.fr       */
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

//	if (roots[1] == 0. || roots[3] == 0. || roots[5] == 0. || roots[7] == 0.)
//	{
//		return (1);
//	}
//	return (INFINITY);
	if (roots[1] != 0. && roots[3] != 0. && roots[5] != 0. && roots[7] != 0.)
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
	return (ret < 0 ? INFINITY : ret);
}

double		intersect_torus(t_ray *ray, t_obj *obj)
{
	/*
	** HUGI WAY
	*/
	// double		a[5];
	// double		roots[8];
	// t_vec3		x;
	// double		m;
	// double		n;
	// double		o;
	// double		p;
	// double		q;
	// double		grgr;
	// double		prpr;
	// double 		mm;
	//
	// x = ray->pos;
	// grgr = obj->gr * obj->gr;
	// prpr = obj->pr * obj->pr;
	// m = vec3_dot(ray->dir, ray->dir);
	// mm = m * m;
	// n = vec3_dot(ray->dir, x);
	// o = vec3_dot(x, x);
	// p = vec3_dot(ray->dir, obj->dir);
	// q = vec3_dot(x, obj->dir);

	// a[4] = mm;
	// a[3] = (4 * m * n);
	// a[2] = (4 * mm + 2 * m * o - 2 * (grgr + prpr) * m + 4 * grgr * p * p);
	// a[1] = (4 * n * o - 4 * (grgr + prpr) * n + 8 * grgr * p * q);
	// a[0] = (o * o - 2 * (grgr + prpr) * o + 4 * grgr * q * q + (grgr - prpr) * (grgr - prpr));
/*
** SEB WAY
*/

	double	x1 = ray->pos.x;
	double	y1 = ray->pos.y;
	double	z1 = ray->pos.z;
	double	d1 = ray->dir.x;
	double	d2 = ray->dir.y;
	double	d3 = ray->dir.z;

	double	a[5];
	double	roots[4];

	double	dd = d1 * d1 + d2 * d2 + d3 * d3;
	double	e = x1 * x1 + y1 * y1 + z1 * z1 - obj->gr * obj->gr - obj->pr * obj->pr;
	double	f = x1 * d1 + y1 * d2 + z1 * d3;
	double	four_aa = 4 * obj->gr * obj->gr;

	a[0] = e * e - four_aa * (obj->pr * obj->pr - y1 * y1);
	a[1] = 4 * f * e + 2 * four_aa * y1 * d2;
	a[2] = 2 * dd * e + 4 * f * f + four_aa * d2 * d2;
	a[3] = 4 * dd * f;
	a[4] = dd * dd;
	int num_real_roots = gsl_poly_solve_quartic(a[3] / a[4], a[2] / a[4], a[1] / a[4], a[0] / a[4], &roots[0], &roots[1], &roots[2], &roots[3]);
	if (num_real_roots == 0)
		return (-1);
	return (roots[0]);

/*
** COMPUTE ROOT
*/

	gsl_poly_complex_workspace *w =  gsl_poly_complex_workspace_alloc(5);
	gsl_poly_complex_solve(a, 5, w, roots);
	gsl_poly_complex_workspace_free(w);
	return (choose_root(roots));
}
