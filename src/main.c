/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 11:54:44 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/22 09:24:48 by scollon          ###   ########.fr       */
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
	int		fd;

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
	if ((fd = open(e->arg.file, O_RDWR)) == -1)
		error(strerror(errno), e->arg.file, 1);
	close(fd) == -1 ? error(strerror(errno), NULL, 1) : 0;
}


static void	print_vec3(char *s, t_vec3 vec)
{
	ft_printf("%s: %f, %f, %f\n", s, vec.x, vec.y, vec.z);
}

void	print_de_batard(t_env *e)
{
	int			i = 0;
	t_cam		*cam;
	t_obj		*obj;
	t_lgt		*lgt;

	cam = e->cam;
	obj = e->obj;
	lgt = e->lgt;
	ft_printf("cameras: \n");
	while (i < e->count.cam)
	{
		print_vec3("pos", cam->pos);
		print_vec3("dir", cam->dir);
		ft_printf("fov: %f\n", cam->fov);
		ft_printf("ss: %d\n", cam->aa.supersampling);
		ft_printf("\n");
		i++;
		cam = cam->next;
	}
	ft_printf("\n");
	ft_printf("objects: \n");
	while (obj != NULL)
	{
		ft_printf("type: %d\n", obj->type);
		print_vec3("pos", obj->pos);
		print_vec3("dir", obj->dir);
		ft_printf("material:\n");
		print_vec3("color", obj->mat.color);
		ft_printf("ambient: %f\n", obj->mat.ambient);
		ft_printf("diffuse: %f\n", obj->mat.diffuse);
		ft_printf("specular: %f\n", obj->mat.specular);
		ft_printf("shininess: %f\n", obj->mat.shininess);
		ft_printf("reflect: %f\n", obj->mat.reflect);
		ft_printf("refract: %f\n", obj->mat.refract);
		ft_printf("transparency: %f\n", obj->mat.transparency);
		ft_printf("absorbtion: %f\n", obj->mat.absorbtion);
		ft_printf("blf: %d\n", obj->mat.texture.filtering);
		ft_printf("texture: %d\n", obj->mat.texture.defined);
		ft_printf("texture.w: %d\n", obj->mat.texture.w);
		ft_printf("texture.h: %d\n", obj->mat.texture.h);
		ft_printf("img: %p\n", obj->mat.texture.img);
		ft_printf("\n");
		obj = obj->next;
	}
	ft_printf("\n");
	ft_printf("lights: \n");
	while (lgt != NULL)
	{
		ft_printf("type: %d\n", lgt->type);
		print_vec3("pos", lgt->pos);
		print_vec3("dir", lgt->dir);
		print_vec3("color", lgt->color);
		ft_printf("intensity: %f\n", lgt->intensity);
		ft_printf("\n");
		lgt = lgt->next;
	}
}


int			main(int ac, char **av)
{
	t_env e;

	ac == 2 && !ft_strcmp(av[1], "--help") ? args_disp() : 0;
	!(e.mlx = mlx_init()) ? error(E_MLX_INIT, NULL, 1) : 0;
	args_get(&e, ac, av);
	init_env(&e);
	parse_yml(&e);
	print_de_batard(&e);
	core(&e);
	return (0);
}
