/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 11:34:53 by scollon           #+#    #+#             */
/*   Updated: 2016/03/28 10:04:25 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		default_cam(t_env *e, t_cam *cam)
{
	if (cam != NULL)
	{
		cam->pos = vec3_zero();
		cam->dir = vec3(0, 0, 1);
		cam->index = 0;
		cam->fov = 60;
		cam->img = img_init(e);
		cam->filter.invert = 0;
		cam->filter.gray_scale = 0;
		cam->filter.gamma = 1.0;
		cam->aa.supersampling = 1;
	}
}

static t_cam	*create_cam(t_env *e, t_line *cam_line, t_cam *prev)
{
	t_cam		*new;
	t_line		*line;

	line = cam_line;
	!(new = (t_cam*)malloc(sizeof(t_cam))) ? error(E_CINIT, NULL, 1) : 0;
	default_cam(e, new);
	while (line != NULL && !ft_strstr(line->line, "- camera:"))
	{
		if (ft_strstr(line->line, "pos:"))
			new->pos = parse_vector(line->line);
		else if (ft_strstr(line->line, "dir:"))
			new->dir = parse_vector(line->line);
		else if (ft_strstr(line->line, "fov:"))
			new->fov = parse_value(line->line, 1, 180);
		else if (ft_strstr(line->line, "supersampling:"))
			new->aa.supersampling = parse_value(line->line, 1, 16);
		line = line->next;
	}
	e->count.cam++;
	new->prev = prev;
	new->next = NULL;
	return (new);
}

t_cam			*parse_camera(t_env *e, t_line *cam_line)
{
	t_line	*line;
	t_cam	*tmp;
	t_cam	*camera;
	t_cam	*current;

	line = cam_line;
	if (!(current = (t_cam*)malloc(sizeof(t_cam))))
		error(E_MALLOC, NULL, 1);
	current->next = NULL;
	camera = current;
	while (line != NULL)
	{
		if (ft_strstr(line->line, "- camera:"))
		{
			current->next = create_cam(e, line->next, current);
			current = current->next;
			camera->next->prev = current;
			current->next = camera->next;
		}
		line = line->next;
	}
	tmp = camera;
	camera = camera->next;
	ft_memdel((void**)&tmp);
	return (camera);
}
