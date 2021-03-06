/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_parallelogram.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 04:56:21 by tbeauman          #+#    #+#             */
/*   Updated: 2016/05/02 19:35:19 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	intersect_parallelogramxy(t_ray *r, t_obj *t)
{
	t_cal		c;

	if ((c.tmp = intersect_plane(r, t)) == INFINITY)
		return (INFINITY);
	if ((c.det = t->pos2.x * t->pos3.y - t->pos2.y * t->pos3.x) == 0)
		return (INFINITY);
	c.dirinv[0][0] = t->pos3.y / c.det;
	c.dirinv[1][0] = -t->pos2.y / c.det;
	c.dirinv[0][1] = -t->pos3.x / c.det;
	c.dirinv[1][1] = t->pos2.x / c.det;
	c.point[0] = r->pos.x + c.tmp * r->dir.x;
	c.point[1] = r->pos.y + c.tmp * r->dir.y;
	c.p = c.dirinv[0][0] * c.point[0] + c.dirinv[0][1] * c.point[1];
	c.q = c.dirinv[1][0] * c.point[0] + c.dirinv[1][1] * c.point[1];
	if (c.p < 0 || c.q < 0 || c.p > 1 || c.q > 1)
		return (INFINITY);
	return (c.tmp);
}

double	intersect_parallelogramxz(t_ray *r, t_obj *t)
{
	t_cal		c;

	if ((c.tmp = intersect_plane(r, t)) == INFINITY)
		return (INFINITY);
	if ((c.det = t->pos2.x * t->pos3.z - t->pos2.z * t->pos3.x) == 0)
		return (INFINITY);
	c.dirinv[0][0] = t->pos3.z / c.det;
	c.dirinv[1][0] = -t->pos2.z / c.det;
	c.dirinv[0][1] = -t->pos3.x / c.det;
	c.dirinv[1][1] = t->pos2.x / c.det;
	c.point[0] = r->pos.x + c.tmp * r->dir.x;
	c.point[1] = r->pos.z + c.tmp * r->dir.z;
	c.p = c.dirinv[0][0] * c.point[0] + c.dirinv[0][1] * c.point[1];
	c.q = c.dirinv[1][0] * c.point[0] + c.dirinv[1][1] * c.point[1];
	if (c.p < 0 || c.q < 0 || c.p > 1 || c.q > 1)
		return (INFINITY);
	return (c.tmp);
}

double	intersect_parallelogramyz(t_ray *r, t_obj *t)
{
	t_cal		c;

	if ((c.tmp = intersect_plane(r, t)) == INFINITY)
		return (INFINITY);
	if ((c.det = t->pos2.y * t->pos3.z - t->pos2.z * t->pos3.y) == 0)
		return (INFINITY);
	c.dirinv[0][0] = t->pos3.z / c.det;
	c.dirinv[1][0] = -t->pos2.z / c.det;
	c.dirinv[0][1] = -t->pos3.y / c.det;
	c.dirinv[1][1] = t->pos2.y / c.det;
	c.point[0] = r->pos.y + c.tmp * r->dir.y;
	c.point[1] = r->pos.z + c.tmp * r->dir.z;
	c.p = c.dirinv[0][0] * c.point[0] + c.dirinv[0][1] * c.point[1];
	c.q = c.dirinv[1][0] * c.point[0] + c.dirinv[1][1] * c.point[1];
	if (c.p < 0 || c.q < 0 || c.p > 1 || c.q > 1)
		return (INFINITY);
	return (c.tmp);
}

double	intersect_parallelogram(t_ray *r, t_obj *t)
{
	if ((t->pos2.x != 0 || t->pos2.y != 0) &&
		(t->pos3.x != 0 || t->pos3.y != 0))
		return (intersect_parallelogramxy(r, t));
	if ((t->pos2.x != 0 || t->pos2.z != 0) &&
		(t->pos3.x != 0 || t->pos3.z != 0))
		return (intersect_parallelogramxz(r, t));
	if ((t->pos2.y != 0 || t->pos2.z != 0) &&
		(t->pos3.y != 0 || t->pos3.z != 0))
		return (intersect_parallelogramyz(r, t));
	return (INFINITY);
}
