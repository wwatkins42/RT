/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 16:31:16 by tbeauman          #+#    #+#             */
/*   Updated: 2016/03/23 11:21:50 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

typedef struct	s_cal
{
	double		tmp;
	double		dirinv[2][2];
	double		point[2];
	double		det;
	double		p;
	double		q;
}				t_cal;

double	intersect_trianglexy(t_ray *r, t_obj *t)
{
	t_cal		c;

	if ((c.tmp = intersect_plane(r, t)) == INFINITY)
		return (INFINITY);
	if ((c.det = t->pos2.x * t->pos3.y -
		t->pos2.y * t->pos3.x) == 0)
		return (INFINITY);
	c.dirinv[0][0] = t->pos3.y / c.det;
	c.dirinv[1][0] = -t->pos2.y / c.det;
	c.dirinv[0][1] = -t->pos3.x / c.det;
	c.dirinv[1][1] = t->pos2.x / c.det;
	c.point[0] = r->pos.x + c.tmp * r->dir.x - t->pos.x;
	c.point[1] = r->pos.y + c.tmp * r->dir.y - t->pos.y;
	c.p = c.dirinv[0][0] * c.point[0] + c.dirinv[0][1] * c.point[1];
	c.q = c.dirinv[1][0] * c.point[0] + c.dirinv[1][1] * c.point[1];
	if (c.p < 0 || c.q < 0 || c.p + c.q > 1)
		return (INFINITY);
	return (c.tmp);
}

double	intersect_trianglexz(t_ray *r, t_obj *t)
{
	t_cal		c;

	if ((c.tmp = intersect_plane(r, t)) == INFINITY)
		return (INFINITY);
	if ((c.det = t->pos2.x * t->pos3.z -
		t->pos2.z * t->pos3.x) == 0)
		return (INFINITY);
	c.dirinv[0][0] = t->pos3.z / c.det;
	c.dirinv[1][0] = -t->pos2.z / c.det;
	c.dirinv[0][1] = -t->pos3.x / c.det;
	c.dirinv[1][1] = t->pos2.x / c.det;
	c.point[0] = r->pos.x + c.tmp * r->dir.x - t->pos.x;
	c.point[1] = r->pos.z + c.tmp * r->dir.z - t->pos.z;
	c.p = c.dirinv[0][0] * c.point[0] + c.dirinv[0][1] * c.point[1];
	c.q = c.dirinv[1][0] * c.point[0] + c.dirinv[1][1] * c.point[1];
	if (c.p < 0 || c.q < 0 || c.p + c.q > 1)
		return (INFINITY);
	return (c.tmp);
}

double	intersect_triangleyz(t_ray *r, t_obj *t)
{
	t_cal		c;

	if ((c.tmp = intersect_plane(r, t)) == INFINITY)
		return (INFINITY);
	if ((c.det = t->pos2.y * t->pos3.z -
		t->pos2.z * t->pos3.y) == 0)
		return (INFINITY);
	c.dirinv[0][0] = t->pos3.z / c.det;
	c.dirinv[1][0] = -t->pos2.z / c.det;
	c.dirinv[0][1] = -t->pos3.y / c.det;
	c.dirinv[1][1] = t->pos2.y / c.det;
	c.point[0] = r->pos.y + c.tmp * r->dir.y - t->pos.y;
	c.point[1] = r->pos.z + c.tmp * r->dir.z - t->pos.z;
	c.p = c.dirinv[0][0] * c.point[0] + c.dirinv[0][1] * c.point[1];
	c.q = c.dirinv[1][0] * c.point[0] + c.dirinv[1][1] * c.point[1];
	if (c.p < 0 || c.q < 0 || c.p + c.q > 1)
		return (INFINITY);
	return (c.tmp);
}

double	intersect_triangle(t_ray *r, t_obj *t)
{
	if ((t->pos2.x != 0 || t->pos2.y != 0) &&
		(t->pos3.x != 0 || t->pos3.y != 0))
		return (intersect_trianglexy(r, t));
	if ((t->pos2.x != 0 || t->pos2.z != 0) &&
		(t->pos3.x != 0 || t->pos3.z != 0))
		return (intersect_trianglexz(r, t));
	if ((t->pos2.y != 0 || t->pos2.z != 0) &&
		(t->pos3.y != 0 || t->pos3.z != 0))
		return (intersect_triangleyz(r, t));
	return (INFINITY);
}

// double	intersect_triangle(t_ray *r, t_obj *t)
// {
// 	t_cal		c;
// 	int			lol;
//
// 	lol = 0;
// 	if ((c.tmp = intersect_plane(r, t)) == INFINITY)
// 		return (INFINITY);
// 	if ((t->pos2.x == 0 && t->pos2.y == 0) || (t->pos3.x == 0 && t->pos3.y == 0))
// 		lol = 1;
// 	if ((c.det = t->pos2.x * (lol ? t->pos3.z : t->pos3.y) -
// 		(lol ? t->pos2.z : t->pos2.y) * t->pos3.x) == 0)
// 		return (INFINITY);
// 	c.dirinv[0][0] = (lol ? t->pos3.z : t->pos3.y) / c.det;
// 	c.dirinv[1][0] = (lol ? -t->pos2.z : -t->pos2.y) / c.det;
// 	c.dirinv[0][1] = -t->pos3.x / c.det;
// 	c.dirinv[1][1] = t->pos2.x / c.det;
// 	c.point[0] = r->pos.x + c.tmp * r->dir.x - t->pos.x;
// 	c.point[1] = (lol ? r->pos.z : r->pos.y) + c.tmp * (lol ? r->dir.z : r->dir.y) - (lol ? t->pos.z : t->pos.y);
// 	c.p = c.dirinv[0][0] * c.point[0] + c.dirinv[0][1] * c.point[1];
// 	c.q = c.dirinv[1][0] * c.point[0] + c.dirinv[1][1] * c.point[1];
// 	if (c.p < 0 || c.q < 0 || c.p + c.q > 1)
// 		return (INFINITY);
// 	return (c.tmp);
// }
