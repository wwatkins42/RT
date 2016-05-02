/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_csg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 13:40:42 by scollon           #+#    #+#             */
/*   Updated: 2016/05/01 11:24:11 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_obj	*create_object_for_csg(t_env *e, t_line *object_line)
{
	t_obj		*new;
	t_line		*line;

	line = object_line;
	!(new = (t_obj*)malloc(sizeof(t_obj))) ? error(e, E_OINIT, NULL, 1) : 0;
	default_object(new);
	while (line != NULL && !ft_strstr(line->line, "- object:"))
	{
		fill_object_attr(e, line, new);
		line = line->next;
	}
	if (new->mat.texture.normal_map && new->mat.texture.defined)
		create_normal_map(e, new);
	new->pr *= new->pr;
	new->gr *= new->gr;
	new->scale2 = new->scale * new->scale;
	new->k = tan(new->scale) * tan(new->scale);
	if (new->type == TRIANGLE || new->type == PARALLELOGRAM)
		new->dir = vec3_norm(vec3_cross(new->pos2, new->pos3));
	if (new->type == CUBE)
		create_cube(e, new);
	(new->type != BBOX && new->type != CUBE) ? new->comp = NULL : 0;
	if (new->type == CSG)
		parse_csg(e, new, line);
	return (new);
}

static void		parse_fistons(t_env *e, t_obj *csg, t_line *line)
{
	if (ft_strstr(line->line, "- object:"))
	{
		if (csg->left)
		{
			if (csg->right)
				error(e, E_OTYPE, line->line, 0);
			else
				csg->right = create_object_for_csg(e, line->next);
		}
		else
			csg->left = create_object_for_csg(e, line->next);
	}
}

static void		parse_op(t_env *e, t_obj *csg, char *line)
{
	if (ft_strstr(line, "- op:"))
	{
		if (ft_strstr(line, "UNION"))
			csg->op = UNION;
		else if (ft_strstr(line, "DIFF"))
			csg->op = DIFF;
		else if (ft_strstr(line, "INTER"))
			csg->op = INTER;
		else
			error(e, E_OPARAM, line, 0);
	}
}

void			parse_csg(t_env *e, t_obj *csg, t_line *line)
{
	int			count_parenthesis;

	count_parenthesis = 1;
	while (line && !ft_strchr(line->line, '('))
		line = line->prev;
	line = line->next;
	while (line && count_parenthesis)
	{
		if (count_parenthesis == 1)
		{
			parse_fistons(e, csg, line);
			parse_op(e, csg, line->line);
		}
		if (ft_strchr(line->line, '('))
			count_parenthesis++;
		else if (ft_strchr(line->line, ')'))
			count_parenthesis--;
		line = line->next;
	}
}
