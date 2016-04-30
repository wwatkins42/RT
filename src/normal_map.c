/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:27:48 by scollon           #+#    #+#             */
/*   Updated: 2016/04/30 15:04:49 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	get_intensity(t_rgb color)
{
	double		m;
	t_vec3		tmp;

	tmp = rgb_to_vec3(color);
	m = (tmp.x + tmp.y + tmp.z) / 3.0;
	return (m);
}

static double	*get_gradient(t_rgb **img, int y, int x, t_texture text)
{
	double	actual;
	double	*grad;

	grad = NULL;
	if ((grad = (double*)malloc(sizeof(double) * 4)) == NULL)
		error(E_MALLOC, NULL, 1);
	actual = get_intensity(img[y][x]);
	grad[0] = (y - 1 > 0 ? get_intensity(img[y - 1][x]) : actual);
	grad[1] = (x - 1 > 0 ? get_intensity(img[y][x - 1]) : actual);
	grad[2] = (x + 1 < text.w ? get_intensity(img[y][x + 1]) : actual);
	grad[3] = (y + 1 < text.h ? get_intensity(img[y + 1][x]) : actual);
	return (grad);
}

static t_rgb	compute_gradient(double *grad, t_obj *obj)
{
	t_vec3		color;
	double		diffx;
	double		diffy;
	double		scale;

	scale = obj->mat.texture.normal_strength;
	diffx = grad[1] - grad[2];
	diffy = grad[0] - grad[3];
	color.x = vec3_norm(vec3(1, diffx * scale, 0)).y;
	color.y = vec3_norm(vec3(1, diffy * scale, 0)).y;
	color.z = sqrt(1 - ft_clampf(color.x * color.x + color.y * color.y, 0, 1));
	vec3_normalize(&color);
	return (vec3_to_rgb(vec3_add(vec3_fmul(color, 0.5), vec3(0.5, 0.5, 0.5))));
}

void			create_normal_map(t_obj *obj)
{
	int		x;
	int		y;
	double	*grad;

	y = -1;
	grad = NULL;
	obj->mat.texture.bump =
	(t_rgb**)malloc(sizeof(t_rgb*) * obj->mat.texture.h);
	obj->mat.texture.bump == NULL ? error(E_MALLOC, NULL, 1) : 0;
	while (++y < obj->mat.texture.h)
	{
		x = -1;
		obj->mat.texture.bump[y] =
		(t_rgb*)malloc(sizeof(t_rgb) * obj->mat.texture.w);
		obj->mat.texture.bump[y] == NULL ? error(E_MALLOC, NULL, 1) : 0;
		while (++x < obj->mat.texture.w)
		{
			grad = get_gradient(obj->mat.texture.img, y, x, obj->mat.texture);
			obj->mat.texture.bump[y][x] = compute_gradient(grad, obj);
			ft_memdel((void**)&grad);
		}
	}
}

t_vec3			bump_normal(t_obj *obj, t_ray *ray)
{
	t_vec3		normal;
	t_vec3		tangent;
	t_vec3		binormal;
	t_vec3		bump;
	t_vec3		c[2];

	normal = obj->normal;
	bump = texture_mapping(obj, obj->mat.texture.bump, ray->hit);
	bump = vec3_sub(vec3_fmul(bump, 2), vec3(1, 1, 1));
	c[0] = vec3_cross(normal, vec3(0, 0, 1));
	c[1] = vec3_cross(normal, vec3(0, 1, 0));
	tangent = (vec3_magnitude(c[0]) > vec3_magnitude(c[1]) ? c[0] : c[1]);
	tangent = vec3_sub(tangent, vec3_fmul(normal, vec3_dot(tangent, normal)));
	vec3_normalize(&tangent);
	binormal = vec3_norm(vec3_cross(normal, tangent));
	normal.x = vec3_dot(bump, vec3(tangent.x, binormal.x, normal.x));
	normal.y = vec3_dot(bump, vec3(tangent.y, binormal.y, normal.y));
	normal.z = vec3_dot(bump, vec3(tangent.z, binormal.z, normal.z));
	vec3_normalize(&normal);
	return (normal);
}
