/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:09:33 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/07 18:22:53 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse(t_env *e)
{
	char	*line;

	if ((e->arg.fd = open(e->arg.file, O_RDWR)) == -1)
		error(strerror(errno), NULL, 1);
	ft_strdel(&e->arg.file);
	while (get_next_line(e->arg.fd, &line) > 0 && ft_strcmp(line, "..."))
	{
		if (ft_strstr(line, "cameras:"))
			parse_camera(e, line);
		//else if (!ft_strcmp(line, "lights:"))
		//	parse_lights(e, line);
		//else if (!ft_strcmp(line, "objects:"))
		//	parse_objects(e, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

void	parse_camera(t_env *e, char *str)
{
	int		i;
	char	*line;
	t_cam	*current;

	(i = ft_atoi(ft_strstr(str, ":") + 1)) == 0 ? error(E_CAM_INIT, 0, 1) : 0;
	if ((e->cam = (t_cam*)malloc(sizeof(t_cam))) == NULL)
		error(E_MALLOC, NULL, 1);
	current = NULL;
	e->cam->next = current;
	while (get_next_line(e->arg.fd, &line) > 0 && i >= 0)
	{
		if (ft_strstr(line, "- camera:"))
		{
			current = create_camera(e);
			current->index = ft_atof(ft_strstr(line, ":") + 1);
			current = current->next;
		}
		ft_strdel(&line);
		i--;
	}
	ft_strdel(&line);
}

/*void	parse_lights(t_env *e, char *str)
{
	int		i;
	char	*line;
	t_lgt	*current;

	(i = ft_atoi(ft_strstr(str, ":") + 1) == 0 ? error(E_OBJ_INIT, 0, 1) : 0);
	if ((e->lgt = (t_lgt*)malloc(sizeof(t_lgt))) == NULL)
		error(E_MALLOC, NULL, 1);
	current = NULL;
	e->lgt->next = current;
	while (get_next_line(e->arg.fd, &line) > 0 && i >= 0)
	{
		if (ft_strstr(line, "- type:"))
		{
			current = create_light(e);
			current = current->next;
		}
		ft_strdel(&line);
		i--;
	}
	ft_strdel(&line);
}*/

t_vec3	parse_vector(const char *line)
{
	t_vec3	vec3;

	vec3 = (t_vec3) { 0, 0, 0 };
	vec3.x = ft_atof(ft_strstr(line, "x:") + 2);
	vec3.y = ft_atof(ft_strstr(line, "y:") + 2);
	vec3.z = ft_atof(ft_strstr(line, "z:") + 2);
	vec3_clamp(&vec3, MIN_POS, MAX_POS);
	return (vec3);
}
