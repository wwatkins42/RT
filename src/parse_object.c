/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 14:52:10 by scollon           #+#    #+#             */
/*   Updated: 2016/04/29 13:54:18 by scollon          ###   ########.fr       */
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

t_obj			*parse_object(t_env *e, t_line *object_line)
{
	t_line	*line;
	t_obj	*tmp;
	t_obj	*object;
	t_obj	*current;

	line = object_line;
	if (!(current = (t_obj*)malloc(sizeof(t_obj))))
		error(E_MALLOC, NULL, 1);
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
	tmp = object;
	object = object->next;
	ft_memdel((void**)&tmp);
	return (object);
}
