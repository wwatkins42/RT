/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:09:33 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/07 16:17:12 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse(t_env *e)
{
	char	*line;

	while (get_next_line(e->arg.fd, &line) > 0 && !ft_strcmp(line, "..."))
	{
		if (!ft_strcmp(line, "cameras:"))
			parse_camera(e, line);
		//else if (!ft_strcmp(line, "lights:"))
		//	parse_lights(e, line);
		//else if (!ft_strcmp(line, "objects:"))
		//	parse_objects(e, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

void	parse_camera(t_env *e, const char *str)
{
	int		i;
	char	*line;
	t_cam	*current;
	t_cam	*prev;

	(i = ft_atoi(ft_strstr(str, ":") + 1)) == 0 ? error(E_CAM_INIT, 0, 1) : 0;
	if ((e->cam = (t_cam*)malloc(sizeof(t_cam))) == NULL)
		error(E_MALLOC, NULL, 1);
	current = NULL;
	e->cam->next = current;
	while (get_next_line(e->arg.fd, &line) > 0 && i > 0)
	{
		if (ft_strstr(line, "- camera:"))
		{
			current = create_camera(e);
			current->index = ft_atof(ft_strstr(line, ":") + 1);
			prev = current;
			current = current->next;
			current->prev = prev;
		}
		ft_strdel(&line);
		i--;
	}
	ft_strdel(&line);
}

t_vec3	parse_vector(const char *line)
{
	int		i;
	int		n;
	char	**split;
	t_vec3	vec3;

	i = 0;
	n = 0;
	vec3 = (t_vec3) { 0, 0, 0 };
	split = ft_strsplit(line, ' ');
	while (split[i] != NULL && n != 3)
	{
		str_digit(split[i]) == 1 ? n++ : 0;
		n == 1 ? vec3.x = ft_atof(split[i]) : 0;
		n == 2 ? vec3.y = ft_atof(split[i]) : 0;
		n == 3 ? vec3.z = ft_atof(split[i]) : 0;
		ft_strdel(&split[i]);
		i++;
	}
	ft_strdel(&split[i]);
	free(split);
	vec3_clamp(&vec3, MIN_POS, MAX_POS);
	return (vec3);
}
