/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cube_troue.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 06:42:48 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/30 17:42:12 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		intersect_cube_troue(t_ray *r, t_obj *obj)
{
	double		a[5];
	double		root[4];
	t_vec3		x;
	int			ret;

	x = r->pos;
	// x = vec3_sub(r->pos, obj->pos);
	// vec3_rotate(&x, vec3_fmul(obj->rot, -1));
	a[4] = ft_pow(r->dir.x, 4) + ft_pow(r->dir.y, 4) + ft_pow(r->dir.z, 4);
	a[3] = (4 * (ft_pow(r->dir.x, 3) * x.x + ft_pow(r->dir.y, 3) * x.y +
		ft_pow(r->dir.z, 3) * x.z)) / a[4];
	a[2] = (6 * (ft_pow(r->dir.x, 2) * ft_pow(x.x, 2) + ft_pow(r->dir.y, 2) *
		ft_pow(x.y, 2) + ft_pow(r->dir.z, 2) * ft_pow(x.z, 2)) -
		5 * vec3_dot(r->dir, r->dir)) / a[4];
	a[1] = (4 * (ft_pow(x.x, 3) * r->dir.x + ft_pow(x.y, 3) * r->dir.y +
		ft_pow(x.z, 3) * r->dir.z) - 10 * vec3_dot(r->dir, x)) / a[4];
	a[0] = (ft_pow(x.x, 4) + ft_pow(x.y, 4) + ft_pow(x.z, 4) -
		5 * vec3_dot(x, x) + obj->scale) / a[4];
	ret = solve_quartic(a, root);
	return (choose_root4(root, ret));
}
