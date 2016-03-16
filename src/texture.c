/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 15:01:43 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/16 16:15:47 by wwatkins         ###   ########.fr       */
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
	double	u;
	double	v;
	int		i;
	int		j;

	t_vec3	uaxis = vec3(obj->normal.y, obj->normal.z, obj->normal.x);
	t_vec3	vaxis = vec3_cross(uaxis, obj->normal);

	u = vec3_dot(hit, uaxis) * 0.25 + 1;
	v =	vec3_dot(hit, vaxis) * 0.25 + 1;
	i = u * obj->mat.texture.w * 0.5;
	j = v * obj->mat.texture.h * 0.5;
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
	double	u;
	double	v;
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
