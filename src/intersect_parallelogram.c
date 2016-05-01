/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_parallelogram.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 04:56:21 by tbeauman          #+#    #+#             */
/*   Updated: 2016/05/01 18:05:45 by tbeauman         ###   ########.fr       */
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
	c.point[0] = r->pos.x + c.tmp * r->dir.x - t->pos.x;
	c.point[1] = r->pos.y + c.tmp * r->dir.y - t->pos.y;
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
	c.point[0] = r->pos.x + c.tmp * r->dir.x - t->pos.x;
	c.point[1] = r->pos.z + c.tmp * r->dir.z - t->pos.z;
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
	c.point[0] = r->pos.y + c.tmp * r->dir.y - t->pos.y;
	c.point[1] = r->pos.z + c.tmp * r->dir.z - t->pos.z;
	c.p = c.dirinv[0][0] * c.point[0] + c.dirinv[0][1] * c.point[1];
	c.q = c.dirinv[1][0] * c.point[0] + c.dirinv[1][1] * c.point[1];
	if (c.p < 0 || c.q < 0 || c.p > 1 || c.q > 1)
		return (INFINITY);
	return (c.tmp);
}
//
// double	intersect_parallelogram(t_ray *r, t_obj *t)
// {
// 	if ((t->pos2.x != 0 || t->pos2.y != 0) &&
// 		(t->pos3.x != 0 || t->pos3.y != 0))
// 		return (intersect_parallelogramxy(r, t));
// 	if ((t->pos2.x != 0 || t->pos2.z != 0) &&
// 		(t->pos3.x != 0 || t->pos3.z != 0))
// 		return (intersect_parallelogramxz(r, t));
// 	if ((t->pos2.y != 0 || t->pos2.z != 0) &&
// 		(t->pos3.y != 0 || t->pos3.z != 0))
// 		return (intersect_parallelogramyz(r, t));
// 	return (INFINITY);
// }
//
//
double	intersect_parallelogram(t_ray *ray, t_obj *t)
{
	t_vec3		e1;
	t_vec3		e2;
	t_triangle	tri;
	double		intersection;

	e1 = vec3_sub(t->pos2, t->pos);
	e2 = vec3_sub(t->pos3, t->pos);
	tri.p = vec3_cross(ray->dir, e2);
	tri.det = vec3_dot(e1, tri.p);
	if (tri.det > -EPSILON && tri.det < EPSILON)
		return (INFINITY);
	tri.vertex_camera_direction = ray->pos;
	tri.u = vec3_dot(tri.vertex_camera_direction, tri.p) * (1 / tri.det);
	if (tri.u < 0 || tri.u > 1)
		return (INFINITY);
	tri.q = vec3_cross(tri.vertex_camera_direction, e1);
	tri.v = vec3_dot(ray->dir, tri.q) * (1 / tri.det);
	if (tri.v < 0 || tri.v > 1)
		return (INFINITY);
	intersection = vec3_dot(e2, tri.q) * (1 / tri.det);
	if (intersection > EPSILON)
		return (intersection);
	return (INFINITY);
}
