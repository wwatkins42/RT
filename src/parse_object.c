/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 14:52:10 by scollon           #+#    #+#             */
/*   Updated: 2016/04/29 15:02:43 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// static void test(t_obj *quad)
// {
// 	quad->co.a = 1;
// 	quad->co.b = 1;
// 	quad->co.c = 1;
// 	quad->co.d = 0;
// 	quad->co.e = 0;
// 	quad->co.f = 0;
// 	quad->co.g = 0;
// 	quad->co.h = 0;
// 	quad->co.i = 0;
// 	quad->co.j = -5;
// }

static void		do_not_parse_csg_as_classical_objects(t_line **line)
{
	int			count_parenthesis;

	if (ft_strchr((*line)->line, '('))
	{
		count_parenthesis = 1;
		while (count_parenthesis)
		{
			*line = (*line)->next;
			if (!*line)
				error(E_IFILE, (*line)->line, 1);
			if (ft_strchr((*line)->line, ')'))
				count_parenthesis--;
			if (ft_strchr((*line)->line, '('))
				count_parenthesis++;
		}
	}
}

t_obj			*parse_object(t_env *e, t_line *object_line)
{
	t_line	*line;
	t_obj	*tmp;
	t_obj	*object;
	t_obj	*current;

	line = object_line;
	if (!(current = (t_obj*)malloc(sizeof(t_obj))))
		error(E_MALLOC, NULL, 1);
	current->next = NULL;
	object = current;
	while (line != NULL)
	{
		do_not_parse_csg_as_classical_objects(&line);
		if (ft_strstr(line->line, "- object:"))
		{
			current->next = create_object(e, line->next);
			current = current->next;
		}
		line = line->next;
	}
	tmp = object;
	object = object->next;
	ft_memdel((void**)&tmp);
	return (object);
}
