/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 17:08:14 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/15 17:11:40 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	texture_mapping_sphere(t_vec3 hit, t_obj *obj)
{
	t_vec3	d;
	double	u;
	double	v;
	int		i;
	int		j;

	if (!obj->mat.texture.defined)
		return (obj->mat.color);
	else
	{
		d = vec3_sub(hit, obj->pos);
		u = 0.5 + atan2(d.z, d.x) / (2.0 * M_PI);
		v = 0.5 - asin(d.y) / M_PI;
		i = (u * obj->mat.texture.w);
		j = (v * obj->mat.texture.h);
		return (obj->mat.texture.img[j][i]);
	}
}
