/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_roots.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 19:16:26 by tbeauman          #+#    #+#             */
/*   Updated: 2016/04/30 11:03:34 by tbeauman         ###   ########.fr       */
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

double			choose_root2(double *roots, int ret)
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
