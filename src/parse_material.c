/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 15:26:08 by scollon           #+#    #+#             */
/*   Updated: 2016/03/25 14:53:27 by wwatkins         ###   ########.fr       */
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
	else if (ft_strstr(line, "CHECKER"))
		return (CHECKER);
	else
		return (BMP);
}

static void	parse_material_texture(t_env *e, t_mat *mat, char *line)
{
	char		info[256];

	mat->texture.type = get_texture_type(line);
	if (mat->texture.type == NONE || mat->texture.type == CHECKER)
		return ;
	else if (mat->texture.type == BMP)
	{
		mat->texture = bmp_importer(ft_strstr(line, ":") + 2);
		sprintf(info, "->import:(%dx%d)%s\n", mat->texture.w,
			mat->texture.h, ft_strstr(line, ":") + 2);
	}
	else
	{
		mat->texture = texture_generator(mat->texture.type, T_RES_W, T_RES_H);
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
	else if (ft_strstr(line, "texture_normal_strength:"))
		mat->texture.normal_strength = parse_value(line, 0, 20);
	else if (ft_strstr(line, "texture_scale:"))
		mat->texture.scale = 1.0 / parse_value(line, 0, 100);
	else if (ft_strstr(line, "normal_perturbation:"))
		mat->normal_perturbation = parse_boolean(line);
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
		else if (ft_strstr(line->line, "fresnel:"))
			mat->fresnel.defined = parse_boolean(line->line);
		else
			parse_material_bis(e, mat, line->line);
		line = line->next;
	}
}
