/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:19:08 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/10 11:29:21 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	default_camera(t_env *e, t_cam *current)
{
	if (current != NULL)
	{
		current->pos = vec3_zero();
		current->dir = vec3(0, 0, 1);
		current->rot = vec3_zero();
		current->index = 0;
		current->fov = 60;
		current->img = img_init(e);
	}
}

void		parse_camera(t_env *e, char *str)
{
	int		i;
	char	*line;
	t_cam	*current;
	t_cam	*prev;

	(i = ft_atoi(ft_strstr(str, ":") + 1)) == 0 ? error(E_CINIT, 0, 1) : 0;
	if ((e->cam = (t_cam*)malloc(sizeof(t_cam))) == NULL)
		error(E_MALLOC, NULL, 1);
	current = NULL;
	prev = NULL;
	e->cam->next = current;
	while (i > 0 && get_next_line(e->arg.fd, &line) > 0)
	{
		if (ft_strstr(line, "- camera:"))
		{
			i--;
			current = create_camera(e, prev);
			current->index = ft_atof(ft_strstr(line, ":") + 1);
			prev = current;
			current = current->next;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

t_cam		*create_camera(t_env *e, t_cam *prev)
{
	char	*line;
	t_cam	*current;

	if (!(current = (t_cam*)malloc(sizeof(t_cam))))
		error(E_MALLOC, NULL, 1);
	default_camera(e, current);
	while (get_next_line(e->arg.fd, &line) > 0 && !ft_strstr(line, "---"))
	{
		if (ft_strstr(line, "pos: "))
			current->pos = parse_vector(line);
		else if (ft_strstr(line, "dir: "))
			current->dir = parse_vector(line);
		else if (ft_strstr(line, "fov: "))
			current->fov = ft_atof(ft_strstr(line, ":") + 1);
		else if (ft_strstr(line, "background: "))
			parse_gradient(e, line);
		ft_strdel(&line);
	}
	printf("pos: %f, %f, %f\n", current->pos.x, current->pos.y, current->pos.z);
	printf("dir: %f, %f, %f\n", current->dir.x, current->dir.y, current->dir.z);
	printf("fov: %f\n\n", current->fov);
	ft_strdel(&line);
	current->prev = prev;
	current->next = NULL;
	return (current);
}
