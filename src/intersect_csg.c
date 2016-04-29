/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_csg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 22:22:04 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/29 14:11:32 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double (*intersect[20])(t_ray *, t_obj *) =
{ intersect_sphere, intersect_cone, intersect_plane, intersect_cylinder,
intersect_triangle, intersect_cube, intersect_parallelogram, intersect_hyperboloid1,
intersect_hyperboloid2, intersect_paraboloid, intersect_torus, intersect_chewing_gum, intersect_quadric,
intersect_moebius, intersect_disc, intersect_csg, intersects_bbox };

double		do_union(t_ray *r, t_obj *left, t_obj *right, t_obj *dad)
{
	if ((left->in == INFINITY || left->in < EPSILON) &&
		(right->in == INFINITY || right->in < EPSILON))
		return (save_nothan(dad));
	if (left->in < right->in)
	{
		if (left->out > right->out)
			return (save_lin_lout(r, left, right, dad));
		else
			return (save_lin_rout(r, left, right, dad));
	}
	else if (left->in < right->out && right->out < left->out)
		return (save_rin_lout(r, left, right, dad));
	else
		return (save_rin_rout(r, left, right, dad));
}

double		do_inter(t_ray *r, t_obj *left, t_obj *right, t_obj *dad)
{
	if (left->in == INFINITY || left->in < EPSILON ||
		right->in == INFINITY || right->in < EPSILON)
		return (INFINITY);
	if (left->in < right->in)
	{
		if (left->out < right->in)
			return (save_nothan(dad));
		if (left->out < right->out)
			return (save_rin_lout(r, left, right, dad));
		else
			return (save_rin_rout(r, left, right, dad));
	}
	else
	{
		if (right->out < left->in)
			return (save_nothan(dad));
		if (right->out < left->out)
			return (save_lin_rout(r, left, right, dad));
		else
			return (save_lin_lout(r, left, right, dad));
	}

}

double		do_diff(t_ray *r, t_obj *left, t_obj *right, t_obj *dad)
{
	if (left->in == INFINITY || left->in < EPSILON)
		return (save_nothan(dad));
	if (right->in == INFINITY || right->in < EPSILON)
		return (save_lin_lout(r, left, right, dad));
	else if (left->in > right->in)
	{
		if (left->in > right->out)
			return (save_lin_lout(r, left, right, dad));
		else if (left->out < right->out)
			return (save_nothan(dad));
		else
			return (save_rout_lout(r, left, right, dad));
	}
	else if (left->out < right->in)
		return (save_lin_lout(r, left, right, dad));
	else if (left->out < right->out)
		return (save_lin_rin(r, left, right, dad));
	else
		return (save_lin_lout(r, left, right, dad));

}

double    do_op(t_ray *r, t_obj *left, t_obj *right, t_obj *dad)
{
    if (dad->op == UNION)
		return (do_union(r, left, right, dad));
    else if (dad->op == INTER)
		return (do_inter(r, left, right, dad));
    else
		return (do_diff(r, left, right, dad));
}

double    intersect_csg(t_ray *r, t_obj *dad)
{
    if (dad->left && dad->right)
    {
        intersect[dad->left->type](r, dad->left);
        intersect[dad->right->type](r, dad->right);
		dad->in = INFINITY;
		dad->out = INFINITY;
        dad->t = do_op(r, dad->left, dad->right, dad);
	    return (dad->t);
    }
	return (INFINITY);
}
