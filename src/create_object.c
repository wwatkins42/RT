/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 13:54:26 by scollon           #+#    #+#             */
/*   Updated: 2016/05/02 10:15:50 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static t_mat		default_material(void)
{
	t_mat	mat;

	mat.color = vec3(1, 1, 1);
	mat.ambient = 0.225;
	mat.diffuse = 0.875;
	mat.specular = 1.0;
	mat.shininess = 256;
	mat.glossiness = 0;
	mat.reflect = 0;
	mat.refract = 0;
	mat.transparency = 0;
	mat.absorbtion = 0;
	mat.texture.defined = 0;
	mat.texture.transparency_mapping = 0;
	mat.texture.filtering = 0;
	mat.texture.normal_map = 0;
	mat.texture.normal_strength = 2;
	mat.texture.scale = 1;
	mat.texture.rotation = 0;
	mat.receive_shadow = 1;
	mat.fresnel.defined = 0;
	mat.normal_perturbation = 0;
	return (mat);
}

void				default_object(t_obj *object)
{
	object->type = SPHERE;
	object->pos = vec3(0, 0, 5);
	object->pos2 = vec3(0, 1, 0);
	object->pos3 = vec3(1, 0, 0);
	object->dir = vec3(0, 0, 1);
	object->cut = vec3(0, 0, 0);
	object->m = 1;
	object->pr = 1;
	object->gr = 2;
	object->min = -INFINITY;
	object->max = INFINITY;
	object->scale = 1;
	object->mat = default_material();
	object->comp = NULL;
	object->next = NULL;
	object->left = NULL;
	object->right = NULL;
}

int				get_object_type(t_env *e, char *line)
{
	int		i;
	char	*type;

	i = -1;
	if (!(type = ft_strtrim(ft_strchr(line, ':') + 1)))
		error(e, E_MALLOC, NULL, 1);
	while (g_object_type[++i].reference != NULL)
	{
		if (ft_strcmp(type, g_object_type[i].reference) == 0)
		{
			ft_strdel(&type);
			return (g_object_type[i].index);
		}
	}
	error(e, E_OTYPE, type, 0);
	ft_strdel(&type);
	return (SPHERE);
}

void			fill_object_attr(t_env *e, t_line *line, t_obj *new)
{
	if (ft_strstr(line->line, "type:"))
		new->type = get_object_type(e, line->line);
	else if (ft_strstr(line->line, "pos:"))
		new->pos = parse_vector(e, line->line);
	else if (ft_strstr(line->line, "pos2:"))
		new->pos2 = parse_vector(e, ft_strchr(line->line, ':'));
	else if (ft_strstr(line->line, "pos3:"))
		new->pos3 = vec3_norm(parse_vector(e, ft_strchr(line->line, ':')));
	else if (ft_strstr(line->line, "dir:"))
		new->dir = vec3_norm(parse_vector(e, line->line));
	else if (ft_strstr(line->line, "cut:"))
		new->cut = parse_vector(e, line->line);
	else if (ft_strstr(line->line, "scale:"))
		new->scale = parse_value(line->line, 0.1, 1000);
	else if (ft_strstr(line->line, "min:"))
		new->min = parse_value(line->line, -INFINITY, INFINITY);
	else if (ft_strstr(line->line, "max:"))
		new->max = parse_value(line->line, -INFINITY, INFINITY);
	else if (ft_strstr(line->line, "pr:"))
		new->pr = parse_value(line->line, 0, INFINITY);
	else if (ft_strstr(line->line, "gr:"))
		new->gr = parse_value(line->line, 0, INFINITY);
	else if (ft_strstr(line->line, "material:"))
		parse_material(e, &new->mat, line);
	else if (ft_strstr(line->line, "obj:"))
		new = parse_obj(ft_strstr(line->line, ":") + 1, e, new);
}

void create_cube(t_env *e, t_obj *cube)
{
        double  k;

        !(cube->comp = malloc(6 * sizeof(t_obj))) ? error(e, E_MALLOC, NULL, 0) : 0;
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


t_obj				*create_object(t_env *e, t_line *object_line)
{
	t_obj		*new;
	t_line		*line;

	line = object_line;
	!(new = (t_obj*)malloc(sizeof(t_obj))) ? error(e, E_OINIT, NULL, 1) : 0;
	default_object(new);
	while (line != NULL && !ft_strstr(line->line, "- object:") &&
		!ft_strchr(line->line, '('))
	{
		fill_object_attr(e, line, new);
		line = line->next;
	}
	e->count.obj++;
	new->id = e->count.obj;
	if (new->mat.texture.normal_map && new->mat.texture.defined)
		create_normal_map(e, new);
	new->scale2 = new->scale * new->scale;
	new->pr *= new->pr;
	new->gr *= new->gr;
	new->k = tan(new->scale) * tan(new->scale);
	if (new->type == TRIANGLE || new->type == PARALLELOGRAM)
		new->dir = vec3_norm(vec3_cross(new->pos2, new->pos3));
	if (new->type == CUBE)
		create_cube(e, new);
	if (new->type == CSG)
		parse_csg(e, new, line);
	(new->type != BBOX && new->type != CUBE) ? new->comp = NULL : 0;
	new->mat.fresnel.defined ? set_fresnel(new) : 0;
	return (new);
}
