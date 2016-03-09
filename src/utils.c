/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 16:13:08 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/09 10:54:18 by wwatkins         ###   ########.fr       */
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
