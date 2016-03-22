/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 11:49:00 by scollon           #+#    #+#             */
/*   Updated: 2016/03/22 08:41:39 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3		parse_color(char *line)
{
	t_vec3	color;

	color = (t_vec3) {0, 0, 0};
	while (*line != '#' && ft_strncmp(line, "0x", 2) != 0)
		line++;
	color = hex_vec3(ft_atoi_base(line, 16));
	return (color);
}

double		parse_value(const char *line)
{
	int			i;
	double		value;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	(line[i - 1] == '-') ? i -= 1 : 0;
	value = ft_atof(&line[i]);
	return (value);
}

t_vec3		parse_vector(const char *line)
{
	int		i;
	char	**tab;
	t_vec3	vec;

	i = -1;
	vec = (t_vec3) {0, 0, 0};
	!(tab = ft_strsplit(line, ',')) ? error(E_MALLOC, NULL, 1) : 0;
	while (tab[++i] != NULL)
	{
		if (ft_strstr(tab[i], "x:"))
			vec.x = parse_value(tab[i]);
		else if (ft_strstr(tab[i], "y:"))
			vec.y = parse_value(tab[i]);
		else if (ft_strstr(tab[i], "z:"))
			vec.z = parse_value(tab[i]);
		ft_strdel(&tab[i]);
	}
	ft_memdel((void**)tab);
	return (vec);
}
