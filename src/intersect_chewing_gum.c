/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_chewing_gum.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 06:42:48 by tbeauman          #+#    #+#             */
/*   Updated: 2016/05/02 11:04:30 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			intersect_chewing_gum(t_ray *ray, t_obj *obj)
{
	int			ret;
	t_vec3		x;
	double		a[5];
	double		roots[4];

	obj->in = INFINITY;
	obj->out = INFINITY;
	x = ray->pos;
	a[4] = ft_pow(ray->dir.x, 4) + ft_pow(ray->dir.y, 4) +
		ft_pow(ray->dir.z, 4);
	a[3] = (4 * (ft_pow(ray->dir.x, 3) * x.x + ft_pow(ray->dir.y, 3) * x.y +
		ft_pow(ray->dir.z, 3) * x.z)) / a[4];
	a[2] = (6 * (ft_pow(ray->dir.x, 2) * ft_pow(x.x, 2) + ft_pow(ray->dir.y, 2)
		* ft_pow(x.y, 2) + ft_pow(ray->dir.z, 2) * ft_pow(x.z, 2))) / a[4];
	a[1] = (4 * (ray->dir.x * ft_pow(x.x, 3) + ray->dir.y * ft_pow(x.y, 3) +
		ray->dir.z * ft_pow(x.z, 3))) / a[4];
	a[0] = (ft_pow(x.x, 4) + ft_pow(x.y, 4) + ft_pow(x.z, 4) -
		ft_pow(obj->scale, 4)) / a[4];
	ret = solve_quartic(a, roots);
	if (ret >= 2)
	{
		obj->in = roots[0];
		obj->out = roots[1];
	}
	return (choose_root4(roots, ret));
}

t_vec3			chewing_gum_normal(t_vec3 *tr, t_obj *obj)
{
	t_vec3	ret;

	(void)obj;
	ret.x = 4 * pow(tr->x, 3);
	ret.y = 4 * pow(tr->y, 3);
	ret.z = 4 * pow(tr->z, 3);
	return (ret);
}
