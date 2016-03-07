/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:34:54 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/07 18:22:20 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cam	*create_camera(t_env *e)
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
