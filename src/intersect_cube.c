/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cube.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 02:52:56 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/28 11:26:30 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		intersect_cube(t_ray *ray, t_obj *cube)
{
	int		i;
	int		lol;
	double	tmin;
	double	ts[2] = {INFINITY, INFINITY};
	double	t;

	i = 0;
	lol = 0;
	tmin = INFINITY;
	cube->in = INFINITY;
	cube->out = INFINITY;
	while (i < 6)
	{
		t = intersect_parallelogram(ray, &cube->comp[i]);
		if (t > EPSILON && t != INFINITY && ((ts[lol] = t) || 1))
		{
			lol = 1;
			if (t < tmin && ((cube->comp_hit = i) || 1))
				tmin = t;
		}
		i++;
	}
	cube->in = ts[0] < ts[1] ? ts[0] : ts[1];
	cube->out = ts[0] < ts[1] ? ts[1] : ts[0];
	return (tmin);
}
