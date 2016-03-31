/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 15:01:43 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/30 17:36:18 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_vec3	bilinear_filtering(t_obj *obj, t_vec3 **img, float u, float v)
{
	t_vec3	color;
	t_bfi	bfi;

	u = u * obj->mat.texture.w - 0.5;
	v = v * obj->mat.texture.h - 0.5;
	bfi.x = ft_clamp(floor(u), 0, obj->mat.texture.w - 2);
	bfi.y = ft_clamp(floor(v), 0, obj->mat.texture.h - 2);
	bfi.ur = u - bfi.x;
	bfi.vr = v - bfi.y;
	bfi.uo = 1 - bfi.ur;
	bfi.vo = 1 - bfi.vr;
	bfi.c[0] = vec3_fmul(img[bfi.y][bfi.x], bfi.uo);
	bfi.c[1] = vec3_fmul(img[bfi.y][bfi.x + 1], bfi.ur);
	bfi.c[2] = vec3_fmul(img[bfi.y + 1][bfi.x], bfi.uo);
	bfi.c[3] = vec3_fmul(img[bfi.y + 1][bfi.x + 1], bfi.ur);
	color = vec3_add(vec3_fmul(vec3_add(bfi.c[0], bfi.c[1]), bfi.vo),
			vec3_fmul(vec3_add(bfi.c[2], bfi.c[3]), bfi.vr));
	return (color);
}

static t_vec3	texture_mapping_plane(t_obj *obj, t_vec3 **img, t_vec3 hit)
{
	float	u;
	float	v;
	float	offset;
	t_vec3	u_axis;
	t_vec3	v_axis;

	offset = 0;
	u_axis = vec3(-obj->normal.z, obj->normal.y, -obj->normal.x);
	if (obj->mat.texture.rotation == 90)
		u_axis = vec3(obj->normal.y, obj->normal.z, -obj->normal.x);
	else if (obj->mat.texture.rotation == 180)
		u_axis = vec3(obj->normal.z, obj->normal.y, -obj->normal.x);
	else if (obj->mat.texture.rotation == 270)
		u_axis = vec3(obj->normal.y, -obj->normal.z, -obj->normal.x);
	v_axis = vec3_cross(u_axis, obj->normal);
	u = offset + vec3_dot(hit, u_axis) * obj->mat.texture.scale;
	v = offset + vec3_dot(hit, v_axis) * obj->mat.texture.scale;
	u = u - floor(u);
	v = v - floor(v);
	if (obj->mat.texture.filtering)
		return (bilinear_filtering(obj, img, u, v));
	else
		return (img[(int)(v * (obj->mat.texture.h - 1))]
				[(int)(u * (obj->mat.texture.w - 1))]);
}

static t_vec3	texture_mapping_sphere(t_obj *obj, t_vec3 **img, t_vec3 hit)
{
	t_vec3	d;
	float	u;
	float	v;
	int		i;
	int		j;

	d = vec3_norm(vec3_sub(hit, obj->pos));
	u = 0.5 + atan2(d.z, d.x) / M_PI * 0.5;
	v = 0.5 - asin(d.y) / M_PI;
	if (obj->mat.texture.filtering)
		return (bilinear_filtering(obj, img, u, v));
	else
	{
		i = ft_clamp(u * obj->mat.texture.w, 0, obj->mat.texture.w - 1);
		j = ft_clamp(v * obj->mat.texture.h, 0, obj->mat.texture.h - 1);
		return (img[j][i]);
	}
}

static t_vec3	texture_mapping_cylinder(t_obj *obj, t_vec3 **img, t_vec3 hit)
{
	t_vec3	d;
	float	u;
	float	v;
	int		i;
	int		j;

	d = vec3_sub(hit, vec3_mul(obj->pos, obj->dir));
	u = 0.5 + atan2(d.z, d.x) / M_PI * 0.5;
	v = d.y / (obj->max - obj->min);
	v = v - floor(v);
	if (obj->mat.texture.filtering)
		return (bilinear_filtering(obj, img, u, v));
	else
	{
		i = ft_clamp(u * obj->mat.texture.w, 0, obj->mat.texture.w - 1);
		j = ft_clamp(v * obj->mat.texture.h, 0, obj->mat.texture.h - 1);
		return (img[j][i]);
	}
}

t_vec3			texture_mapping(t_obj *obj, t_vec3 **img, t_vec3 hit)
{
	if (!obj->mat.texture.defined)
		return (obj->mat.color);
	if (obj->type == PLANE || obj->type == TRIANGLE ||
		obj->type == PARALLELOGRAM)
		return (texture_mapping_plane(obj, img, hit));
	else if (obj->type == SPHERE)
		return (texture_mapping_sphere(obj, img, hit));
	else if (obj->type == CYLINDER || obj->type == CONE)
		return (texture_mapping_cylinder(obj, img, hit));
	return (obj->mat.color);
}
