/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 16:13:08 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/10 12:44:42 by scollon          ###   ########.fr       */
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

	ret.x = (hex % 256) / 255.0;
	ret.y = ((hex >> 8) % 256) / 255.0;
	ret.z = ((hex >> 16) % 256) / 255.0;
	return (ret);
}

t_img			img_init(t_env *e, int w, int h)
{
	t_img	img;

	if (!(img.adr = mlx_new_image(e->mlx, w, h)))
		error(E_IMG_INIT, NULL, 1);
	if (!(img.img = mlx_get_data_addr(img.adr, &img.bpp, &img.sl,
		&img.endian)))
		error(E_IMG_INIT, NULL, 1);
	img.opp = img.bpp / 8;
	return (img);
}
