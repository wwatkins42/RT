/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 09:38:30 by scollon           #+#    #+#             */
/*   Updated: 2016/05/02 11:18:30 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		destroy_camera_list(t_env *e, t_cam **list, int nb)
{
	t_cam	*ca;

	ca = *list;
	while (--nb > 0)
	{
		if (ca->type == STEREOSCOPIC)
		{
			if (ca->twin->img.adr)
				mlx_destroy_image(e->mlx, ca->twin->img.adr);
			ca->stereo.adr ? mlx_destroy_image(e->mlx, ca->stereo.adr) : 0;
			ft_memdel((void**)&ca->twin);
		}
		ca->img.adr ? mlx_destroy_image(e->mlx, ca->img.adr) : 0;
		ca->selection = NULL;
		ca = ca->next;
		ft_memdel((void**)&ca->prev);
	}
	*list = NULL;
}

void		destroy_object_texture(t_texture *text)
{
	int		i;

	i = -1;
	while (++i < text->h)
	{
		ft_memdel((void**)&text->img[i]);
		text->normal_map ? ft_memdel((void**)&text->bump[i]) : 0;
	}
	free(text->img);
	text->img = NULL;
	text->normal_map ? free(text->bump) : 0;
	text->bump = NULL;
}

void		destroy_object_list(t_obj **list)
{
	t_obj	*obj;
	t_obj	*past;

	obj = *list;
	past = NULL;
	while (obj != NULL)
	{
		if (obj->mat.texture.defined)
			destroy_object_texture(&obj->mat.texture);
		past = obj;
		obj = obj->next;
		ft_memdel((void**)&past);
	}
	*list = NULL;
}

void		destroy_light_list(t_lgt **list)
{
	t_lgt	*lgt;
	t_lgt	*past;

	lgt = *list;
	past = NULL;
	while (lgt != NULL)
	{
		past = lgt;
		lgt = lgt->next;
		ft_memdel((void**)&past);
	}
	*list = NULL;
}

void		quit(t_env *e, const int status)
{
	e->win.adr ? mlx_destroy_window(e->mlx, e->win.adr) : 0;
	destroy_camera_list(e, &e->cam, e->count.cam);
	destroy_object_list(&e->obj);
	destroy_light_list(&e->lgt);
	ft_memdel(&e->mlx);
	exit(status);
}
