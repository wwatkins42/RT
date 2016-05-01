/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cube.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 02:52:56 by tbeauman          #+#    #+#             */
/*   Updated: 2016/05/01 19:23:44 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		intersect_cube(t_ray *ray, t_obj *cube)
{
	int		i;
	int		lol;
	double	ts[4];
	t_ray	tray;

	i = 0;
	lol = 0;
	ts[0] = INFINITY;
	ts[1] = INFINITY;
	ts[2] = INFINITY;
	cube->in = INFINITY;
	cube->out = INFINITY;
	while (i < 6)
	{
		tray = *ray;
		tray.pos = vec3_sub(ray->pos, cube->comp[i].pos);
		vec3_inverse_rotate(&tray.pos, cube->rot);
		vec3_inverse_rotate(&tray.dir, cube->rot);
		ts[3] = intersect_parallelogram(&tray, &cube->comp[i]);
		if (ts[3] > EPSILON && ts[3] != INFINITY && ((ts[lol] = ts[3]) || 1))
		{
			lol = 1;
			if (ts[3] < ts[2] && ((cube->comp_hit = i) || 1))
				ts[2] = ts[3];
		}
		i++;
	}
	cube->in = ts[0] < ts[1] ? ts[0] : ts[1];
	cube->out = ts[0] < ts[1] ? ts[1] : ts[0];
	return (ts[2]);
}
