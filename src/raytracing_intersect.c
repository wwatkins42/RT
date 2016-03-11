/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_intersect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 14:42:27 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/11 14:57:34 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"



t_obj	*ray_intersect(t_env *e, t_ray ray, double *tmin, double *t)
{
	t_obj	*obj;
	t_obj	*out;

	obj = e->obj;
	while ((obj = obj->next) != NULL)
	{
		*t = e->intersect[obj->type](e, ray, obj);
		if (*t > EPSILON && *t < *tmin)
		{
			out = obj;
			*tmin = *t;
		}
	}
	return (out);
}
