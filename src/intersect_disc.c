/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_disc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 21:52:12 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/29 18:01:56 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	intersect_disc(t_ray *r, t_obj *t)
{
	t_calc	c;

	if ((c.eq = intersect_plane(r, t)) == INFINITY)
		return (INFINITY);
	r->hit = vec3_add(r->pos, vec3_fmul(r->dir, c.eq));
	if (vec3_magnitude(vec3_sub(r->hit, t->pos)) > t->scale)
		return (INFINITY);
	return (c.eq);
}
