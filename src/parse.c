/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:09:33 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/17 15:57:34 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			parse(t_env *e)
{
	char	*line;
	char	info[256];

	if ((e->arg.fd = open(e->arg.file, O_RDWR)) == -1)
		error(strerror(errno), e->arg.file, 1);
	sprintf(info, "FILE: %s (%dx%d)\n", e->arg.file, e->win.w, e->win.h);
	display_info(e, info);
	while (get_next_line(e->arg.fd, &line) > 0 && ft_strcmp(line, "...") != 0)
	{
		if (ft_strstr(line, "cameras:"))
			parse_camera(e, line);
		else if (ft_strstr(line, "lights:"))
			parse_lights(e, line);
		else if (ft_strstr(line, "objects:"))
			parse_objects(e, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	sprintf(info, "SCENE:[cam:%d, lgt:%d, obj:%d]\n",
	e->count.cam, e->count.lgt, e->count.obj);
	display_info(e, info);
}

static short	get_texture_type(const char *line)
{
	if (ft_strstr(line, "NONE"))
		return (NONE);
	else if (ft_strstr(line, "MARBLE"))
		return (MARBLE);
	else if (ft_strstr(line, "WOOD"))
		return (WOOD);
	else if (ft_strstr(line, "EARTH"))
		return (EARTH);
	else
		return (BMP);
}

void			parse_texture(t_env *e, t_obj *obj, const char *line)
{
	short		type;
	char		info[256];

	type = get_texture_type(line);
	if (type == NONE)
		return ;
	else if (type == BMP)
	{
		obj->mat.texture = bmp_importer(ft_strstr(line, ":") + 2);
		sprintf(info, "->import:(%dx%d)%s\n", obj->mat.texture.w,
			obj->mat.texture.h, ft_strstr(line, ":") + 2);
	}
	else
	{
		obj->mat.texture = texture_generator(type, T_RES_W, T_RES_H);
		sprintf(info, "->perlin:(%dx%d)[%s]\n", obj->mat.texture.w,
			obj->mat.texture.h, ft_strstr(line, ":") + 2);
	}
	display_info(e, info);
}

t_vec3			parse_vector(const char *line)
{
	int		i;
	char	**tab;
	t_vec3	vec3;

	i = -1;
	vec3 = (t_vec3) { 0, 0, 0 };
	tab = ft_strsplit(line, ' ');
	while (tab[++i] != NULL)
	{
		if (tab[i + 1] != NULL)
		{
			if (tab[i][1] == 'x')
				vec3.x = ft_atof(tab[i + 1]);
			if (tab[i][0] == 'y')
				vec3.y = ft_atof(tab[i + 1]);
			if (tab[i][0] == 'z')
				vec3.z = ft_atof(tab[i + 1]);
		}
		ft_strdel(&tab[i]);
	}
	vec3_clamp(&vec3, MIN_POS, MAX_POS);
	ft_memdel((void**)tab);
	return (vec3);
}
