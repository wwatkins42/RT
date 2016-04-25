/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cube_troue.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 06:42:48 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/25 17:13:01 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		intersect_cube_troue(t_ray *ray, t_obj *obj)
{
	t_poly4		p;
	t_vec3		x;
	int			ret;

	x = vec3_sub(ray->pos, obj->pos);
	p.a4 = ft_pow(ray->dir.x, 4) + ft_pow(ray->dir.y, 4) + ft_pow(ray->dir.z, 4);
	p.a3 = 4 * (ft_pow(ray->dir.x, 3) * x.x + 2 * ft_pow(ray->dir.y, 3) * x.y);
	p.a2 = 6 * (ft_pow(ray->dir.x, 2) * ft_pow(x.x, 2) + 2 * ft_pow(ray->dir.y,
		2) * ft_pow(x.y, 2)) - 5 * (vec3_dot(ray->dir, ray->dir));
	p.a1 = 4 * (ft_pow(x.x, 3) * ray->dir.x + ft_pow(x.y, 3) * ray->dir.y * 2) -
		10 * (ray->dir.x * x.x + 2 * ray->dir.y * x.y);
	p.a0 = ft_pow(x.x, 4) + ft_pow(x.y, 4) + ft_pow(x.z, 4) - 5 * (vec3_dot(x, x));
	gsl_poly_complex_workspace *w =  gsl_poly_complex_workspace_alloc(5);
	gsl_poly_complex_solve(a, 5, w, roots);
	gsl_poly_complex_workspace_free(w);
	return (choose_root(p, ret));
}
