/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 16:13:08 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/18 12:25:03 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		str_digit(char *str)
{
	while (*str)
		if (ft_isdigit(*str++))
			return (1);
	return (0);
}

void	repeat(float *value, float bound, float size, short type)
{
	if (type == SUP)
		while (*value > bound)
			*value -= size;
	else
		while (*value < bound)
			*value += size;
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

void	display_loading(t_env *e, int u, int v)
{
	static int	prev = 0;
	int			percent;
	float		progress;
	float		goal;

	progress = u * (v + 1);
	goal = e->win.w * e->win.h;
	percent = progress / goal * 100;
	if (percent != prev)
	{
		if (e->scene.resync)
		{
			mlx_put_image_to_window(e->mlx, e->win.adr, e->cam->img.adr, 0, 0);
			mlx_do_sync(e->mlx);
		}
		if (e->scene.percent)
		{
			system("clear");
			ft_printf("%d%%\n", percent);
		}
		prev = percent;
	}
}
