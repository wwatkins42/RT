/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:34:54 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/08 10:06:52 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cam		*create_camera(t_env *e)
{
	char	*line;
	t_cam	*current;

	if (!(current = (t_cam*)malloc(sizeof(t_cam))))
		error(E_MALLOC, NULL, 1);
	while (get_next_line(e->arg.fd, &line) > 0 && ft_strlen(line) > 1)
	{
		if (ft_strstr(line, "pos: "))
			current->pos = parse_vector(line);
		if (ft_strstr(line, "dir: "))
			current->dir = parse_vector(line);
		if (ft_strstr(line, "fov: "))
			current->fov = ft_atof(ft_strstr(line, ":") + 1);
		//if (ft_strstr(line, "background: "))
		//	current->gradient = parse_gradient(line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	current->prev = NULL;
	current->next = NULL;
	printf("camera\n");
	printf("pos: (%f, %f, %f)\n", current->pos.x, current->pos.y, current->pos.z);
	printf("dir: (%f, %f, %f)\n", current->dir.x, current->dir.y, current->dir.z);
	printf("fov: %f\n\n", current->fov);
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
}

t_lgt		*create_light(t_env *e)
{
	char	*line;
	t_lgt	*current;

	if (!(current = (t_lgt *)malloc(sizeof(t_lgt))))
		error(E_MALLOC, NULL, 1);
	while (get_next_line(e->arg.fd, &line) > 0 && ft_strlen(line) > 1)
	{
		if (ft_strstr(line, "- type: "))
			get_light_type(current, line);
		if (ft_strstr(line, "pos: "))
			current->pos = parse_vector(line);
		if (ft_strstr(line, "dir: "))
			current->dir = parse_vector(line);
		if (ft_strstr(line, "color: "))
			current->color = hex_to_vec3(ft_atoi_base(ft_strstr(line, "0x"), 16));
		if (ft_strstr(line, "intesity: "))
			current->intensity = ft_atof(ft_strstr(line, ":") + 1);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	current->next = NULL;
	printf("light\n");
	printf("pos: (%f, %f, %f)\n", current->pos.x, current->pos.y, current->pos.z);
	printf("clr: (%f, %f, %f)\n", current->color.x, current->color.y, current->color.z);
	printf("int: %f\n\n", current->intensity);
	return (current);
}
