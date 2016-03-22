/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 11:27:42 by scollon           #+#    #+#             */
/*   Updated: 2016/03/22 07:53:28 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	destroy_parse(t_parse *core)
{
	int			i;
	t_line		*cur;
	t_line		*tmp;

	i = 0;
	while (i < 3)
	{
		i == 0 ? cur = core->cam : 0;
		i == 1 ? cur = core->lgt : 0;
		i == 2 ? cur = core->obj : 0;
		while (cur != NULL)
		{
			tmp = cur;
			ft_strdel(&cur->line);
			ft_memdel((void**)&cur);
			cur = tmp->next;
		}
		i++;
	}
}

void		parse(t_env *e, t_parse *core)
{
	e->cam = parse_camera(e, core->cam);
	e->lgt = parse_light(e, core->lgt);
	e->obj = parse_object(e, core->obj);
	destroy_parse(core);
}
