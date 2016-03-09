/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 09:29:31 by scollon           #+#    #+#             */
/*   Updated: 2016/03/09 09:38:32 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

t_lgt		*create_light(t_env *e, char *type)
{
	char	*line;
	t_lgt	*current;

	if (!(current = (t_lgt *)malloc(sizeof(t_lgt))))
		error(E_MALLOC, NULL, 1);
	default_light(current);
	while (get_next_line(e->arg.fd, &line) > 0 && ft_strlen(line) > 1)
	{
		get_light_type(current, type);
		if (ft_strstr(line, "pos: "))
			current->pos = parse_vector(line);
		else if (ft_strstr(line, "dir: "))
			current->dir = parse_vector(line);
		else if (ft_strstr(line, "color: "))
			current->color = hex_vec3(ft_atoi_base(ft_strstr(line, "0x"), 16));
		else if (ft_strstr(line, "intensity: "))
			current->intensity = ft_atof(ft_strstr(line, ":") + 1);
		else
			error(E_LPARAM, line, 0);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	current->next = NULL;
	return (current);
}
