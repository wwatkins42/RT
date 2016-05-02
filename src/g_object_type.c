/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_object_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 11:41:44 by scollon           #+#    #+#             */
/*   Updated: 2016/05/01 12:06:04 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

const t_gobj_type		g_object_type[20] =
{
	{ SPHERE, "SPHERE" },
	{ CONE, "CONE" },
	{ PLANE, "PLANE" },
	{ CYLINDER, "CYLINDER" },
	{ TRIANGLE, "TRIANGLE" },
	{ CHEWINGGUM, "CHEWINGGUM" },
	{ CUBE_TROUE, "CUBE_TROUE" },
	{ CUBE, "CUBE" },
	{ PARALLELOGRAM, "PARALLELOGRAM" },
	{ HYPERBOLOID_ONE, "HYPERBOLOID_ONE" },
	{ HYPERBOLOID_TWO, "HYPERBOLOID_TWO" },
	{ PARABOLOID, "PARABOLOID" },
	{ TORUS, "TORUS" },
	{ QUADRIC, "QUADRIC" },
	{ MOEBIUS, "MOEBIUS" },
	{ DISC, "DISC" },
	{ DISC, "DISC" },
	{ CSG, "CSG" },
	{ BBOX, "OBJ" },
	{ -1, NULL }
};
