/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 14:52:10 by scollon           #+#    #+#             */
/*   Updated: 2016/03/23 11:50:54 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		default_object(t_obj *object)
{
	object->type = SPHERE;
	object->pos = vec3(0, 0, 5);
	object->pos2 = vec3(0, 1, 0);
	object->pos3 = vec3(1, 0, 0);
	object->dir = vec3(0, 0, 1);
	object->m = 1;
	object->pr = 1;
	object->gr = 2;
	object->min = -10;
	object->max = 10;
	object->scale = 1;
	object->mat.color = vec3(1, 1, 1);
	object->mat.ambient = 0.225;
	object->mat.diffuse = 0.875;
	object->mat.specular = 1.0;
	object->mat.shininess = 256;
	object->mat.reflect = 0;
	object->mat.refract = 0;
	object->mat.transparency = 0;
	object->mat.absorbtion = 0;
	object->mat.texture.defined = 0;
	object->mat.texture.filtering = 0;
	object->mat.texture.normal_map = 0;
	object->mat.receive_shadow = 1;
}

static int		get_object_type(char *line)
{
	if (ft_strstr(line, "SPHERE"))
		return (SPHERE);
	else if (ft_strstr(line, "CONE"))
		return (CONE);
	else if (ft_strstr(line, "PLANE"))
		return (PLANE);
	else if (ft_strstr(line, "CYLINDER"))
		return (CYLINDER);
	else if (ft_strstr(line, "TRIANGLE"))
		return (TRIANGLE);
	else if (ft_strstr(line, "CUBE"))
		return (CUBE);
	else if (ft_strstr(line, "PARALLELOGRAM"))
		return (PARALLELOGRAM);
	else if (ft_strstr(line, "HYPERBOLOID_ONE"))
		return (HYPERBOLOID_ONE);
	else if (ft_strstr(line, "HYPERBOLOID_TWO"))
		return (HYPERBOLOID_TWO);
	else if (ft_strstr(line, "PARABOLOID"))
		return (PARABOLOID);
	else if (ft_strstr(line, "TORUS"))
		return (TORUS);
	else
		error(E_OTYPE, line, 0);
	return (SPHERE);
}

static void create_cube(t_obj *cube)
{
	double	k;

	!(cube->comp = malloc(6 * sizeof(t_obj))) ? error(E_MALLOC, NULL, 0) : 0;
	k = cube->scale;
	cube->comp[0].type = PARALLELOGRAM;
	cube->comp[0].pos = cube->pos;
	cube->comp[0].pos2 = (t_vec3) {k, 0, 0};
	cube->comp[0].pos3 = (t_vec3) {0, k, 0};
	cube->comp[0].dir = vec3_norm(vec3_cross(cube->comp[0].pos2, cube->comp[0].pos3));
	cube->comp[1].type = PARALLELOGRAM;
	cube->comp[1].pos = vec3_add(cube->pos, (t_vec3) {k, 0, 0});
	cube->comp[1].pos2 = (t_vec3) {0, 0, k};
	cube->comp[1].pos3 = (t_vec3) {0, k, 0};
	cube->comp[1].dir = vec3_norm(vec3_cross(cube->comp[1].pos2, cube->comp[1].pos3));
	cube->comp[2].type = PARALLELOGRAM;
	cube->comp[2].pos = vec3_add(cube->pos, (t_vec3) {0, 0, k});
	cube->comp[2].pos2 = (t_vec3) {0, 0, -k};
	cube->comp[2].pos3 = (t_vec3) {0, k, 0};
	cube->comp[2].dir = vec3_norm(vec3_cross(cube->comp[2].pos2, cube->comp[2].pos3));
	cube->comp[3].type = PARALLELOGRAM;
	cube->comp[3].pos = vec3_add(cube->pos, (t_vec3) {0, k, 0});
	cube->comp[3].pos2 = (t_vec3) {k, 0, 0};
	cube->comp[3].pos3 = (t_vec3) {0, 0, k};
	cube->comp[3].dir = vec3_norm(vec3_cross(cube->comp[3].pos2, cube->comp[3].pos3));
	cube->comp[4].type = PARALLELOGRAM;
	cube->comp[4].pos = cube->pos;
	cube->comp[4].pos2 = (t_vec3) {k, 0, 0};
	cube->comp[4].pos3 = (t_vec3) {0, 0, k};
	cube->comp[4].dir = vec3_norm(vec3_cross(cube->comp[4].pos2, cube->comp[4].pos3));
	cube->comp[5].type = PARALLELOGRAM;
	cube->comp[5].pos = vec3_add(cube->pos, (t_vec3) {k, 0, k});
	cube->comp[5].pos2 = (t_vec3) {-k, 0, 0};
	cube->comp[5].pos3 = (t_vec3) {0, k, 0};
	cube->comp[5].dir = vec3_norm(vec3_cross(cube->comp[5].pos2, cube->comp[5].pos3));
}

static t_obj	*create_object(t_env *e, t_line *object_line)
{
	t_obj		*new;
	t_line		*line;

	line = object_line;
	!(new = (t_obj*)malloc(sizeof(t_obj))) ? error(E_OINIT, NULL, 1) : 0;
	default_object(new);
	while (line != NULL && !ft_strstr(line->line, "- object:"))
	{
		if (ft_strstr(line->line, "type:"))
			new->type = get_object_type(line->line);
		else if (ft_strstr(line->line, "pos:"))
			new->pos = parse_vector(line->line);
		else if (ft_strstr(line->line, "pos2:"))
			new->pos2 = parse_vector(ft_strchr(line->line, ':'));
		else if (ft_strstr(line->line, "pos3:"))
			new->pos3 = parse_vector(ft_strchr(line->line, ':'));
		else if (ft_strstr(line->line, "dir:"))
			new->dir = parse_vector(line->line);
		else if (ft_strstr(line->line, "scale:"))
			new->scale = parse_value(line->line, 0.1, 1000);
		else if (ft_strstr(line->line, "min:"))
			new->min = parse_value(line->line, -INFINITY, INFINITY);
		else if (ft_strstr(line->line, "max:"))
			new->max = parse_value(line->line, -INFINITY, INFINITY);
		else if (ft_strstr(line->line, "pr:"))
			new->pr = ft_atof(ft_strstr(line->line, ":") + 1);
		else if (ft_strstr(line->line, "gr:"))
			new->gr = ft_atof(ft_strstr(line->line, ":") + 1);
		else if (ft_strstr(line->line, "material:"))
			parse_material(e, &new->mat, line);
		line = line->next;
	}
	e->count.obj++;
	new->mat.texture.normal_map && new->mat.texture.defined ? create_normal_map(new) : 0;
	new->scale2 = new->scale * new->scale;
	new->k = tan(new->scale) * tan(new->scale);
	if (new->type == TRIANGLE || new->type == PARALLELOGRAM)
		new->dir = vec3_norm(vec3_cross(new->pos2, new->pos3));
	if (new->type == CUBE)
		create_cube(new);
	else
		new->comp = NULL;
	new->next = NULL;
	return (new);
}

t_obj			*parse_object(t_env *e, t_line *object_line)
{
	t_line	*line;
	t_obj	*object;
	t_obj	*current;

	line = object_line->next->next;
	current = NULL;
	current = create_object(e, line);
	object = current;
	while (line != NULL)
	{
		if (ft_strstr(line->line, "- object:"))
		{
			current->next = create_object(e, line->next);
			current = current->next;
		}
		line = line->next;
	}
	return (object);
}
