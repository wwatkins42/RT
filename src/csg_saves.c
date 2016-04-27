/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg_saves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 09:26:16 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/27 09:26:24 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double    save_lin_lout(t_ray *r, t_obj *left, t_obj *right, t_obj *dad)
{
	(void)right;
    r->hit = vec3_add(r->pos, vec3_fmul(r->dir, left->in));
    set_normal(r, left);
    dad->normal = left->normal;
    dad->mat = left->mat;
	dad->in = left->in;
	dad->out = left->out;
    return (left->in);
}

double    save_lin_rout(t_ray *r, t_obj *left, t_obj *right, t_obj *dad)
{
	r->hit = vec3_add(r->pos, vec3_fmul(r->dir, left->in));
	set_normal(r, left);
	dad->normal = left->normal;
	dad->mat = left->mat;
	dad->in = left->in;
	dad->out = right->out;
	return (left->in);
}

double    save_rin_lout(t_ray *r, t_obj *left, t_obj *right, t_obj *dad)
{
    r->hit = vec3_add(r->pos, vec3_fmul(r->dir, right->in));
    set_normal(r, right);
    dad->normal = right->normal;
    dad->mat = right->mat;
	dad->in = right->in;
	dad->out = left->out;
    return (right->in);
}

double    save_rin_rout(t_ray *r, t_obj *left, t_obj *right, t_obj *dad)
{
	(void)left;
    r->hit = vec3_add(r->pos, vec3_fmul(r->dir, right->in));
    set_normal(r, right);
    dad->normal = right->normal;
    dad->mat = right->mat;
	dad->in = right->in;
	dad->out = right->out;
    return (right->in);
}

double    save_rout_lout(t_ray *r, t_obj *left, t_obj *right, t_obj *dad)
{
    r->hit = vec3_add(r->pos, vec3_fmul(r->dir, right->out));
    set_normal(r, right);
    dad->normal = vec3_fmul(right->normal, -1);
    dad->mat = right->mat;
	dad->in = right->out;
	dad->out = left->out;
    return (right->out);
}
