/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 16:13:08 by wwatkins          #+#    #+#             */
/*   Updated: 2016/04/30 14:58:16 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ispressed(char *key)
{
	if (key[MOUSE] || key[I] || key[K] || key[J] || key[L] || key[KP] ||
		key[KM] || key[CU] || key[CD] || key[CL] || key[CR] || key[CF] ||
		key[CB] || key[OU] || key[OD] || key[OL] || key[OR] || key[OF] ||
		key[OB] || key[FI] || key[FG] || key[FGM] || key[FGP] || key[DEL] ||
		key[CMD] || key[CTRL])
		return (1);
	return (0);
}

void	kswitch(char *k)
{
	int	t;

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

void	display_texture(t_env *e, t_rgb **img, t_texture texture)
{
	int		x;
	int		y;

	y = -1;
	while (++y < texture.h)
	{
		x = -1;
		while (++x < texture.w)
			img_pixel_put(&e->cam->img, x, y, rgb_to_vec3(img[y][x]));
	}
}
