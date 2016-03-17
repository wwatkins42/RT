/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 16:13:08 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/17 16:04:03 by wwatkins         ###   ########.fr       */
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

void    kswitch(char *k)
{
    int t;

    t = 0;
    *k == 1 ? t = 1 : 0;
    *k == 1 ? *k = 0 : 0;
    *k == 0 && t != 1 ? *k = 1 : 0;
}

void	display_info(t_env *e, char *str)
{
	static int	y = -17;

	if (y < e->win.h)
		y += 17;
	else
	{
		mlx_clear_window(e->mlx, e->win.adr);
		y = 0;
	}
	mlx_string_put(e->mlx, e->win.adr, 0, y, 0x81E259, str);
	mlx_do_sync(e->mlx);
}

// TEMPORARY
void			vec3_print(const t_vec3 vec)
{
	printf("vec3(%f, %f, %f)\n", vec.x, vec.y, vec.z);
}
