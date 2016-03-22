/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 14:52:10 by scollon           #+#    #+#             */
/*   Updated: 2016/03/22 10:47:14 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		default_object(t_obj *object)
{
	object->type = SPHERE;
	object->pos = vec3(0, 0, 5);
	object->dir = vec3(0, 0, 1);
	object->scale = 1;
	object->mat.color = vec3(1, 1, 1);
	object->mat.ambient = 0.225;
	object->mat.diffuse = 0.875;
	object->mat.specular = 1.0;
	object->mat.shininess = 256;
	object->mat.reflect = 0;
	object->mat.refract = 0;
	object->mat.transparency = 0;
	object->mat.absorbtion = 0;
	object->mat.texture.defined = 0;
	object->mat.texture.filtering = 0;
	object->mat.texture.normal_map = 0;
	object->mat.shadow = 1;
}

static int		get_object_type(char *line)
{
	if (ft_strstr(line, "SPHERE"))
		return (SPHERE);
	else if (ft_strstr(line, "CONE"))
		return (CONE);
	else if (ft_strstr(line, "PLANE"))
		return (PLANE);
	else if (ft_strstr(line, "CYLINDER"))
		return (CYLINDER);
	else
		error(E_OTYPE, line, 0);
	return (SPHERE);
}

static t_obj	*create_object(t_env *e, t_line *object_line)
{
	t_obj		*new;
	t_line		*line;

	line = object_line;
	!(new = (t_obj*)malloc(sizeof(t_obj))) ? error(E_OINIT, NULL, 1) : 0;
	default_object(new);
	while (line != NULL && !ft_strstr(line->line, "- object:"))
	{
		if (ft_strstr(line->line, "type:"))
			new->type = get_object_type(line->line);
		else if (ft_strstr(line->line, "pos:"))
			new->pos = parse_vector(line->line);
		else if (ft_strstr(line->line, "dir:"))
			new->dir = parse_vector(line->line);
		else if (ft_strstr(line->line, "scale:"))
			new->scale = parse_value(line->line, 0.1, 1000);
		else if (ft_strstr(line->line, "material:"))
			parse_material(e, &new->mat, line);
		line = line->next;
	}
	e->count.obj++;
	new->mat.texture.normal_map ? create_normal_map(new) : 0;
	new->scale2 = new->scale * new->scale;
	new->k = tan(new->scale) * tan(new->scale);
	new->next = NULL;
	return (new);
}

t_obj			*parse_object(t_env *e, t_line *object_line)
{
	t_line	*line;
	t_obj	*object;
	t_obj	*current;

	line = object_line->next->next;
	current = NULL;
	current = create_object(e, line);
	object = current;
	while (line != NULL)
	{
		if (ft_strstr(line->line, "- object:"))
		{
			current->next = create_object(e, line->next);
			current = current->next;
		}
		line = line->next;
	}
	return (object);
}
