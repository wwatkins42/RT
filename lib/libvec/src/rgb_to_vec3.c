/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_vec3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/30 10:11:09 by scollon           #+#    #+#             */
/*   Updated: 2016/04/30 11:04:50 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

t_vec3		rgb_to_vec3(t_rgb rgb)
{
	t_vec3	v;

	v.x = (double)rgb.x / 255;
	v.y = (double)rgb.y / 255;
	v.z = (double)rgb.z / 255;
	return (v);
}

t_rgb		vec3_to_rgb(t_vec3	v)
{
	t_rgb rgb;

	rgb.x = (unsigned char)(v.x * 255);
	rgb.y = (unsigned char)(v.y * 255);
	rgb.z = (unsigned char)(v.z * 255);
	return (rgb);
}
