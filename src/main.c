/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 11:54:44 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/20 04:45:24 by tbeauman         ###   ########.fr       */
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

// int		main(int ac, char **av)
// {
// 	t_poly4	p;
// 	int		ret;
//
// 	if (ac == 6)
// 	{
// 		p.a4 = ft_atof(av[1]);
// 		p.a3 = ft_atof(av[2]);
// 		p.a2 = ft_atof(av[3]);
// 		p.a1 = ft_atof(av[4]);
// 		p.a0 = ft_atof(av[5]);
// 		ret = solve_quartic(&p);
// 		printf("ret: %d\n", ret);
// 		printf("polynom: %fx^4 + %fx^3 + %fx^2 + %fx + %f\n", p.a4, p.a3, p.a2, p.a1, p.a0);
// 		if (ret == 2)
// 			printf("\033[33m%f | %f\n\033[0m", p.root1,
// 			p.root2);
// 		else if (ret == 4)
// 			printf("\033[33m%f	|	%f	|	%f | %f\n\033[0m", p.root1,
// 			p.root2,
// 			p.root3,
// 			p.root4);
// 		else
// 			printf("no roots\n");
// 	}
// 	if (ac == 5)
// 	{
// 		p.a3 = ft_atof(av[1]);
// 		p.a2 = ft_atof(av[2]);
// 		p.a1 = ft_atof(av[3]);
// 		p.a0 = ft_atof(av[4]);
// 		printf("polynom: %fx3 + %fx2 + %fx + %f\n", p.a3, p.a2, p.a1, p.a0);
// 		ret = solve_cubic(&p);
// 		if (ret == 1)
// 			printf("\033[31m%f\n\033[0m", p.a3 * p.root1 * p.root1 * p.root1 +
// 			p.a2 * p.root1 * p.root1 + p.a1 * p.root1 + p.a0);
// 		else if (ret == 2)
// 			printf("\033[31m%f	|	%f\n\033[0m", p.a3 * p.root1 * p.root1 * p.root1 +
// 			p.a2 * p.root1 * p.root1 + p.a1 * p.root1 + p.a0,
// 			p.a3 * p.root2 * p.root2 * p.root2 +
// 			p.a2 * p.root2 * p.root2 + p.a1 * p.root2 + p.a0);
// 		else
// 			printf("\033[31m%f	|	%f	|	%f\n\033[0m", p.a3 * p.root1 * p.root1 * p.root1 +
// 			p.a2 * p.root1 * p.root1 + p.a1 * p.root1 + p.a0,
// 			p.a3 * p.root2 * p.root2 * p.root2 +
// 			p.a2 * p.root2 * p.root2 + p.a1 * p.root2 + p.a0,
// 			p.a3 * p.root3 * p.root3 * p.root3 +
// 			p.a2 * p.root3 * p.root3 + p.a1 * p.root3 + p.a0);
// 	}
// }
