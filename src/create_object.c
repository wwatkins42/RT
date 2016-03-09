/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 09:29:14 by scollon           #+#    #+#             */
/*   Updated: 2016/03/09 10:51:38 by wwatkins         ###   ########.fr       */
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

void	parse_objects(t_env *e, char *str)
{
	int		i;
	char	*line;
	t_obj	*current;

	(i = ft_atoi(ft_strstr(str, ":") + 1)) == 0 ? error(E_OINIT, NULL, 1) : 0;
	if (!(e->obj = (t_obj*)malloc(sizeof(t_obj))))
		error(E_MALLOC, NULL, 1);
	current = NULL;
	e->obj->next = current;
	while (i > 0 && get_next_line(e->arg.fd, &line) > 0)
	{
		if (ft_strstr(line, "- type:"))
		{
			current = create_object(e, line);
			current = current->next;
		}
		ft_strdel(&line);
		i--;
	}
	ft_strdel(&line);
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
