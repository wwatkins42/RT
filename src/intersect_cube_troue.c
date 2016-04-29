/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cube_troue.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 06:42:48 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/29 13:59:45 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		intersect_cube_troue(t_ray *ray, t_obj *obj)
{
	double		a[5];
	double		root[4];
	t_vec3		x;
	int			ret;

	x = vec3_sub(ray->pos, obj->pos);
	a[4] = ft_pow(ray->dir.x, 4) + ft_pow(ray->dir.y, 4) + ft_pow(ray->dir.z, 4);
	a[3] = (4 * (ft_pow(ray->dir.x, 3) * x.x + 2 * ft_pow(ray->dir.y, 3) * x.y)) / a[4];
	a[2] = (6 * (ft_pow(ray->dir.x, 2) * ft_pow(x.x, 2) + 2 * ft_pow(ray->dir.y,
		2) * ft_pow(x.y, 2)) - 5 * (vec3_dot(ray->dir, ray->dir))) / a[4];
	a[1] = (4 * (ft_pow(x.x, 3) * ray->dir.x + ft_pow(x.y, 3) * ray->dir.y * 2) -
		10 * (ray->dir.x * x.x + 2 * ray->dir.y * x.y)) / a[4];
	a[0] = (ft_pow(x.x, 4) + ft_pow(x.y, 4) + ft_pow(x.z, 4) - 5 * (vec3_dot(x, x))) / a[4];
	ret = solve_quartic(a, root);
	return (choose_root4(root, ret));
}
