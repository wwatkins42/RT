/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 16:13:08 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/14 10:58:18 by wwatkins         ###   ########.fr       */
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



// TEMPORARY
void			vec3_print(const t_vec3 vec)
{
	printf("vec3(%f, %f, %f)\n", vec.x, vec.y, vec.z);
}

void    kswitch(char *k)
{
    int t;

    t = 0;
    *k == 1 ? t = 1 : 0;
    *k == 1 ? *k = 0 : 0;
    *k == 0 && t != 1 ? *k = 1 : 0;
}
