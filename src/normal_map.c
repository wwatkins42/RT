/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:27:48 by scollon           #+#    #+#             */
/*   Updated: 2016/03/21 14:10:08 by wwatkins         ###   ########.fr       */
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

static t_vec3	compute_gradient(double **grad)
{
	t_vec3		color;
	double		diffx;
	double		diffy;
	double		scale;

	// when calculating diffx and diffy, changing order of sub values changes
	// the invertion of colors (depth).
	scale = 2.5;
	diffx = grad[1][0] - grad[1][2];
	diffy = grad[0][1] - grad[2][1];
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

t_vec3			bump_normal(t_obj *obj, t_ray *ray)
{
	t_vec3		normal;
	t_vec3		tangent;
	t_vec3		binormal;
	t_vec3		bump;
	t_vec3		c[2];

	normal = obj->normal;
	bump = texture_mapping(obj, obj->mat.texture.bump, ray->hit);
	bump = vec3_sub(vec3_fmul(bump, 2.0), vec3(1, 1, 1));
	c[0] = vec3_cross(normal, vec3(0, 0, 1));
	c[1] = vec3_cross(normal, vec3(0, 1, 0));
	// tangent = vec3_magnitude(c[0]) > vec3_magnitude(c[1]) ? c[0] : c[1];
	tangent = c[1];
	vec3_normalize(&tangent);
	binormal = vec3_cross(normal, tangent);
	vec3_normalize(&binormal);
	normal.x = vec3_dot(bump, tangent);
	normal.y = vec3_dot(bump, binormal);
	normal.z = vec3_dot(bump, obj->normal);
	vec3_normalize(&normal);
	return (normal);
}
