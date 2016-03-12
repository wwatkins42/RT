/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 11:54:44 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/12 14:29:39 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	args_disp(void)
{
	ft_putendl("\nusage:\n./rt [-s scene] [-w width] [-h height] [--help]");
	ft_putendl("\noptions:");
	ft_putendl("-s <file_path> set specified program scene.");
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
	e->arg.file = NULL;
	while (++i < ac)
	{
		!ft_strcmp(av[i], "--help") ? args_disp() : 0;
		if (!ft_strcmp(av[i], "-w") || !ft_strcmp(av[i], "--width"))
			i + 1 < ac ? e->arg.w = ft_atoi(av[i + 1]) : 0;
		else if (!ft_strcmp(av[i], "-h") || !ft_strcmp(av[i], "--height"))
			i + 1 < ac ? e->arg.h = ft_atoi(av[i + 1]) : 0;
		else if (!ft_strcmp(av[i], "-s") || !ft_strcmp(av[i], "--scene"))
			i + 1 < ac ? e->arg.file = ft_strdup(av[i + 1]) : 0;
	}
	if (e->arg.file == NULL)
		e->arg.file = ft_strdup("./resource/scene/default.yml");
}

int			main(int ac, char **av)
{
	t_env e;

	ac == 2 && !ft_strcmp(av[1], "--help") ? args_disp() : 0;
	!(e.mlx = mlx_init()) ? error(E_MLX_INIT, NULL, 1) : 0;
	args_get(&e, ac, av);
	init_env(&e);
	parse(&e);
	core(&e);
	return (0);
}
