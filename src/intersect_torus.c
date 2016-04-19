/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_torus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 02:53:33 by tbeauman          #+#    #+#             */
/*   Updated: 2016/03/24 12:50:10 by tbeauman         ###   ########.fr       */
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
}/*
double	intersect_torus(t_ray *ray, t_obj *obj)
{
	t_poly4		p;
	double		dd;
	double		pp;
	double		pd;
	double		grgr;
	double		prpr;
	double		pppgrgrmprpr;
	int			ret;
	// t_vec3		len;

	// len = vec3_sub(ray->pos, obj->pos);
	dd = vec3_dot(ray->dir, ray->dir);
	pp = vec3_dot(ray->pos, ray->pos);
	pd = vec3_dot(ray->dir, ray->pos);
	grgr = obj->gr * obj->gr;
	prpr = obj->pr * obj->pr;
	pppgrgrmprpr = pp + grgr - prpr;
	p.a4 = dd * dd;
	p.a3 = 4 * dd * vec3_dot(ray->dir, ray->pos);
	p.a2 = 2 * dd * pppgrgrmprpr + pd * pd -
		4 * grgr * (ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z);
	p.a1 = 4 * pd * pppgrgrmprpr - 8 * grgr * (ray->dir.x * ray->pos.x + ray->dir.z * ray->pos.z);
	p.a0 = pppgrgrmprpr * pppgrgrmprpr - 4 * grgr * (ray->pos.x * ray->pos.x + ray->pos.z * ray->pos.z);
	ret = solve_quartic(&p);
	return (choose_root(p, ret));
}
*/
double		intersect_torus(t_ray *ray, t_obj *obj)
{
	double		m;
	double		n;
	double		o;
	t_poly4		pol;
	double		p;
	double		q;
	t_vec3		x;
	double		grgr;
	double		prpr;
	int			ret;
	double		d;


	grgr = obj->gr * obj->gr;
	prpr = obj->pr * obj->pr;
	x = vec3_sub(ray->pos, obj->pos);
	m = vec3_dot(ray->dir, ray->dir);
	n = vec3_dot(ray->dir, x);
	o = vec3_dot(x, x);
	p = vec3_dot(ray->dir, obj->dir);
	q = vec3_dot(x, obj->dir);
	d = o + grgr - prpr;
	pol.a4 = 1;
	pol.a3 = 4 * n;
	pol.a2 = 2 * d + pol.a3 * pol.a3 / 4 - 4 * grgr * (1 - vec3_dot(ray->dir, obj->dir));
	pol.a1 = pol.a3 * d - 4 * grgr * 2 * (vec3_dot(x, ray->hit) - vec3_dot(obj->dir, x) * vec3_dot(ray->dir, obj->dir));
	pol.a0 = d * d - 4 * grgr * o - q * q;
	ret = solve_quartic(&pol);
	return (choose_root(pol, ret));
}
