/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 15:26:08 by scollon           #+#    #+#             */
/*   Updated: 2016/03/22 17:46:45 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static short		get_texture_type(const char *line)
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

static void	parse_material_texture(t_env *e, t_mat *mat, char *line)
{
	short		type;
	char		info[256];

	type = get_texture_type(line);
	if (type == NONE)
		return ;
	else if (type == BMP)
	{
		mat->texture = bmp_importer(ft_strstr(line, ":") + 2);
		sprintf(info, "->import:(%dx%d)%s\n", mat->texture.w,
			mat->texture.h, ft_strstr(line, ":") + 2);
	}
	else
	{
		mat->texture = texture_generator(type, T_RES_W, T_RES_H);
		sprintf(info, "->perlin:(%dx%d)[%s]\n", mat->texture.w,
			mat->texture.h, ft_strstr(line, ":") + 2);
	}
	display_info(e, info);
}

static void			parse_material_bis(t_env *e, t_mat *mat, char *line)
{
	if (ft_strstr(line, "refract:"))
		mat->refract = parse_value(line, 0, 10);
	else if (ft_strstr(line, "transparency:"))
		mat->transparency = parse_value(line, 0, 1);
	else if (ft_strstr(line, "absorbtion:"))
		mat->absorbtion = parse_value(line, 0, 1);
	else if (ft_strstr(line, "texture:"))
		parse_material_texture(e, mat, line);
	else if (ft_strstr(line, "texture_filtering:"))
		mat->texture.filtering = parse_boolean(line);
	else if (ft_strstr(line, "receive_shadow:"))
		mat->receive_shadow = parse_boolean(line);
	else if (ft_strstr(line, "texture_normal:"))
		mat->texture.normal_map = parse_boolean(line);
}

void				parse_material(t_env *e, t_mat *mat, t_line *line)
{
	while (line != NULL && !ft_strstr(line->line, "- object:"))
	{
		if (ft_strstr(line->line, "color:"))
			mat->color = parse_color(line->line);
		else if (ft_strstr(line->line, "ambient:"))
			mat->ambient = parse_value(line->line, 0, 1);
		else if (ft_strstr(line->line, "diffuse:"))
			mat->diffuse = parse_value(line->line, 0, 10);
		else if (ft_strstr(line->line, "specular:"))
			mat->specular = parse_value(line->line, 0, 50);
		else if (ft_strstr(line->line, "shininess:"))
			mat->shininess = parse_value(line->line, 0, 16384);
		else if (ft_strstr(line->line, "reflect:"))
			mat->reflect = parse_value(line->line, 0, 1);
		else
			parse_material_bis(e, mat, line->line);
		line = line->next;
	}
}
