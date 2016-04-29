/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_csg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 13:40:42 by scollon           #+#    #+#             */
/*   Updated: 2016/04/29 14:54:40 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_obj	*create_object_for_csg(t_env *e, t_line *object_line)
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
		else if (ft_strstr(line->line, "pos2:"))
			new->pos2 = parse_vector(ft_strchr(line->line, ':'));
		else if (ft_strstr(line->line, "pos3:"))
			new->pos3 = parse_vector(ft_strchr(line->line, ':'));
		else if (ft_strstr(line->line, "dir:"))
			new->dir = parse_vector(line->line);
		else if (ft_strstr(line->line, "scale:"))
			new->scale = parse_value(line->line, 0.1, 1000);
		else if (ft_strstr(line->line, "min:"))
			new->min = ft_atof(ft_strstr(line->line, ":") + 1);
		else if (ft_strstr(line->line, "max:"))
			new->max = ft_atof(ft_strstr(line->line, ":") + 1);
		else if (ft_strstr(line->line, "pr:"))
			new->pr = ft_atof(ft_strstr(line->line, ":") + 1);
		else if (ft_strstr(line->line, "gr:"))
			new->gr = ft_atof(ft_strstr(line->line, ":") + 1);
		else if (ft_strstr(line->line, "material:"))
			parse_material(e, &new->mat, line);
		line = line->next;
	}
	new->mat.texture.normal_map && new->mat.texture.defined ? create_normal_map(new) : 0;
	new->pr *= new->pr;
	new->gr *= new->gr;
	new->scale2 = new->scale * new->scale;
	new->k = tan(new->scale) * tan(new->scale);
	if (new->type == TRIANGLE || new->type == PARALLELOGRAM)
		new->dir = vec3_norm(vec3_cross(new->pos2, new->pos3));
	if (new->type == CUBE)
		create_cube(new);
	(new->type != BBOX && new->type != CUBE) ? new->comp = NULL : 0;
	// if (new->type == QUADRIC)
	// 	test(new);
	if (new->type == CSG)
		parse_csg(e, new, line);
	return (new);
}

void parse_csg(t_env *e, t_obj *csg, t_line *line)
{
	int		count_parenthesis;

	count_parenthesis = 1;
	while (line && !ft_strchr(line->line, '('))
		line = line->prev;
	line = line->next;
	while (line && count_parenthesis)
	{
		if (count_parenthesis == 1)
		{
			if (ft_strstr(line->line, "- object:"))
			{
				if (csg->left)
				{
					if (csg->right)
						error(E_OTYPE, line->line, 0);
					else
						csg->right = create_object_for_csg(e, line->next);
				}
				else
					csg->left = create_object_for_csg(e, line->next);
			}
			if (ft_strstr(line->line, "- op:"))
			{
				if (ft_strstr(line->line, "UNION"))
					csg->op = UNION;
				else if (ft_strstr(line->line, "DIFF"))
					csg->op = DIFF;
				else if (ft_strstr(line->line, "INTER"))
					csg->op = INTER;
			}
		}
		if (ft_strchr(line->line, '('))
			count_parenthesis++;
		else if (ft_strchr(line->line, ')'))
			count_parenthesis--;
		line = line->next;
	}
}
