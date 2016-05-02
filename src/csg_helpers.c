/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 09:26:16 by tbeauman          #+#    #+#             */
/*   Updated: 2016/05/02 11:20:13 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	save_lin_lout(t_env *e, t_ray *r, t_obj *dad)
{
	r->hit = vec3_add(r->pos, vec3_fmul(r->dir, dad->left->in));
	set_normal(e, r, dad->left);
	dad->normal = dad->left->normal;
	dad->mat = dad->left->mat;
	dad->in = dad->left->in;
	dad->out = dad->left->out;
	return (dad->left->in);
}

double	save_lin_rout(t_env *e, t_ray *r, t_obj *dad)
{
	r->hit = vec3_add(r->pos, vec3_fmul(r->dir, dad->left->in));
	set_normal(e, r, dad->left);
	dad->normal = dad->left->normal;
	dad->mat = dad->left->mat;
	dad->in = dad->left->in;
	dad->out = dad->right->out;
	return (dad->left->in);
}

double	save_rin_lout(t_env *e, t_ray *r, t_obj *dad)
{
	r->hit = vec3_add(r->pos, vec3_fmul(r->dir, dad->right->in));
	set_normal(e, r, dad->right);
	dad->normal = dad->right->normal;
	dad->mat = dad->right->mat;
	dad->in = dad->right->in;
	dad->out = dad->left->out;
	return (dad->right->in);
}

double	save_rin_rout(t_env *e, t_ray *r, t_obj *dad)
{
	r->hit = vec3_add(r->pos, vec3_fmul(r->dir, dad->right->in));
	set_normal(e, r, dad->right);
	dad->normal = dad->right->normal;
	dad->mat = dad->right->mat;
	dad->in = dad->right->in;
	dad->out = dad->right->out;
	return (dad->right->in);
}

double	save_rout_lout(t_env *e, t_ray *r, t_obj *dad)
{
	r->hit = vec3_add(r->pos, vec3_fmul(r->dir, dad->right->out));
	set_normal(e, r, dad->right);
	dad->normal = vec3_fmul(dad->right->normal, -1);
	dad->mat = dad->right->mat;
	dad->in = dad->right->out;
	dad->out = dad->left->out;
	return (dad->right->out);
}
