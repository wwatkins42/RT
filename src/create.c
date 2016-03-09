/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:34:54 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/09 09:24:38 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cam		*create_camera(t_env *e)
{
	char	*line;
	t_cam	*current;

	if (!(current = (t_cam*)malloc(sizeof(t_cam))))
		error(E_MALLOC, NULL, 1);
	default_camera(current);
	while (get_next_line(e->arg.fd, &line) > 0 && ft_strlen(line) > 1)
	{
		if (ft_strstr(line, "pos: "))
			current->pos = parse_vector(line);
		else if (ft_strstr(line, "dir: "))
			current->dir = parse_vector(line);
		else if (ft_strstr(line, "fov: "))
			current->fov = ft_atof(ft_strstr(line, ":") + 1);
		//if (ft_strstr(line, "background: "))
		//	current->gradient = parse_gradient(line);
		ft_strdel(&line);
	}
	printf("pos: %f, %f, %f\n", current->pos.x, current->pos.y, current->pos.z);
	ft_strdel(&line);
	current->prev = NULL;
	current->next = NULL;
	return (current);
}

static void	get_light_type(t_lgt *current, const char *line)
{
	if (ft_strstr(line, "POINT"))
		current->type = POINT;
	else if (ft_strstr(line, "SPOT"))
		current->type = SPOT;
	else if (ft_strstr(line, "DIRECTIONAL"))
		current->type = DIRECTIONAL;
	else
		error(E_LTYPE, line, 0);
}

t_lgt		*create_light(t_env *e, char *type)
{
	char	*line;
	t_lgt	*current;

	if (!(current = (t_lgt *)malloc(sizeof(t_lgt))))
		error(E_MALLOC, NULL, 1);
	default_light(current);
	while (get_next_line(e->arg.fd, &line) > 0 && ft_strlen(line) > 1)
	{
		get_light_type(current, type);
		if (ft_strstr(line, "pos: "))
			current->pos = parse_vector(line);
		else if (ft_strstr(line, "dir: "))
			current->dir = parse_vector(line);
		else if (ft_strstr(line, "color: "))
			current->color = hex_vec3(ft_atoi_base(ft_strstr(line, "0x"), 16));
		else if (ft_strstr(line, "intensity: "))
			current->intensity = ft_atof(ft_strstr(line, ":") + 1);
		else
			error(E_LPARAM, line, 0);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	current->next = NULL;
	return (current);
}

t_obj		*create_object(t_env *e, char *type)
{
	char	*line;
	t_obj	*current;

	if (!(current = t_lgt *)malloc(sizeof(t_lgt)))
		error(E_MALLOC, NULL, 1);
	default_object(current);
	while (get_next_line(e->arg.fd, &line) > 0 && ft_strlen(line) > 1)
	{
		get_object_type(type);
		if (ft_strstr(line, "pos: "))
			current->pos = parse_vector(line);
		else if (ft_strstr(line, "dir: "))
			current->dir = parse_vector(line);
		else if (ft_strstr(line, "color: "))
			current->color = hex_vec3(ft_atoi_base(ft_strstr(line, "0x"), 16));
		
	}
}
