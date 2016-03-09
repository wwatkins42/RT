/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 09:29:14 by scollon           #+#    #+#             */
/*   Updated: 2016/03/09 10:01:26 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// static void	parse_material(t_obj *current)
// {
//
// }

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

t_obj		*create_object(t_env *e, char *type)
{
	char	*line;
	t_obj	*current;

	if (!(current = (t_obj*)malloc(sizeof(t_obj))))
		error(E_MALLOC, NULL, 1);
	//default_object(current);
	while (get_next_line(e->arg.fd, &line) > 0 && ft_strlen(line) > 1)
	{
		get_object_type(current, type);
		if (ft_strstr(line, "pos: "))
			current->pos = parse_vector(line);
		else if (ft_strstr(line, "dir: "))
			current->dir = parse_vector(line);
		else if (ft_strstr(line, "scale: "))
			current->scale = ft_atof(ft_strstr(line, ":") + 1);
		//else if (ft_strstr(line, "material:"))
		//	parse_material(current);
		//else
		//	error(E_OPARAM, line, 0);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	current->next = NULL;
	return (current);
}
