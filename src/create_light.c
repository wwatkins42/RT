/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 09:29:31 by scollon           #+#    #+#             */
/*   Updated: 2016/03/09 11:37:55 by wwatkins         ###   ########.fr       */
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

void		parse_lights(t_env *e, char *str)
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
			i--;
			current = create_light(e, line);
			current = current->next;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

t_lgt		*create_light(t_env *e, char *type)
{
	char	*line;
	t_lgt	*current;

	if (!(current = (t_lgt *)malloc(sizeof(t_lgt))))
		error(E_MALLOC, NULL, 1);
	default_light(current);
	get_light_type(current, type);
	while (get_next_line(e->arg.fd, &line) > 0 && !ft_strstr(line, "---"))
	{
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
