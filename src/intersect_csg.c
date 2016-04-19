/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_csg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 22:22:04 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/19 23:35:47 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	do_op(int op, t_obj *obj1, t_obj *obj2)
{
	if (op == UNION)
	{
		if (obj1->in == INFINITY && obj2->in == INFINITY)
			return (INFINITY);
		if (obj1->in < obj2->in)
			return (obj1->in);
		else
			return (obj2->in);
	}
	if (op == DIFF)
		return (hit2 )
}

double	intersect_csg(t_ray *r, t_obj *t)
{
	if (!t->left)

}
