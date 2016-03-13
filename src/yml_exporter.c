/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yml_exporter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 09:30:41 by scollon           #+#    #+#             */
/*   Updated: 2016/03/13 14:56:31 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	*get_type(int type, int obj)
{
	if (obj == 0)
	{
		if (type == 0)
			return ("POINT");
		else if (type == 1)
			return ("SPOT");
		else
			return ("DIRECTIONAL");
	}
	else
	{
		if (type == 0)
			return ("SPHERE");
		else if (type == 1)
			return ("CONE");
		else if (type == 2)
			return ("PLANE");
		else
			return ("CYLINDER");
	}
}

static void	export_camera(const int fd, t_env *e)
{
	int		i;
	t_cam	*cam;

	i = -1;
	cam = e->cam;
	ft_printf_fd(fd, "cameras:\n");
	while (++i < 1)
	{
		ft_printf_fd(fd, "- camera:\n");
		ft_printf_fd(fd, "  pos: {x: %f, y: %f, z: %f}\n",
					cam->pos.x, cam->pos.y, cam->pos.z);
		ft_printf_fd(fd, "  dir: {x: %f, y: %f, z: %f}\n",
					cam->dir.x, cam->dir.y, cam->dir.z);
		ft_printf_fd(fd, "  fov: %ld\n", cam->fov);
		write(fd, "\n", 1);
		cam = cam->next;
	}
}

static void	export_light(const int fd, t_env *e)
{
	t_lgt	*lgt;

	lgt = e->lgt;
	ft_printf_fd(fd, "lights:\n");
	while (lgt != NULL)
	{
		ft_printf_fd(fd, "- type: %s\n", get_type(lgt->type, 0));
		ft_printf_fd(fd, "  pos: {x: %f, y: %f, z: %f}\n",
					lgt->pos.x, lgt->pos.y, lgt->pos.z);
		ft_printf_fd(fd, "  color: %#x\n", vec3_hex(lgt->color));
		ft_printf_fd(fd, "  intensity: %f\n", lgt->intensity);
		ft_printf_fd(fd, "  shadow: %s\n", "HARD");
		write(fd, "\n", 1);
		lgt = lgt->next;
	}
}

static void	export_object(const int fd, t_env *e)
{
	t_obj *obj;

	obj = e->obj;
	write(fd, "objects:\n", 9);
	while (obj != NULL)
	{
		ft_printf_fd(fd, "- type: %s\n", get_type(obj->type, 1));
		ft_printf_fd(fd, "  pos: {x: %f, y: %f, z: %f}\n",
					obj->pos.x, obj->pos.y, obj->pos.z);
		ft_printf_fd(fd, "  pos: {x: %f, y: %f, z: %f}\n",
					obj->dir.x, obj->dir.y, obj->dir.z);
		write(fd, "  material:\n", 12);
		ft_printf_fd(fd, "    color: %#x\n", vec3_hex(obj->mat.color));
		ft_printf_fd(fd, "    ambient: %f\n", obj->mat.ambient);
		ft_printf_fd(fd, "    diffuse: %f\n", obj->mat.diffuse);
		ft_printf_fd(fd, "    specular: %f\n", obj->mat.specular);
		ft_printf_fd(fd, "    shininess: %f\n", obj->mat.shininess);
		ft_printf_fd(fd, "    reflect: %f\n", obj->mat.reflect);
		ft_printf_fd(fd, "    refract: %f\n", obj->mat.refract);
		ft_printf_fd(fd, "    transparency: %f\n", obj->mat.transparency);
		ft_printf_fd(fd, "    absorbtion: %f\n", obj->mat.absorbtion);
		write(fd, "\n", 1);
		obj = obj->next;
	}
}

void		yml_exporter(t_env *e, char *name)
{
	int		fd;
	char	*full_name;
	char	*buffer;
	time_t	epoch;

	time(&epoch);
	buffer = ft_strdup(name);
	buffer[ft_strrchr(buffer, '.') - buffer] = '\0';
	buffer = ft_strjoin(buffer, "_%d_%m_%Y_%H-%M-%S");
	full_name = (char*)malloc(sizeof(char) * 128);
	strftime(full_name, 128, buffer, localtime(&epoch));
	full_name = ft_strjoin(full_name, ".yml");
	if ((fd = open(full_name, FILE_ARG, FILE_RIGHTS)) == -1)
	{
		error(strerror(errno), full_name, 0);
		ft_strdel(&full_name);
		return ;
	}
	ft_strdel(&full_name);
	write(fd, "---\n", 4);
	export_camera(fd, e);
	export_light(fd, e);
	export_object(fd, e);
	write(fd, "...\n", 4);
	close(fd) == -1 ? error(strerror(errno), NULL, 0) : 0;
}
