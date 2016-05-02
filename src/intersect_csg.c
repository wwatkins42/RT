/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_csg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 22:22:04 by tbeauman          #+#    #+#             */
/*   Updated: 2016/05/02 19:42:39 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		do_union(t_env *e, t_ray *r, t_obj *dad)
{
	if ((dad->left->in == INFINITY || dad->left->in < EPSILON) &&
		(dad->right->in == INFINITY || dad->right->in < EPSILON))
		return (save_nothan(dad));
	if (dad->left->in < dad->right->in)
	{
		if (dad->left->out > dad->right->out)
			return (save_lin_lout(e, r, dad));
		else
			return (save_lin_rout(e, r, dad));
	}
	else if (dad->left->in < dad->right->out
		&& dad->right->out < dad->left->out)
		return (save_rin_lout(e, r, dad));
	else
		return (save_rin_rout(e, r, dad));
}

double		do_inter(t_env *e, t_ray *r, t_obj *dad)
{
	if (dad->left->in == INFINITY || dad->left->in < EPSILON ||
		dad->right->in == INFINITY || dad->right->in < EPSILON)
		return (INFINITY);
	if (dad->left->in < dad->right->in)
	{
		if (dad->left->out < dad->right->in)
			return (save_nothan(dad));
		if (dad->left->out < dad->right->out)
			return (save_rin_lout(e, r, dad));
		else
			return (save_rin_rout(e, r, dad));
	}
	else
	{
		if (dad->right->out < dad->left->in)
			return (save_nothan(dad));
		if (dad->right->out < dad->left->out)
			return (save_lin_rout(e, r, dad));
		else
			return (save_lin_lout(e, r, dad));
	}
}

double		do_diff(t_env *e, t_ray *r, t_obj *dad)
{
	if (dad->left->in == INFINITY || dad->left->in < EPSILON)
		return (save_nothan(dad));
	if (dad->right->in == INFINITY || dad->right->in < EPSILON)
		return (save_lin_lout(e, r, dad));
	else if (dad->left->in > dad->right->in)
	{
		if (dad->left->in > dad->right->out)
			return (save_lin_lout(e, r, dad));
		else if (dad->left->out < dad->right->out)
			return (save_nothan(dad));
		else
			return (save_rout_lout(e, r, dad));
	}
	else if (dad->left->out < dad->right->in)
		return (save_lin_lout(e, r, dad));
	else if (dad->left->out < dad->right->out)
		return (save_lin_rin(e, r, dad));
	else
		return (save_lin_lout(e, r, dad));
}

double		do_op(t_env *e, t_ray *r, t_obj *dad)
{
	if (dad->op == UNION)
		return (do_union(e, r, dad));
	else if (dad->op == INTER)
		return (do_inter(e, r, dad));
	else
		return (do_diff(e, r, dad));
}

double		intersect_csg(t_env *e, t_ray *r, t_obj *dad)
{
	t_ray	*tray;

	if (dad->left && dad->right && ((tray = r) || 1))
	{
		if (dad->left->type != CSG && dad->left->type != CUBE)
			transform_ray_for_csg(tray, dad->left, dad);
		dad->left->type == CSG ? intersect_csg(e, r, dad->left)
			: e->intersect[dad->left->type](r, dad->left);
		tray = r;
		if (dad->left->type != CSG && dad->left->type != CUBE)
			transform_ray_for_csg(tray, dad->right, dad);
		dad->right->type == CSG ? intersect_csg(e, r, dad->right)
			: e->intersect[dad->right->type](r, dad->right);
		dad->in = INFINITY;
		dad->out = INFINITY;
		dad->t = do_op(e, r, dad);
		return (dad->t);
	}
	return (INFINITY);
}
