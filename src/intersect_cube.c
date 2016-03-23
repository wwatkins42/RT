/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cube.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 02:52:56 by tbeauman          #+#    #+#             */
/*   Updated: 2016/03/23 07:28:22 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		intersect_cube(t_ray *ray, t_obj *cube)
{
	int		i;
	double	tmin;
	double	t;

	i = 0;
	tmin = INFINITY;
	while (i < 6)
	{
		t = intersect_parallelogramme(ray, &cube->comp[i]);
		if (t > EPSILON && t < tmin)
		{
			cube->comp_hit = i;
			tmin = t;
		}
		i++;
	}
	return (tmin);
}
