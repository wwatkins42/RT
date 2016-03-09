/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:09:33 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/09 09:19:59 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse(t_env *e)
{
	char	*line;

	if ((e->arg.fd = open(e->arg.file, O_RDWR)) == -1)
		error(strerror(errno), NULL, 1);
	ft_strdel(&e->arg.file);
	while (get_next_line(e->arg.fd, &line) > 0 && ft_strcmp(line, "...") != 0)
	{
		if (ft_strstr(line, "cameras:"))
			parse_camera(e, line);
		else if (ft_strstr(line, "lights:"))
			parse_lights(e, line);
		else if (ft_strstr(line, "objects:"))
			parse_objects(e, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

void	parse_camera(t_env *e, char *str)
{
	int		i;
	char	*line;
	t_cam	*current;

	(i = ft_atoi(ft_strstr(str, ":") + 1)) == 0 ? error(E_CINIT, 0, 1) : 0;
	if ((e->cam = (t_cam*)malloc(sizeof(t_cam))) == NULL)
		error(E_MALLOC, NULL, 1);
	current = NULL;
	e->cam->next = current;
	while (i > 0 && get_next_line(e->arg.fd, &line) > 0)
	{
		if (ft_strstr(line, "- camera:"))
		{
			i--;
			current = create_camera(e);
			current->index = ft_atof(ft_strstr(line, ":") + 1);
			current = current->next;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

void	parse_lights(t_env *e, char *str)
{
	int		i;
	char	*line;
	t_lgt	*current;

	(i = ft_atoi(ft_strstr(str, ":") + 1)) == 0 ? error(E_LINIT, NULL, 1) : 0;
	if ((e->lgt = (t_lgt*)malloc(sizeof(t_lgt))) == NULL)
		error(E_MALLOC, NULL, 1);
	current = NULL;
	e->lgt->next = current;
	while (i > 0 && get_next_line(e->arg.fd, &line) > 0)
	{
		if (ft_strstr(line, "- type:"))
		{
			current = create_light(e, line);
			current = current->next;
		}
		ft_strdel(&line);
		i--;
	}
	ft_strdel(&line);
}

void	parse_objects(t_env *e, char *str)
{
	int		i;
	char	*line;
	t_obj	*current;

	(i = ft_atoi(ft_strstr(str, ":") + 1)) == 0 ? error(E_OINIT, NULL, 1) : 0;o
	if ((e->obj = (t_obj*)malloc(sizeof(t_obj))))
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
