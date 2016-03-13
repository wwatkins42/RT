/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 09:29:14 by scollon           #+#    #+#             */
/*   Updated: 2016/03/13 14:58:36 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	default_object(t_obj *obj)
{
	obj->type = SPHERE;
	obj->pos = vec3_zero();
	obj->dir = vec3_zero();
	obj->scale = 1;
	obj->mat.color = vec3(1, 1, 1);
	obj->mat.ambient = 0.025;
	obj->mat.diffuse = 0.975;
	obj->mat.specular = 1.0;
	obj->mat.shininess = 256;
	obj->mat.reflect = 0;
	obj->mat.refract = 0;
	obj->mat.transparency = 0;
	obj->mat.absorbtion = 0;
}

static void	parse_material(t_env *e, t_obj *obj)
{
	char	*line;

	while (get_next_line(e->arg.fd, &line) > 0 && !ft_strstr(line, "---"))
	{
		if (ft_strcmp(line, "...") == 0)
			break ;
		if (ft_strstr(line, "color: "))
			obj->mat.color = hex_vec3(ft_atoi_base(ft_strstr(line, "0x"), 16));
		else if (ft_strstr(line, "ambient: "))
			obj->mat.ambient = ft_atof(ft_strstr(line, ":") + 1);
		else if (ft_strstr(line, "diffuse: "))
			obj->mat.diffuse = ft_atof(ft_strstr(line, ":") + 1);
		else if (ft_strstr(line, "specular: "))
			obj->mat.specular = ft_atof(ft_strstr(line, ":") + 1);
		else if (ft_strstr(line, "shininess: "))
			obj->mat.shininess = ft_atof(ft_strstr(line, ":") + 1);
		else if (ft_strstr(line, "reflect: "))
			obj->mat.reflect = ft_atof(ft_strstr(line, ":") + 1);
		else if (ft_strstr(line, "refract: "))
			obj->mat.refract = ft_atof(ft_strstr(line, ":") + 1);
		else if (ft_strstr(line, "transparency: "))
			obj->mat.transparency = ft_atof(ft_strstr(line, ":") + 1);
		else if (ft_strstr(line, "absorbtion: "))
			obj->mat.absorbtion = ft_atof(ft_strstr(line, ":") + 1);
		else
			error(E_OPARAM, line, 0);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

static void	get_object_type(t_obj *current, char *type)
{
	if (ft_strstr(type, "SPHERE"))
		current->type = SPHERE;
	else if (ft_strstr(type, "CONE"))
		current->type = CONE;
	else if (ft_strstr(type, "PLANE"))
		current->type = PLANE;
	else if (ft_strstr(type, "CYLINDER"))
		current->type = CYLINDER;
	else
		error(E_OTYPE, type, 0);
}

void		create_object(t_env *e, t_obj *obj, char *type)
{
	char	*line;

	default_object(obj);
	get_object_type(obj, type);
	while (get_next_line(e->arg.fd, &line) > 0 && !ft_strstr(line, "---"))
	{
		if (ft_strstr(line, "material:"))
			break ;
		if (ft_strstr(line, "pos: "))
			obj->pos = parse_vector(line);
		else if (ft_strstr(line, "dir: "))
			obj->dir = parse_vector(line);
		else if (ft_strstr(line, "scale: "))
			obj->scale = ft_atof(ft_strstr(line, ":") + 1);
		else
			error(E_OPARAM, line, 0);
		ft_strdel(&line);
	}
	parse_material(e, obj);
	ft_strdel(&line);
	obj->next = NULL;
}

void		parse_objects(t_env *e, char *str)
{
	int		i;
	char	*line;
	t_obj	*current;

	(i = ft_atoi(ft_strstr(str, ":") + 1)) == 0 ? error(E_OINIT, NULL, 1) : 0;
	!(current = (t_obj*)malloc(sizeof(t_obj))) ? error(E_MALLOC, NULL, 1) : 0;
	e->obj = current;
	while (i > 0 && get_next_line(e->arg.fd, &line) > 0)
	{
		if (ft_strstr(line, "- type:"))
		{
			i--;
			create_object(e, current, line);
			if (i > 0)
				if (!(current->next = (t_obj*)malloc(sizeof(t_obj))))
					error(E_MALLOC, NULL, 1);
			current = current->next;
		}
		ft_strdel(&line);
	}
	current = e->obj;
	ft_strdel(&line);
}
