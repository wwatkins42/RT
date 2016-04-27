/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbox_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aacuna <aacuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 12:00:39 by aacuna            #+#    #+#             */
/*   Updated: 2016/04/26 12:07:52 by aacuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	min4(double nb1, double nb2, double nb3, double nb4)
{
	double min;

	min = nb1;
	if (nb2 < min)
		min = nb2;
	if (nb3 < min)
		min = nb3;
	if (nb4 < min)
		min = nb4;
	return (min);
}

double	max4(double nb1, double nb2, double nb3, double nb4)
{
	double max;

	max = nb1;
	if (nb2 > max)
		max = nb2;
	if (nb3 > max)
		max = nb3;
	if (nb4 > max)
		max = nb4;
	return (max);
}

double	min(double nb1, double nb2)
{
	if (nb1 < nb2)
		return (nb1);
	else
		return (nb2);
}

double	max(double nb1, double nb2)
{
	if (nb1 > nb2)
		return (nb1);
	else
		return (nb2);
}

int		count_objs(t_obj *obj)
{
	t_obj	*obj_list;
	int		i;

	obj_list = obj;
	i = 0;
	if (obj_list == NULL)
		return (0);
	while (obj_list)
	{
		if (obj_list->type == BBOX)
			i = i + count_objs(obj_list->comp);
		else
			i++;
		obj_list = obj_list->next;
	}
	return (i);
}
