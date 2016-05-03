/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 13:54:26 by scollon           #+#    #+#             */
/*   Updated: 2016/05/03 15:53:44 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int				get_object_type(t_env *e, char *line)
{
	int		i;
	char	*type;

	i = -1;
	if (!(type = ft_strtrim(ft_strchr(line, ':') + 1)))
		error(e, E_MALLOC, NULL, 1);
	while (g_object_type[++i].reference != NULL)
	{
		if (ft_strcmp(type, g_object_type[i].reference) == 0)
		{
			ft_strdel(&type);
			return (g_object_type[i].index);
		}
	}
	error(e, E_OTYPE, type, 0);
	ft_strdel(&type);
	return (SPHERE);
}

static void		fill_object_attr2(t_env *e, t_line *line, t_obj *new)
{
	if (ft_strstr(line->line, "scale:"))
		new->scale = parse_value(line->line, 0.01, 1000);
	else if (ft_strstr(line->line, "min:"))
		new->min = parse_value(line->line, -INFINITY, INFINITY);
	else if (ft_strstr(line->line, "max:"))
		new->max = parse_value(line->line, -INFINITY, INFINITY);
	else if (ft_strstr(line->line, "pr:"))
		new->pr = parse_value(line->line, 0, INFINITY);
	else if (ft_strstr(line->line, "gr:"))
		new->gr = parse_value(line->line, 0, INFINITY);
	else if (ft_strstr(line->line, "material:"))
		parse_material(e, &new->mat, line);
	else if (ft_strstr(line->line, "obj:"))
		new = parse_obj(ft_strstr(line->line, ":") + 1, e, new);
}

int				fill_object_attr(t_env *e, t_line *line, t_obj *new)
{
	if (ft_strstr(line->line, "type:"))
		new->type = get_object_type(e, line->line);
	else if (ft_strstr(line->line, "pos:"))
		new->pos = parse_vector(e, line->line);
	else if (ft_strstr(line->line, "pos2:"))
		new->pos2 = parse_vector(e, ft_strchr(line->line, ':'));
	else if (ft_strstr(line->line, "pos3:"))
		new->pos3 = parse_vector(e, ft_strchr(line->line, ':'));
	else if (ft_strstr(line->line, "rot:"))
		new->rot = parse_vector(e, ft_strchr(line->line, ':'));
	else if (ft_strstr(line->line, "dir:"))
		new->dir = vec3_norm(parse_vector(e, line->line));
	else if (ft_strstr(line->line, "cut:"))
		new->cut = parse_vector(e, line->line);
	else
		fill_object_attr2(e, line, new);
	return (1);
}

t_obj			*create_object(t_env *e, t_line *object_line)
{
	t_obj		*new;
	t_line		*line;

	line = object_line;
	!(new = (t_obj*)malloc(sizeof(t_obj))) ? error(e, E_OINIT, NULL, 1) : 0;
	default_object(new);
	while (line != NULL && !ft_strstr(line->line, "- object:") &&
		!ft_strchr(line->line, '('))
	{
		fill_object_attr(e, line, new);
		line = line->next;
	}
	e->count.obj++;
	new->id = e->count.obj;
	if (new->mat.texture.normal_map && new->mat.texture.defined)
		create_normal_map(e, new);
	new->scale2 = new->scale * new->scale;
	new->pr *= new->pr;
	new->gr *= new->gr;
	new->k = tan(new->scale) * tan(new->scale);
	if (new->type == TRIANGLE || new->type == PARALLELOGRAM)
		new->dir = vec3_norm(vec3_cross(new->pos2, new->pos3));
	new->type == CUBE ? create_cube(e, new) : 0;
	new->type == CSG ? parse_csg(e, new, line) : 0;
	(new->type != BBOX && new->type != CUBE) ? new->comp = NULL : 0;
	new->mat.fresnel.defined ? set_fresnel(new) : 0;
	return (new);
}
