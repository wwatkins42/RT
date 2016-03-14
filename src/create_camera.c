/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:19:08 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/14 07:56:35 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	default_camera(t_env *e, t_cam *current)
{
	if (current != NULL)
	{
		current->pos = vec3_zero();
		current->dir = vec3(0, 0, 0);
		current->index = 0;
		current->fov = 60;
		current->img = img_init(e, e->win.w, e->win.h);
	}
}

static void	create_camera(t_env *e, t_cam *cam, t_cam *prev)
{
	char	*line;

	default_camera(e, cam);
	while (get_next_line(e->arg.fd, &line) > 0 && !ft_strstr(line, "---"))
	{
		if (ft_strstr(line, "pos: "))
			cam->pos = parse_vector(line);
		else if (ft_strstr(line, "dir: "))
			cam->dir = parse_vector(line);
		else if (ft_strstr(line, "fov: "))
			cam->fov = ft_atof(ft_strstr(line, ":") + 1);
		else if (ft_strstr(line, "background: "))
			parse_gradient(cam, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	cam->prev = prev;
	cam->next = NULL;
	e->cam->prev = cam;
}

void		parse_camera(t_env *e, char *str)
{
	int		i;
	char	*line;
	t_cam	*current;
	t_cam	*prev;

	prev = NULL;
	(i = ft_atoi(ft_strstr(str, ":") + 1)) == 0 ? error(E_CINIT, 0, 1) : 0;
	!(current = (t_cam*)malloc(sizeof(t_cam))) ? error(E_MALLOC, NULL, 1) : 0;
	e->cam = current;
	while (i > 0 && get_next_line(e->arg.fd, &line) > 0)
	{
		if (ft_strstr(line, "- camera:"))
		{
			i--;
			create_camera(e, current, prev);
			current->index = ft_atof(ft_strstr(line, ":") + 1);
			prev = current;
			if (i > 0)
				current->next = (t_cam*)malloc(sizeof(t_cam));
			current = current->next;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	e->cam->prev->next = e->cam;
}
