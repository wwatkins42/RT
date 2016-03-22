/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 15:26:08 by scollon           #+#    #+#             */
/*   Updated: 2016/03/22 07:54:37 by scollon          ###   ########.fr       */
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

static t_texture	parse_material_texture(t_env *e, const char *line)
{
	t_texture	texture;
	short		type;
	char		info[256];

	type = get_texture_type(line);
	texture.defined = 0;
	texture.filtering = 0;
	texture.normal_map = 0;
	if (type == NONE)
		return (texture);
	else if (type == BMP)
	{
		texture = bmp_importer(ft_strstr(line, ":") + 2);
		sprintf(info, "->import:(%dx%d)%s\n", texture.w,
			texture.h, ft_strstr(line, ":") + 2);
	}
	else
	{
		texture = texture_generator(type, T_RES_W, T_RES_H);
		sprintf(info, "->perlin:(%dx%d)[%s]\n", texture.w,
			texture.h, ft_strstr(line, ":") + 2);
	}
	display_info(e, info);
	return (texture);
}

static void			parse_material_bis(t_env *e, t_mat *mat, const char *line)
{
	if (ft_strstr(line, "refract:"))
		mat->refract = parse_value(line);
	else if (ft_strstr(line, "transparency:"))
		mat->transparency = parse_value(line);
	else if (ft_strstr(line, "absorbtion:"))
		mat->absorbtion = parse_value(line);
	else if (ft_strstr(line, "texture:"))
		mat->texture = parse_material_texture(e, line);
	else if (ft_strstr(line, "texture_filtering:"))
		mat->texture.filtering = parse_value(line);
	else if (ft_strstr(line, "shadow:"))
		mat->shadow = parse_value(line);
	else if (ft_strstr(line, "bump:"))
		mat->texture.normal_map = parse_value(line);
}

t_mat				parse_material(t_env *e, t_line *line)
{
	t_mat	mat;

	while (line != NULL && !ft_strstr(line->line, "- object:"))
	{
		if (ft_strstr(line->line, "color:"))
			mat.color = parse_color(line->line);
		else if (ft_strstr(line->line, "ambient:"))
			mat.ambient = parse_value(line->line);
		else if (ft_strstr(line->line, "diffuse:"))
			mat.diffuse = parse_value(line->line);
		else if (ft_strstr(line->line, "specular:"))
			mat.specular = parse_value(line->line);
		else if (ft_strstr(line->line, "shininess:"))
			mat.shininess = parse_value(line->line);
		else if (ft_strstr(line->line, "reflect:"))
			mat.reflect = parse_value(line->line);
		else
			parse_material_bis(e, &mat, line->line);
		line = line->next;
	}
	return (mat);
}
