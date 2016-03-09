/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 16:13:08 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/09 09:41:04 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				str_digit(char *str)
{
	while (*str)
		if (ft_isdigit(*str++))
			return (1);
	return (0);
}

t_vec3			hex_vec3(const int hex)
{
	t_vec3	ret;

	ret.x = hex % 256;
	ret.y = ((hex >> 8) % 256);
	ret.z = ((hex >> 16) % 256);
	ret.x /= 255;
	ret.y /= 255;
	ret.z /= 255;
	return (ret);
}

t_vec3	parse_vector(const char *line)
{
	int		i;
	char	**tab;
	t_vec3	vec3;

	i = -1;
	vec3 = (t_vec3) { 0, 0, 0 };
	tab = ft_strsplit(line, ' ');
	while (tab[++i] != NULL)
	{
		if (tab[i + 1] != NULL)
		{
			if (tab[i][0] == 'x')
				vec3.x = ft_atof(tab[i + 1]);
			else if (tab[i][0] == 'y')
				vec3.y = ft_atof(tab[i + 1]);
			else if (tab[i][0] == 'z')
				vec3.z = ft_atof(tab[i + 1]);
		}
		ft_strdel(&tab[i]);
	}
	vec3_clamp(&vec3, MIN_POS, MAX_POS);
	ft_memdel((void**)tab);
	return (vec3);
}
