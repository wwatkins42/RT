/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_basics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 09:23:04 by tbeauman          #+#    #+#             */
/*   Updated: 2016/05/02 11:27:22 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	plane_normal(t_vec3 *hit, t_obj *obj)
{
	(void)hit;
	return (obj->dir);
}

t_vec3	sphere_normal(t_vec3 *hit, t_obj *obj)
{
	(void)obj;
	return (*hit);
}

t_vec3	cylinder_normal(t_vec3 *hit, t_obj *obj)
{
	t_vec3	ret;

	ret = *hit;
	ret = vec3_sub(ret, vec3_fmul(obj->dir, obj->m));
	return (ret);
}

t_vec3	cone_normal(t_vec3 *hit, t_obj *obj)
{
	t_vec3	ret;

	ret = *hit;
	ret = vec3_sub(ret, vec3_fmul(obj->dir,
		(1 + obj->k) * obj->m));
	return (ret);
}
