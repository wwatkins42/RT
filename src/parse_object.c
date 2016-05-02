/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 14:52:10 by scollon           #+#    #+#             */
/*   Updated: 2016/05/02 10:14:39 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		do_not_parse_csg_as_classical_objects(t_env *e, t_line **line)
{
	int			count_parenthesis;

	if (ft_strchr((*line)->line, '('))
	{
		count_parenthesis = 1;
		while (count_parenthesis)
		{
			*line = (*line)->next;
			if (!*line)
				error(e, E_IFILE, (*line)->line, 1);
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
		error(e, E_MALLOC, NULL, 1);
	current->next = NULL;
	object = current;
	while (line != NULL)
	{
		do_not_parse_csg_as_classical_objects(e, &line);
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
