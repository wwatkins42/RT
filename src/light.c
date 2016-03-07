/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 17:27:55 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/07 17:31:52 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_lgt	*create_light(t_env *e)
{
	char	*line;
	t_lgt	*current;

	if (!(current = (t_lgt*)malloc(sizeof(t_lgt))))
		error(E_MALLOC, NULL, 1);
	while (get_next_line(e->arg.fd, &line) > 0 && line[0] != '\n')
	{
		if (ft_strstr(line, "pos: "))
			current->pos = parse_vector(line);
		if (ft_strstr(line, "color: "))
			current->color = ft_atoi_base(ft_strstr(line, ":") + 1, 16);
		if (ft_strstr(line, "intensity: "))
			current->intensity = ft_atof(ft_strstr(line, ":") + 1);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	current->prev = NULL;
	current->next = NULL;
	return (current);
}
