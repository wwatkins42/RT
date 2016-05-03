/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 18:37:50 by tbeauman          #+#    #+#             */
/*   Updated: 2016/05/03 11:56:32 by tbeauman         ###   ########.fr       */
=======
/*   By: aacuna <aacuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 18:37:50 by tbeauman          #+#    #+#             */
/*   Updated: 2016/05/03 11:28:25 by aacuna           ###   ########.fr       */
>>>>>>> f47f6ba5572afb1dbce48104cfb3391e56c0c189
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_mat	default_material(void)
{
	t_mat	mat;

	mat.color = vec3(1, 1, 1);
	mat.ambient = 0.225;
	mat.diffuse = 0.875;
	mat.specular = 1.0;
	mat.shininess = 256;
	mat.glossiness = 0;
	mat.reflect = 0;
	mat.refract = 0;
	mat.transparency = 0;
	mat.absorbtion = 0;
	mat.texture.defined = 0;
	mat.texture.transparency_mapping = 0;
	mat.texture.filtering = 0;
	mat.texture.normal_map = 0;
	mat.texture.normal_strength = 2;
	mat.texture.scale = 1;
	mat.texture.rotation = 0;
	mat.receive_shadow = 1;
	mat.fresnel.defined = 0;
	mat.normal_perturbation = 0;
	return (mat);
}

void			default_object(t_obj *object)
{
	object->type = SPHERE;
	object->pos = vec3(0, 0, 0);
	object->pos2 = vec3(0, 1, 0);
	object->pos3 = vec3(1, 0, 0);
	object->dir = vec3(0, 1, 0);
	object->cut = vec3(0, 0, 0);
	object->rot = vec3(0, 0, 0);
	object->m = 1;
	object->pr = 1;
	object->gr = 2;
	object->min = -INFINITY;
	object->max = INFINITY;
	object->scale = 1;
	object->mat = default_material();
	object->comp = NULL;
	object->next = NULL;
	object->left = NULL;
	object->right = NULL;
}
