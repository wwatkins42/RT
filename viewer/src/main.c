/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:26:36 by scollon           #+#    #+#             */
/*   Updated: 2016/03/11 10:03:30 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"
#include "bmp_exporter.h"

static void		args_disp(void)
{
	ft_putendl("\nusage:\n./image_viewer image [--help]");
	ft_putendl("\nimport and show mlx image");
	ft_putendl("options:");
	ft_putendl("--help         show help.\n");
	exit(0);
}

static void		parse_load(t_env *e, int ac, char **av, int i)
{
	t_view	*prev;
	t_view	*current;

	e->win.w = 0;
	e->win.h = 0;
	!(current = (t_view*)malloc(sizeof(t_view))) ? error(E_MALLOC, NULL, 1) : 0;
	e->head_viewer = current;
	prev = NULL;
	while (++i < ac)
	{
		current->prev = prev;
		e->viewer_path = ft_strdup(av[i]);
		current->img = viewer_import(e);
		current->img.w > e->win.w ? e->win.w = current->img.w : 0;
		current->img.h > e->win.h ? e->win.h = current->img.h : 0;
		prev = current;
		if (i + 1 < ac)
		{
			if (!(current->next = (t_view*)malloc(sizeof(t_view))))
				error(E_MALLOC, NULL, 1);
			current = current->next;
		}
	}
	e->tail_viewer = current;
	current->next = NULL;
}

int				main(int ac, char **av)
{
	int			i;
	t_env		e;

	i = 0;
	ac == 1 || !ft_strcmp(av[1], "--help") ? args_disp() : 0;
	!(e.mlx = mlx_init()) ? error(E_MLX_INIT, NULL, 1) : 0;
	parse_load(&e, ac, av, 0);
	if (e.win.w > 2560 || e.win.h > 1440 || e.win.w < 200 || e.win.h < 100)
		error("invalid image file", NULL, 1);
	e.current = e.head_viewer;
	if (!(e.win.adr = mlx_new_window(e.mlx, e.win.w, e.win.h, "Viewer")))
		error(E_WIN_INIT, NULL, 1);
	mlx_hook(e.win.adr, 2, (1L << 0), key_pressed, &e);
	mlx_expose_hook(e.win.adr, expose_hook, &e);
	mlx_loop_hook(e.mlx, loop_hook, &e);
	mlx_loop(e.mlx);
}
