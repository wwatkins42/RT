/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresnel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 18:30:35 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/24 18:50:50 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	get_fresnel(t_vec3 v, t_vec3 n, double ir)
{
	double	base;
	double	exponential;

	base = 1.0 - vec3_dot(v, n);
	exponential = powf(base, 5);
	return (ir + exponential * (1.0 - exponential));
}

void	set_fresnel(t_obj *obj)
{
	obj->mat.fresnel.reflect = pow((obj->mat.refract - 1.0) /
		(obj->mat.refract + 1.0), 2);
	obj->mat.fresnel.refract = 1.0 - obj->mat.fresnel.reflect;
}
