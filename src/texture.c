/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 15:01:43 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/16 16:46:25 by wwatkins         ###   ########.fr       */
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
	i = u * obj->mat.texture.w;
	j = v * obj->mat.texture.h;
	i > obj->mat.texture.w - 1 ? i = obj->mat.texture.w - 1 : 0;
	j > obj->mat.texture.h - 1 ? j = obj->mat.texture.h - 1 : 0;
	return (obj->mat.texture.img[j][i]);
}
//
// t_vec3	bilinear_filtering(t_obj *obj, float u, float v);
// {
// }
