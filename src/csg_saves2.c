/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg_saves2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 09:26:39 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/27 09:26:47 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double    save_lin_rin(t_ray *r, t_obj *left, t_obj *right, t_obj *dad)
{
    r->hit = vec3_add(r->pos, vec3_fmul(r->dir, left->in));
    set_normal(r, left);
    dad->normal = left->normal;
    dad->mat = left->mat;
	dad->in = left->in;
	dad->out = right->in;
    return (left->in);
}

double    save_nothan(t_obj *dad)
{
	dad->in = INFINITY;
	dad->out = INFINITY;
    return (INFINITY);
}
