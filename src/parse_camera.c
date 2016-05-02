/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 11:34:53 by scollon           #+#    #+#             */
/*   Updated: 2016/05/01 11:16:56 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		default_cam(t_env *e, t_cam *cam)
{
	if (cam != NULL)
	{
		cam->type = DEFAULT;
		cam->pos = vec3_zero();
		cam->dir = vec3(0, 0, 1);
		cam->index = 0;
		cam->fov = 60;
		cam->img = img_init(e);
		cam->filter.invert = 0;
		cam->filter.gray_scale = 0;
		cam->filter.gamma = 1.0;
		cam->aa.supersampling = 1;
		cam->selection = NULL;
		cam->twin = NULL;
	}
}

static void		create_stereoscopic_twin(t_env *e, t_cam *new)
{
	t_cam	*twin;

	!(twin = (t_cam*)malloc(sizeof(t_cam))) ? error(e, E_CINIT, NULL, 1) : 0;
	twin->type = STEREOSCOPIC;
	twin->dir = new->dir;
	twin->fov = new->fov;
	twin->img = img_init(e);
	twin->filter.invert = 0;
	twin->filter.gray_scale = 0;
	twin->filter.gamma = 1.0;
	twin->aa.supersampling = new->aa.supersampling;
	twin->next = NULL;
	twin->prev = NULL;
	twin->twin = new;
	new->twin = twin;
}

static t_cam	*create_cam(t_env *e, t_line *cam_line, t_cam *prev)
{
	t_cam		*new;
	t_line		*line;

	line = cam_line;
	!(new = (t_cam*)malloc(sizeof(t_cam))) ? error(e, E_CINIT, NULL, 1) : 0;
	default_cam(e, new);
	while (line != NULL && !ft_strstr(line->line, "- camera:"))
	{
		if (ft_strstr(line->line, "type:") && ft_strstr(line->line, "STEREO"))
			new->type = STEREOSCOPIC;
		else if (ft_strstr(line->line, "pos:"))
			new->pos = parse_vector(e, line->line);
		else if (ft_strstr(line->line, "dir:"))
			new->dir = parse_vector(e, line->line);
		else if (ft_strstr(line->line, "fov:"))
			new->fov = parse_value(line->line, 1, 180);
		else if (ft_strstr(line->line, "supersampling:"))
			new->aa.supersampling = parse_value(line->line, 1, 16);
		line = line->next;
	}
	e->count.cam++;
	new->type == STEREOSCOPIC ? create_stereoscopic_twin(e, new) : 0;
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
		error(e, E_MALLOC, NULL, 1);
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
