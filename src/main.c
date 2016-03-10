/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 11:54:44 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/10 12:48:48 by scollon          ###   ########.fr       */
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
	e->arg.w = 0;
	e->arg.h = 0;
	e->arg.s = 0;
	e->arg.l = 0;
	e->arg.file = NULL;
	e->arg.viewer_path = NULL;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-w") || !ft_strcmp(av[i], "--width"))
			i + 1 < ac ? e->arg.w = ft_atoi(av[i + 1]) : 0;
		if (!ft_strcmp(av[i], "-h") || !ft_strcmp(av[i], "--height"))
			i + 1 < ac ? e->arg.h = ft_atoi(av[i + 1]) : 0;
		if (!ft_strcmp(av[i], "-s") || !ft_strcmp(av[i], "--scene"))
		{
			i + 1 < ac ? e->arg.file = ft_strdup(av[i + 1]) : 0;
			e->arg.s = 1;
		}
		if (!ft_strcmp(av[i], "-l") || !ft_strcmp(av[i], "--load"))
			i + 1 < ac ? i = parse_load(e, ac, av, i) : 0;
		!ft_strcmp(av[i], "--help") ? args_disp() : 0;
	}
	!e->arg.s && !e->arg.l ? args_disp() : 0;
}

static void	env_init(t_env *e)
{
	e->arg.w = (e->arg.w < 320 || e->arg.w > 10000 ? 1000 : e->arg.w);
	e->arg.h = (e->arg.h < 200 || e->arg.h > 5000 ? 900 : e->arg.h);
	e->win_r.w = e->arg.w;
	e->win_r.h = e->arg.h;
	e->win_r.dw = e->win_r.w / 2;
	e->win_r.dh = e->win_r.h / 2;
	if (e->arg.s)
	{
		if (!(e->win_r.adr = mlx_new_window(e->mlx, e->win_r.w, e->win_r.h,
			e->arg.file)))
			error(E_WIN_INIT, NULL, 1);
	}
	if (e->arg.l)
	{
		if (!(e->win_v.adr = mlx_new_window(e->mlx, e->win_v.w, e->win_v.h,
			"Viewer")))
			error(E_WIN_INIT, NULL, 1);
	}
}

int			main(int ac, char **av)
{
	t_env e;

	ac == 2 && !ft_strcmp(av[1], "--help") ? args_disp() : 0;
	if (!(e.mlx = mlx_init()))
		error(E_MLX_INIT, NULL, 1);
	args_get(&e, ac, av);
	env_init(&e);
	e.arg.s ? parse(&e) : 0;
	//core(&e);
	mlx_loop(e.mlx);
	return (0);
}
