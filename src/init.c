/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 14:46:31 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/11 15:17:20 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init(t_env *e)
{
	e->intersect[0] = intersect_sphere;
	e->intersect[1] = intersect_cone;
	e->intersect[2] = intersect_plane;
	e->intersect[3] = intersect_cylinder;
}
