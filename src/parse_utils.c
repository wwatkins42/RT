/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 11:49:00 by scollon           #+#    #+#             */
/*   Updated: 2016/03/25 07:46:25 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			is_comment(const char *line)
{
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == '	')
		i++;
	return (line[i] == '#' ? 1 : 0);
}

t_vec3		parse_color(char *line)
{
	t_vec3	color;

	color = (t_vec3) {0, 0, 0};
	while (*line != '#' && ft_strncmp(line, "0x", 2) != 0)
		line++;
	color = hex_vec3(ft_atoi_base(line, 16));
	return (color);
}

short		parse_boolean(const char *line)
{
	if (ft_strstr(line, "true") || ft_strstr(line, "TRUE"))
		return (1);
	if (ft_strstr(line, "false") || ft_strstr(line, "FALSE"))
		return (0);
	return (0);
}

double		parse_value(const char *line, double min, double max)
{
	int			i;
	double		value;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	(line[i - 1] == '-') ? i -= 1 : 0;
	value = ft_atof(&line[i]);
	value = ft_clampf(value, min, max);
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
			vec.x = parse_value(tab[i], -1000, 1000);
		else if (ft_strstr(tab[i], "y:"))
			vec.y = parse_value(tab[i], -1000, 1000);
		else if (ft_strstr(tab[i], "z:"))
			vec.z = parse_value(tab[i], -1000, 1000);
		ft_strdel(&tab[i]);
	}
	ft_memdel((void**)tab);
	return (vec);
}
