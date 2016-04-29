/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_roots.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 19:16:26 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/29 19:16:52 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			choose_root4(double *roots, int ret)
{
	int		i;

	i = 0;
	while (i < ret)
	{
		if (roots[i] > EPSILON)
			return (roots[i]);
		i++;
	}
	return (INFINITY);
}

double			choose_root3(double *roots, int ret)
{
	if (ret == 1)
		return (roots[0] < 0 ? INFINITY : roots[0]);
	ret = 0;
	while (ret < 3)
	{
		if (roots[ret] > 0)
			return (roots[ret]);
		ret++;
	}
	return (INFINITY);
}
