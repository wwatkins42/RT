/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tbeauman_ellipsoid_intersect.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 19:06:43 by tbeauman          #+#    #+#             */
/*   Updated: 2016/03/17 19:29:52 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

typedef struct		s_cal
{
	double			a1;
	double			a2;
	double			a;
	double			b;
	double			c;
	double			d;
}					t_cal;

double	intersect_ellipsoid(t_ray *r, t_obj *e) //NO GOOD YET
{
	t_cal	c;
	double	tmp;

	c.a1 = 2 * e->scale * vec3_dot(r->dir, e->dir);
	c.a2 = e->scale2 * e->scale2 + 2 * e->scale *
		vec3_dot(vec3_sub(r->pos, e->pos), e->dir) - e->scale;
	c.a = 4 * e->scale2 * e->scale2 *
		vec3_dot(r->dir, r->dir) - c.a1 * c.a1;
	c.b = 2 * (4 * e->scale2 * e->scale2 *
		vec3_dot(r->dir, vec3_sub(r->pos, e->pos))) - c.a1 * c.a2;
	c.c = 4 * e->scale2 * e->scale2 * vec3_dot(
		vec3_sub(r->pos, e->pos), vec3_sub(r->pos, e->pos)) - c.a2 * c.a2;
	c.d = c.b * c.b - 4 * c.a * c.c;
	if (c.d < 0)
		return (INFINITY);
	else
	{
		tmp = (-c.b - sqrt(c.d)) / (2 * c.a);
		if (tmp < 0)
				return (INFINITY);
		return (tmp);
	}

}
