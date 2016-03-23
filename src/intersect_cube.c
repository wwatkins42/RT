/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cube.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 02:52:56 by tbeauman          #+#    #+#             */
/*   Updated: 2016/03/23 10:36:12 by wwatkins         ###   ########.fr       */
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
		t = intersect_parallelogram(ray, &cube->comp[i]);
		if (t > EPSILON && t < tmin)
		{
			cube->comp_hit = i;
			tmin = t;
		}
		i++;
	}
	return (tmin);
}
