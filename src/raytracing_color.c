/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 14:28:29 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/11 14:40:12 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	raytracing_color(t_env *e, t_ray ray, t_obj *obj)
{
	t_lgt	*light;
	t_vec3	color;
	t_vec3	diffuse;
	t_vec3	specular;

	color = (t_vec3) {0, 0, 0};
	light = e->light;
	while ((light = light->next) != NULL)
	{
		color = vec3_fmul(light->color, obj->mat.ambient);
		diffuse = set_diffuse(e, obj, light);
		specular = set_specular(e, obj, light);
		color = vec3_add(color, vec3_add(diffuse, specular));
	}
	return (color);
}
