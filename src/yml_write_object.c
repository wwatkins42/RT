/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yml_write_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/30 09:45:39 by scollon           #+#    #+#             */
/*   Updated: 2016/05/03 13:44:17 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	*get_type(const int type)
{
	int		i;

	i = -1;
	while (g_object_type[++i].reference != NULL)
	{
		if (type == g_object_type[i].index)
			return (g_object_type[i].reference);
	}
	return ("SPHERE");
}

static void	export_material(const int fd, t_obj *obj)
{
	ft_printf_fd(fd, "    color: %#x\n", vec3_hex(obj->mat.color));
	ft_printf_fd(fd, "    ambient: %f\n", obj->mat.ambient);
	ft_printf_fd(fd, "    diffuse: %f\n", obj->mat.diffuse);
	ft_printf_fd(fd, "    specular: %f\n", obj->mat.specular);
	ft_printf_fd(fd, "    shininess: %f\n", obj->mat.shininess);
	ft_printf_fd(fd, "    reflect: %f\n", obj->mat.reflect);
	ft_printf_fd(fd, "    refract: %f\n", obj->mat.refract);
	ft_printf_fd(fd, "    transparency: %f\n", obj->mat.transparency);
	ft_printf_fd(fd, "    absorbtion: %f\n", obj->mat.absorbtion);
	if (obj->mat.texture.defined)
		ft_printf_fd(fd, "    texture: %s\n", obj->mat.texture.name);
	ft_printf_fd(fd, "    texture_filtering: %s\n",
							ft_boolean(obj->mat.texture.filtering));
	ft_printf_fd(fd, "    texture_normal: %s\n",
							ft_boolean(obj->mat.texture.normal_map));
	ft_printf_fd(fd, "    texture_normal_strength: %f\n",
							obj->mat.texture.normal_strength);
	ft_printf_fd(fd, "    texture_size: %f\n", obj->mat.texture.scale);
	ft_printf_fd(fd, "    texture_rotation: %f\n", obj->mat.texture.rotation);
	ft_printf_fd(fd, "    receive_shadow: %s\n",
							ft_boolean(obj->mat.receive_shadow));
	ft_printf_fd(fd, "    normal_perturbation: %s\n",
							ft_boolean(obj->mat.normal_perturbation));
}

void		export_object(const int fd, t_env *e)
{
	t_obj *obj;

	obj = e->obj;
	write(fd, "objects:\n", 9);
	while (obj != NULL)
	{
		ft_printf_fd(fd, "- object:\n");
		ft_printf_fd(fd, "  type: %s\n", get_type(obj->type));
		ft_printf_fd(fd, "  scale: %f\n", obj->scale);
		ft_printf_fd(fd, "  pos: {x: %f, y: %f, z: %f}\n",
					obj->pos.x, obj->pos.y, obj->pos.z);
		ft_printf_fd(fd, "  dir: {x: %f, y: %f, z: %f}\n",
					obj->dir.x, obj->dir.y, obj->dir.z);
		write(fd, "  material:\n", 12);
		export_material(fd, obj);
		write(fd, "\n", 1);
		obj = obj->next;
	}
}
