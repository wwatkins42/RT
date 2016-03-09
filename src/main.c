/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 11:54:44 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/09 16:16:53 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	args_disp(void)
{
	ft_putendl("\nusage:\n./rtv1 [scene] [-w width] [-h height] [--help]");
	ft_putendl("\noptions:");
	ft_putendl("-w <width>     set specified program window width.");
	ft_putendl("-h <height>    set specified program window height.");
	ft_putendl("--help         show help.\n");
	exit(0);
}

static void	args_get(t_env *e, int ac, char **av)
{
	int		i;

	i = 0;
	if (ac == 1)
		e->arg.file = ft_strdup("resource/scene/default.yml");
	else
		e->arg.file = ft_strdup(av[1]);
	e->arg.w = 0;
	e->arg.h = 0;
	while (++i < ac)
	{
		if (i + 1 < ac)
		{
			if (!ft_strcmp(av[i], "-w") || !ft_strcmp(av[i], "--width"))
				e->arg.w = ft_atoi(av[i + 1]);
			if (!ft_strcmp(av[i], "-h") || !ft_strcmp(av[i], "--height"))
				e->arg.h = ft_atoi(av[i + 1]);
		}
		!ft_strcmp(av[i], "--help") ? args_disp() : 0;
	}
	e->arg.w = (e->arg.w < 320 || e->arg.w > 10000 ? 1000 : e->arg.w);
	e->arg.h = (e->arg.h < 200 || e->arg.h > 5000 ? 900 : e->arg.h);
}

static void	env_init(t_env *e)
{
	e->win.w = e->arg.w;
	e->win.h = e->arg.h;
	e->win.dw = e->win.w / 2;
	e->win.dh = e->win.h / 2;
	if (!(e->mlx = mlx_init()))
		error(E_MLX_INIT, NULL, 1);
	if (!(e->win.adr = mlx_new_window(e->mlx, e->win.w, e->win.h, e->arg.file)))
		error(E_WIN_INIT, NULL, 1);
	if (!(e->img.adr = mlx_new_image(e->mlx, e->win.w, e->win.h)))
		error(E_IMG_INIT, NULL, 1);
	if (!(e->img.img = mlx_get_data_addr(e->img.adr, &e->img.bpp, &e->img.sl,
		&e->img.endian)))
		error(E_IMG_INIT, NULL, 1);
	e->img.opp = e->img.bpp / 8;
}

int			main(int ac, char **av)
{
	t_env e;

	ac == 2 && !ft_strcmp(av[1], "--help") ? args_disp() : 0;
	args_get(&e, ac, av);
	env_init(&e);
	parse(&e);
	core(&e);
	return (0);
}
