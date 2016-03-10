/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:26:36 by scollon           #+#    #+#             */
/*   Updated: 2016/03/10 16:31:57 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

static void		parse_load(t_env *e, int ac, char **av, int i)
{
	t_view	*prev;
	t_view	*current;

	e->win.w = 0;
	e->win.h = 0;
	if (!(current = (t_view*)malloc(sizeof(t_view))))
		error(E_MALLOC, NULL, 1);
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

int		loop_hook(t_env *e)
{
	expose_hook(e);
	return (0);
}

int		expose_hook(t_env *e)
{
	int	ofx;
	int	ofy;

	ofx = (e->win.w - e->current->img.w) / 2.0;
	ofy = (e->win.h - e->current->img.h) / 2.0;
	mlx_clear_window(e->mlx, e->win.adr);
	mlx_put_image_to_window(e->mlx, e->win.adr, e->current->img.adr, ofx, ofy);
	return (0);
}

int		key_pressed(int kc, t_env *e)
{
	kc == 53 ? exit(0) : 0;
	if (kc == 43 || kc == 123)
		e->current = e->current->next != NULL ? e->current->next : e->head_viewer;
	if (kc == 47 || kc == 124)
		e->current = e->current->prev != NULL ? e->current->prev : e->tail_viewer;
	return (0);
}

int				main(int ac, char **av)
{
	int			i;
	t_env		e;

	i = 0;
	//ac > 1 && !ft_strcmp(av[1], "--help") ? args_disp() : 0;
	!(e.mlx = mlx_init()) ? error(E_MLX_INIT, NULL, 1) : 0;
	parse_load(&e, ac, av, 0);
	e.current = e.head_viewer;
	if (!(e.win.adr = mlx_new_window(e.mlx, e.win.w, e.win.h, "Viewer")))
		error(E_WIN_INIT, NULL, 1);
	mlx_hook(e.win.adr, 2, (1L << 0), key_pressed, &e);
	mlx_expose_hook(e.win.adr, expose_hook, &e);
	mlx_loop_hook(e.mlx, loop_hook, &e);
	mlx_loop(e.mlx);
}
