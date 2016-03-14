/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 09:29:31 by scollon           #+#    #+#             */
/*   Updated: 2016/03/14 07:56:54 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	default_light(t_lgt *current)
{
	if (current != NULL)
	{
		current->type = POINT;
		current->pos = vec3_zero();
		current->color = vec3(1, 1, 1);
		current->intensity = 1.0;
	}
}

static void	get_light_type(t_lgt *current, char *line)
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

static void	get_shadow_type(t_lgt *current, char *line)
{
	if (ft_strstr(line, "HARD"))
		current->type = POINT;
	else if (ft_strstr(line, "SOFT"))
		current->type = SPOT;
	else
		error(E_STYPE, line, 0);
}

static void	create_light(t_env *e, t_lgt *lgt, char *type)
{
	char	*line;

	default_light(lgt);
	get_light_type(lgt, type);
	while (get_next_line(e->arg.fd, &line) > 0 && !ft_strstr(line, "---"))
	{
		if (ft_strstr(line, "pos: "))
			lgt->pos = parse_vector(line);
		else if (ft_strstr(line, "dir: "))
			lgt->dir = parse_vector(line);
		else if (ft_strstr(line, "color: "))
			lgt->color = hex_vec3(ft_atoi_base(ft_strstr(line, "0x"), 16));
		else if (ft_strstr(line, "intensity: "))
			lgt->intensity = ft_atof(ft_strstr(line, ":") + 1);
		else if (ft_strstr(line, "shadow: "))
			get_shadow_type(lgt, line);
		else
			error(E_LPARAM, line, 0);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	lgt->next = NULL;
}

void		parse_lights(t_env *e, char *str)
{
	int		i;
	char	*line;
	t_lgt	*current;

	(i = ft_atoi(ft_strstr(str, ":") + 1)) == 0 ? error(E_LINIT, NULL, 1) : 0;
	!(current = (t_lgt*)malloc(sizeof(t_lgt))) ? error(E_MALLOC, NULL, 1) : 0;
	e->lgt = current;
	while (i > 0 && get_next_line(e->arg.fd, &line) > 0)
	{
		if (ft_strstr(line, "- type:"))
		{
			i--;
			create_light(e, current, line);
			if (i > 0)
				if (!(current->next = (t_lgt*)malloc(sizeof(t_lgt))))
					error(E_MALLOC, NULL, 1);
			current = current->next;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
}
