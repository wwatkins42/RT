/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:27:48 by scollon           #+#    #+#             */
/*   Updated: 2016/03/19 09:10:51 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	get_intensity(t_vec3 color)
{
	double		m;

	m = (color.x + color.y + color.z) / 3.0;
	return (m);
}

static double	**get_gradient(t_vec3 **img, int y, int x, t_texture text)
{
	int		i;
	double	**grad;
	double	zero;

	i = -1;
	zero = 1;
	if (!(grad = (double**)malloc(sizeof(double*) * 3)))
		error(E_MALLOC, NULL, 1);
	while (++i < 3)
		if (!(grad[i] = (double*)malloc(sizeof(double) * 3)))
			error(E_MALLOC, NULL, 1);
	grad[0][0] = x - 1 > 0 && y - 1 > 0 ? get_intensity(img[y - 1][x - 1]) : zero;
	grad[0][1] = y - 1 > 0 ? get_intensity(img[y - 1][x]) : zero;
	grad[0][2] = y - 1 > 0 && x + 1 < text.w ? get_intensity(img[y - 1][x + 1])
				: zero;
	grad[1][0] = x - 1 > 0 ? get_intensity(img[y][x - 1]) : zero;
	grad[1][1] = 0.0;
	grad[1][2] = x + 1 < text.w ? get_intensity(img[y][x + 1]) : zero;
	grad[2][0] = y + 1 < text.h && x - 1 > 0 ? get_intensity(img[y + 1][x - 1])
				: zero;
	grad[2][1] = y + 1 < text.h ? get_intensity(img[y + 1][x]) : zero;
	grad[2][2] = y + 1 < text.h && x + 1 < text.w ?
				get_intensity(img[y + 1][x + 1]) : zero;
	return (grad);
}

// static t_vec3	compute_gradient(double **grad)
// {
// 	double		top_side;
// 	double		bottom_side;
// 	double		right_side;
// 	double		left_side;
// 	t_vec3		normal;
//
// 	top_side = grad[0][0] + grad[0][1] + grad[0][2];
// 	bottom_side = grad[2][0] + grad[2][1] + grad[2][2];
// 	right_side = grad[0][2] + grad[1][2] + grad[2][2];
// 	left_side = grad[0][0] + grad[1][0] + grad[2][0];
// 	normal.x = right_side - left_side;
// 	normal.y = bottom_side - top_side;
// 	normal.z = 8.0;
// 	ft_memdel((void*)&grad[0]);
// 	ft_memdel((void*)&grad[1]);
// 	ft_memdel((void*)&grad[2]);
// 	ft_memdel((void*)grad);
// 	vec3_clamp(&normal, 0.0, 1);
// 	return (vec3_norm(vec3_fmul(vec3_add(normal, vec3(1, 1, 1)), 0.5)));
// }

static t_vec3	compute_gradient(double **grad)
{
	t_vec3		color;
	double		diffx;
	double		diffy;
	double		scale;

	// when calculating diffx and diffy, changing order of sub values changes
	// the invertion of colors (depth).
	scale = 2.5;
	diffx = grad[1][2] - grad[1][0];
	diffy = grad[2][1] - grad[0][1];
	color.x = vec3_norm(vec3(1, diffx * scale, 0)).y;
	color.y = vec3_norm(vec3(1, diffy * scale, 0)).y;
	color.z = sqrt(1 - ft_clampf(color.x * color.x + color.y * color.y, 0, 1));
	vec3_normalize(&color);
	color = vec3_add(vec3_fmul(color, 0.5), vec3(0.5, 0.5, 0.5));
	ft_memdel((void*)&grad[0]);
	ft_memdel((void*)&grad[1]);
	ft_memdel((void*)&grad[2]);
	ft_memdel((void*)grad);
	return (color);
}

void			create_normal_map(t_obj *obj)
{
	int		x;
	int		y;
	double	**grad;

	y = -1;
	obj->mat.texture.bump =
	(t_vec3**)malloc(sizeof(t_vec3*) * obj->mat.texture.h);
	obj->mat.texture.bump == NULL ? error(E_MALLOC, NULL, 1) : 0;
	while (++y < obj->mat.texture.h)
	{
		x = -1;
		obj->mat.texture.bump[y] =
		(t_vec3*)malloc(sizeof(t_vec3) * obj->mat.texture.w);
		obj->mat.texture.bump[y] == NULL ? error(E_MALLOC, NULL, 1) : 0;
		while (++x < obj->mat.texture.w)
		{
			grad = get_gradient(obj->mat.texture.img, y, x, obj->mat.texture);
			obj->mat.texture.bump[y][x] = compute_gradient(grad);
		}
	}
}

void			bump_normal(t_obj *obj, t_ray *ray)
{
	t_vec3		tangent;
	t_vec3		binormal;
	t_vec3		bump;

	bump = texture_mapping(obj, obj->mat.texture.bump, ray->hit);
	// tangent = vec3_cross(obj->normal, vec3(1, 0, 0));
	tangent = vec3_cross(obj->normal, vec3(0, 1, 0));
	binormal = vec3_cross(tangent, obj->normal);
	// obj->normal = vec3_add(obj->normal, vec3_add(vec3_fmul(
	// 			vec3_cross(obj->normal, tangent), bump.x),
	// 			vec3_fmul(vec3_cross(binormal, obj->normal), bump.y)));
	// obj->normal = vec3_sub(vec3_fmul(obj->normal, 2), vec3(1, 1, 1));
	obj->normal = vec3_add(vec3_fmul(tangent, bump.x),
	vec3_add(vec3_fmul(binormal, bump.y), vec3_fmul(obj->normal, bump.z)));
	vec3_normalize(&obj->normal);
}
