/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 15:01:43 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/17 12:31:00 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	texture_mapping(t_obj *obj, t_vec3 hit)
{
	if (!obj->mat.texture.defined)
		return (obj->mat.color);
	if (obj->type == PLANE)
		return (texture_mapping_plane(obj, hit));
	if (obj->type == SPHERE)
		return (texture_mapping_sphere(obj, hit));
	return (obj->mat.color);
}

t_vec3	texture_mapping_plane(t_obj *obj, t_vec3 hit)
{
	int		i;
	int		j;
	t_vec3	u_axis;
	t_vec3	v_axis;

	u_axis = vec3(obj->normal.y, obj->normal.z, -obj->normal.x);
	v_axis = vec3_cross(u_axis, obj->normal);
	// 1.0 is offset, 0.35 is texture scale
	i = (1.0 + vec3_dot(hit, u_axis) * 0.35) * obj->mat.texture.w * 0.5;
	j = (1.0 + vec3_dot(hit, v_axis) * 0.35) * obj->mat.texture.h * 0.5;
	while (i > obj->mat.texture.w - 1)
		i = i - obj->mat.texture.w - 1;
	while (j > obj->mat.texture.h - 1)
		j = j - obj->mat.texture.h - 1;
	while (i < 0)
		i = i + obj->mat.texture.w;
	while (j < 0)
		j = j + obj->mat.texture.h;
	return (obj->mat.texture.img[j][i]);
}

t_vec3	texture_mapping_sphere(t_obj *obj, t_vec3 hit)
{
	t_vec3	d;
	float	u;
	float	v;
	int		i;
	int		j;

	d = vec3_norm(vec3_sub(hit, obj->pos));
	u = 0.5 + atan2(d.z, d.x) / (2.0 * M_PI);
	v = 0.5 - asin(d.y) / M_PI;
	if (obj->mat.texture.filtering)
		return (bilinear_filtering(obj, u, v));
	else
	{
		i = ft_clamp(u * obj->mat.texture.w, 0, obj->mat.texture.w - 1);
		j = ft_clamp(v * obj->mat.texture.h, 0, obj->mat.texture.h - 1);
		return (obj->mat.texture.img[j][i]);
	}
}

t_vec3	bilinear_filtering(t_obj *obj, float u, float v)
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
	bfi.c[0] = vec3_fmul(obj->mat.texture.img[bfi.y][bfi.x], bfi.uo);
	bfi.c[1] = vec3_fmul(obj->mat.texture.img[bfi.y][bfi.x + 1], bfi.ur);
	bfi.c[2] = vec3_fmul(obj->mat.texture.img[bfi.y + 1][bfi.x], bfi.uo);
	bfi.c[3] = vec3_fmul(obj->mat.texture.img[bfi.y + 1][bfi.x + 1], bfi.ur);
	color = vec3_add(vec3_fmul(vec3_add(bfi.c[0], bfi.c[1]), bfi.vo),
			vec3_fmul(vec3_add(bfi.c[2], bfi.c[3]), bfi.vr));
	return (color);
}
