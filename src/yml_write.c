/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yml_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 08:11:00 by scollon           #+#    #+#             */
/*   Updated: 2016/04/30 09:48:59 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	*get_type(int type)
{
	if (type == 0)
		return ("POINT");
	else if (type == 1)
		return ("SPOT");
	else
		return ("DIRECTIONAL");
}

void		export_camera(const int fd, t_env *e)
{
	int		i;
	t_cam	*cam;

	i = -1;
	cam = e->cam;
	ft_printf_fd(fd, "cameras:\n");
	while (++i < e->count.cam)
	{
		ft_printf_fd(fd, "- camera:\n");
		cam->type == STEREOSCOPIC ? ft_printf_fd(fd, "  type: STEREO\n") : 0;
		ft_printf_fd(fd, "  pos: {x: %f, y: %f, z: %f}\n",
					cam->pos.x, cam->pos.y, cam->pos.z);
		ft_printf_fd(fd, "  dir: {x: %f, y: %f, z: %f}\n",
					cam->dir.x, cam->dir.y, cam->dir.z);
		ft_printf_fd(fd, "  fov: %f\n", cam->fov);
		ft_printf_fd(fd, "  supersampling: %d", cam->aa.supersampling);
		write(fd, "\n", 1);
		cam = cam->next;
	}
	write(fd, "\n", 1);
}

void		export_light(const int fd, t_env *e)
{
	t_lgt	*lgt;

	lgt = e->lgt;
	ft_printf_fd(fd, "lights:\n");
	while (lgt != NULL)
	{
		ft_printf_fd(fd, "- light:\n");
		ft_printf_fd(fd, "  type: %s\n", get_type(lgt->type));
		ft_printf_fd(fd, "  pos: {x: %f, y: %f, z: %f}\n",
					lgt->pos.x, lgt->pos.y, lgt->pos.z);
		ft_printf_fd(fd, "  color: %#x\n", vec3_hex(lgt->color));
		ft_printf_fd(fd, "  intensity: %f\n", lgt->intensity);
		ft_printf_fd(fd, "  shadow: %s\n", "HARD");
		write(fd, "\n", 1);
		lgt = lgt->next;
	}
}
