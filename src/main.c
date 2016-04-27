/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 11:54:44 by wwatkins          #+#    #+#             */
/*   Updated: 2016/04/27 18:49:52 by tbeauman         ###   ########.fr       */
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

static int		is_yml(const char *str)
{
	char	*buffer;

	buffer = ft_strrchr(str, '.');
	if (buffer == NULL)
		return (0);
	if (ft_strcmp(buffer, ".yml") != 0 && ft_strcmp(buffer, ".yaml") != 0)
		return (0);
	return (1);
}

static void	args_get(t_env *e, int ac, char **av)
{
	int		i;
	int		fd;

	i = 0;
	e->arg.w = 1280;
	e->arg.h = 720;
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
	!is_yml(e->arg.file) ? error(E_IFILE, e->arg.file, 1) : 0;
	if ((fd = open(e->arg.file, O_RDWR)) == -1)
		error(strerror(errno), e->arg.file, 1);
	close(fd) == -1 ? error(strerror(errno), NULL, 1) : 0;
}

int			main(int ac, char **av)
{
	t_env e;

	ac == 2 && !ft_strcmp(av[1], "--help") ? args_disp() : 0;
	!(e.mlx = mlx_init()) ? error(E_MLX_INIT, NULL, 1) : 0;
	args_get(&e, ac, av);
	init_env(&e);
	parse_yml(&e);
	core(&e);
	return (0);
}

// void test(double *r)
// {
// 	r[0] = 4;
// }
//
// int		main(int ac, char **av)
// {
// 	double	a[5];
// 	double	root[4] = {0, 0, 0, 0};
//
// 	// test(root);
// 	// printf("%f, %f, %f, %f", *root, root[1], root[2], root[3]);
// 	if (ac == 6)
// 	{
// 		a[4] = ft_atof(av[1]);
// 		a[3] = ft_atof(av[2]) / a[4];
// 		a[2] = ft_atof(av[3]) / a[4];
// 		a[1] = ft_atof(av[4]) / a[4];
// 		a[0] = ft_atof(av[5]) / a[4];
// 		int r = solve_quartic(a, root);
//
// 		printf("polynom: y=x^4+%fx^3+%fx^2+%fx+%f\n", a[3], a[2], a[1], a[0]);
// 		printf("number: %d\nsolve_quartic:\n", r);
// 		printf("\033[33m%f 	|	%f 	|	%f  | %f \n\033[0m",
// 		root[0],root[1],
// 		root[2],root[3]);
// 		r = gsl_poly_solve_quartic(a[3], a[2], a[1], a[0], &root[0], &root[1], &root[2], &root[3]);
// 		printf("number: %d\ngsl_poly_solve_quartic:\n", r);
// 		printf("\033[33m%f 	|	%f 	|	%f  | %f \n\033[0m",
// 		root[0],root[1],
// 		root[2],root[3]);
// 	}
// }
