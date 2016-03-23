/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_torus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 02:53:33 by tbeauman          #+#    #+#             */
/*   Updated: 2016/03/22 02:24:30 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// double		newtons_method(t_poly4 f, t_poly4 fprime, double xk)
// {
// 	double	fxk;
//
// 	fxk = eval_poly(f, xk);
// 	if (fxk == 0)
// 		return (xk);
// 	return (newtons_method(f, fprime, xk - fxk / eval_poly(fprime, xk)));
// }

double	choose_root(t_poly4 p, int r)
{
	double	ret;

	if (r == 0)
		return (INFINITY);
	if (r == 2)
	{
		if (fabsl(p.root1) < EPSILON)
			return (fabsl(p.root2) < EPSILON ? 0 : p.root2);
		if (p.root1 < 0)
			return (p.root2 < 0 ? INFINITY : p.root2);
		else
			return (p.root1);
	}
	fabsl(p.root1) < EPSILON ? p.root1 = 0 : 0;
	fabsl(p.root2) < EPSILON ? p.root2 = 0 : 0;
	fabsl(p.root3) < EPSILON ? p.root3 = 0 : 0;
	fabsl(p.root4) < EPSILON ? p.root4 = 0 : 0;
	p.root1 < 0 ? p.root1 = INFINITY : 0;
	p.root2 < 0 ? p.root2 = INFINITY : 0;
	p.root3 < 0 ? p.root3 = INFINITY : 0;
	p.root4 < 0 ? p.root4 = INFINITY : 0;
	ret = p.root1;
	if (ret > p.root2)
		ret = p.root2;
	if (ret > p.root3)
		ret = p.root3;
	if (ret > p.root4)
		ret = p.root4;
	// if (ret <= p.root1 || ret <= p.root2 || ret <= p.root3 || ret <= p.root4)
		// printf("minimum fails\n");
	return (ret);
}
// double	intersect_torus(t_ray *ray, t_obj *obj)
// {
// 	t_poly4		p;
// 	double		dd;
// 	double		pp;
// 	double		pd;
// 	double		grgr;
// 	double		prpr;
// 	double		pppgrgrmprpr;
// 	int			ret;
// 	t_vec3		len;
//
// 	len = vec3_sub(ray->pos, obj->pos);
// 	dd = vec3_dot(ray->dir, ray->dir);
// 	pp = vec3_dot(len, len);
// 	pd = vec3_dot(ray->dir, len);
// 	grgr = obj->gr * obj->gr;
// 	prpr = obj->pr * obj->pr;
// 	pppgrgrmprpr = pp + grgr - prpr;
// 	p.a4 = dd * dd;
// 	p.a3 = 4 * dd * vec3_dot(ray->dir, len);
// 	p.a2 = 2 * dd * pppgrgrmprpr + pd * pd -
// 		4 * grgr * (dd - ray->dir.y * ray->dir.y);
// 	p.a1 = 4 * pd * pppgrgrmprpr - 8 * grgr * (pd - ray->dir.y * len.y);
// 	p.a0 = pppgrgrmprpr - 4 * grgr * (pp - len.y * len.y);
// 	ret = solve_quartic(&p);
// 	return (choose_root(p, ret));
// }

double		intersect_torus(t_ray *ray, t_obj *obj)
{
	double		m;
	double		n;
	double		o;
	t_poly6		pol;
	double		p;
	double		q;
	t_vec3		x;
	double		grgr;
	double		prpr;
	int			ret;


	grgr = obj->gr * obj->gr;
	prpr = obj->pr * obj->pr;
	x = vec3_sub(ray->pos, obj->pos);
	m = 1;//vec3_dot(ray->dir, ray->dir);
	n = vec3_dot(ray->dir, x);
	o = vec3_dot(x, x);
	p = vec3_dot(ray->dir, obj->dir);
	q = vec3_dot(x, obj->dir);
	pol.a[6] = 0;
	pol.a[5] = 0;
	pol.a[4] = m * m;
	pol.a[3] = 4 * m * n;
	pol.a[2] = 4 * m * m + 2 * m * o - 2 * (grgr + prpr) * m + 4 * grgr * p * p;
	pol.a[1] = 4 * n * o - 4 * (grgr + prpr) * n + 8 * grgr * p * q;
	pol.a[0] = o * o - 2 * (grgr + prpr) * o +
		4 * grgr * q * q + (grgr - prpr) * (grgr - prpr);
	// if (number_roots(pol))
	// {
		t_poly4	poly;

		poly = (t_poly4){pol.a[0], pol.a[1], pol.a[2], pol.a[3], pol.a[4], 0, 0, 0, 0};
		ret = solve_quartic(&poly);
		if (ret > 500)
			return (-1);
		return (choose_root(poly, ret));
	// }
	// else
	// 	return (INFINITY);
}
