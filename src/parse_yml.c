/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_yml.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:09:33 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/25 16:36:50 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_line	*init_list(char *line, t_line *prev)
{
	t_line *new;

	!(new = (t_line*)malloc(sizeof(t_line))) ? error(E_MALLOC, NULL, 1) : 0;
	new->line = ft_strdup(line);
	new->next = NULL;
	new->prev = prev;
	return (new);
}

static int		get_condition(int line_type, char *line)
{
	if (line_type == 0)
	{
		return (ft_strncmp(line, "cameras:", 8) == 0 ||
				ft_strncmp(line, "lights:", 7) == 0 ||
				ft_strncmp(line, "objects:", 8) == 0);
	}
	else if (line_type == 1)
	{
		return (ft_strncmp(line, "scenes:", 6) == 0 ||
				ft_strncmp(line, "lights:", 7) == 0 ||
				ft_strncmp(line, "objects:", 8) == 0);
	}
	else if (line_type == 2)
	{
		return (ft_strncmp(line, "cameras:", 8) == 0 ||
				ft_strncmp(line, "scenes:", 6) == 0 ||
				ft_strncmp(line, "objects:", 8) == 0);
	}
	else
	{
		return (ft_strncmp(line, "cameras:", 8) == 0 ||
				ft_strncmp(line, "lights:", 7) == 0 ||
				ft_strncmp(line, "scenes:", 6) == 0);
	}
}

static char		*get_line(const int fd, t_line *first, int line_type)
{
	char	*line;
	t_line	*prev;
	t_line	*cur;

	prev = first;
	cur = first;
	while (get_next_line(fd, &line) > 0)
	{
		if (get_condition(line_type, line))
			return (line);
		if (!is_comment(line))
		{
			prev = cur;
			cur->next = init_list(line, prev);
			cur = cur->next;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (NULL);
}

static void		parse_loop(const int fd, t_parse *core)
{
	char		*tmp;
	char		*line;

	while (get_next_line(fd, &line) > 0 && ft_strcmp(line, "...") != 0)
	{
		tmp = ft_strdup(line);
		if (ft_strncmp(tmp, "scene:", 6) == 0 && ft_strdel(&tmp))
			tmp = get_line(fd, core->scene, 0);
		if (ft_strncmp(tmp, "cameras:", 8) == 0 && ft_strdel(&tmp))
			tmp = get_line(fd, core->cam, 1);
		if (ft_strncmp(tmp, "lights:", 7) == 0 && ft_strdel(&tmp))
			tmp = get_line(fd, core->lgt, 2);
		if (ft_strncmp(tmp, "objects:", 8) == 0 && ft_strdel(&tmp))
			tmp = get_line(fd, core->obj, 3);
		ft_strdel(&tmp);
		ft_strdel(&line);
	}
	ft_strdel(&line);
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

void			parse_yml(t_env *e)
{
	t_parse		core;

	if ((e->arg.fd = open(e->arg.file, O_RDWR)) == -1)
		error(strerror(errno), e->arg.file, 1);
	core.scene = init_list("scene", NULL);
	core.cam = init_list("cameras", NULL);
	core.lgt = init_list("lights", NULL);
	core.obj = init_list("objects", NULL);
	parse_loop(e->arg.fd, &core);
	close(e->arg.fd) == -1 ? error(strerror(errno), e->arg.file, 0) : 0;
	parse(e, &core);
	print_de_batard(e);
	ft_printf("parsed !\n");
}
