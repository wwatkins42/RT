/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_bbox.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aacuna <aacuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 11:54:44 by aacuna            #+#    #+#             */
/*   Updated: 2016/04/29 12:00:31 by aacuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj	*create_bbox(t_obj *objs)
{
	t_obj	*i;
	t_obj	*nb;

	nb = (t_obj*)malloc(sizeof(*nb));
	default_object(nb);
	nb->type = BBOX;
	i = objs;
	nb->pos = i->pos;
	nb->pos2 = i->pos2;
	while (i != NULL)
	{
		if (i->type == TRIANGLE)
		{
			nb->pos.x = min4(nb->pos.x, i->pos.x, i->pos2.x, i->pos3.x);
			nb->pos.y = min4(nb->pos.y, i->pos.y, i->pos2.y, i->pos3.y);
			nb->pos.z = min4(nb->pos.z, i->pos.z, i->pos2.z, i->pos3.z);
			nb->pos2.x = max4(nb->pos2.x, i->pos.x, i->pos2.x, i->pos3.x);
			nb->pos2.y = max4(nb->pos2.y, i->pos.y, i->pos2.y, i->pos3.y);
			nb->pos2.z = max4(nb->pos2.z, i->pos.z, i->pos2.z, i->pos3.z);
		}
		i = i->next;
	}
	nb->comp = objs;
	return (nb);
}

t_obj	*divide_bbox(t_obj *original_box)
{
	int		nb_objs;
	int		i;
	t_obj	*objs;
	t_obj	*new_box;

	objs = original_box->comp;
	nb_objs = count_objs(objs);
	i = 0;
	if (nb_objs <= 100)
		return (original_box);
	while (i < ((nb_objs / 2) - 1) && objs)
	{
		objs = objs->next;
		i++;
	}
	if (objs)
	{
		new_box = create_bbox(objs->next);
		objs->next = NULL;
		original_box->comp = create_bbox(original_box->comp);
		original_box->comp->next = new_box;
		original_box->comp->next = divide_bbox(original_box->comp->next);
		original_box->comp = divide_bbox(original_box->comp);
	}
	return (original_box);
}

double	min_i(double obj_pos, double obj_pos2,
					double ray_pos, double ray_dir)
{
	double t1;
	double t2;

	t1 = (obj_pos - ray_pos) / ray_dir;
	t2 = (obj_pos2 - ray_pos) / ray_dir;
	return (min(t1, t2));
}

double	max_i(double obj_pos, double obj_pos2,
						double ray_pos, double ray_dir)
{
	double t1;
	double t2;

	t1 = (obj_pos - ray_pos) / ray_dir;
	t2 = (obj_pos2 - ray_pos) / ray_dir;
	return (max(t1, t2));
}

double	intersects_bbox(t_ray *ray, t_obj *b)
{
	double	tnear;
	double	tfar;

	tnear = -INFINITY;
	tfar = INFINITY;
	if (ray->dir.x != 0)
	{
		tnear = max(tnear, min_i(b->pos.x, b->pos2.x, ray->pos.x, ray->dir.x));
		tfar = min(tfar, max_i(b->pos.x, b->pos2.x, ray->pos.x, ray->dir.x));
	}
	if (ray->dir.y != 0)
	{
		tnear = max(tnear, min_i(b->pos.y, b->pos2.y, ray->pos.y, ray->dir.y));
		tfar = min(tfar, max_i(b->pos.y, b->pos2.y, ray->pos.y, ray->dir.y));
	}
	if (tnear > tfar)
		return (INFINITY);
	if (ray->dir.z != 0)
	{
		tnear = max(tnear, min_i(b->pos.z, b->pos2.z, ray->pos.z, ray->dir.z));
		tfar = min(tfar, max_i(b->pos.z, b->pos2.z, ray->pos.z, ray->dir.z));
	}
	if (tnear > tfar)
		return (INFINITY);
	return (tnear);
}
