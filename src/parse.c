/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 11:27:42 by scollon           #+#    #+#             */
/*   Updated: 2016/03/22 17:17:04 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	destroy_parse(t_parse *core)
{
	int			i;
	t_line		*cur;
	t_line		*tmp;

	i = 0;
	while (i < 4)
	{
		i == 0 ? cur = core->cam : 0;
		i == 1 ? cur = core->lgt : 0;
		i == 2 ? cur = core->obj : 0;
		i == 3 ? cur = core->scene : 0;
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

static void	parse_scene(t_env *e, t_line *scene)
{
	t_line *line;

	line = scene;
	while (line != NULL)
	{
		if (ft_strstr(line->line, "reflect_max:"))
			e->reflect.depth_max = parse_value(line->line, 0, 16);
		else if (ft_strstr(line->line, "refract_max:"))
			e->refract.depth_max = parse_value(line->line, 0, 16);
		else if (ft_strstr(line->line, "sensibility:"))
			e->mouse.sensibility = parse_value(line->line, 0, 0.6);
		else if (ft_strstr(line->line, "lerp:"))
			e->mouse.lerp = parse_boolean(line->line);
		else if (ft_strstr(line->line, "velocity:"))
			e->scene.velocity = parse_value(line->line, 0, 10);
		else if (ft_strstr(line->line, "resync:"))
			e->scene.resync = parse_boolean(line->line);
		else if (ft_strstr(line->line, "percent:"))
			e->scene.percent = parse_boolean(line->line);
		line = line->next;
	}
}

void		parse(t_env *e, t_parse *core)
{
	char	info[256];

	sprintf(info, "FILE: %s (%dx%d)\n", e->arg.file, e->win.w, e->win.h);
	display_info(e, info);
	parse_scene(e, core->scene);
	e->cam = parse_camera(e, core->cam);
	e->lgt = parse_light(e, core->lgt);
	e->obj = parse_object(e, core->obj);
	destroy_parse(core);
	sprintf(info, "SCENE:[cam:%d, lgt:%d, obj:%d]\n",
	e->count.cam, e->count.lgt, e->count.obj);
	display_info(e, info);
}
