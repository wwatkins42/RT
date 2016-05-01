/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 13:54:26 by scollon           #+#    #+#             */
/*   Updated: 2016/05/01 19:34:03 by tbeauman         ###   ########.fr       */
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
	object->dir = vec3(0, 1, 0);
	object->cut = vec3(0, 0, 0);
	object->rot = vec3(0, 0, 0);
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

int			get_object_type(char *line)
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
	else if (ft_strstr(line, "CHEWINGGUM"))
		return (CHEWINGGUM);
	else if (ft_strstr(line, "CUBE_TROUE"))
		return (CUBE_TROUE);
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
	else if (ft_strstr(line, "QUADRIC"))
		return (QUADRIC);
	else if (ft_strstr(line, "MOEBIUS"))
		return (MOEBIUS);
	else if (ft_strstr(line, "DISC"))
		return (DISC);
	else if (ft_strstr(line, "CSG"))
		return (CSG);
	else if (ft_strstr(line, "OBJ"))
		return (BBOX);
	else
		error(E_OTYPE, line, 0);
	return (SPHERE);
}

void			fill_object_attr(t_env *e, t_line *line, t_obj *new)
{
	if (ft_strstr(line->line, "type:"))
		new->type = get_object_type(line->line);
	else if (ft_strstr(line->line, "pos:"))
		new->pos = parse_vector(line->line);
	else if (ft_strstr(line->line, "pos2:"))
		new->pos2 = parse_vector(ft_strchr(line->line, ':'));
	else if (ft_strstr(line->line, "pos3:"))
		new->pos3 = vec3_norm(parse_vector(ft_strchr(line->line, ':')));
	else if (ft_strstr(line->line, "dir:"))
		new->dir = vec3_norm(parse_vector(line->line));
	else if (ft_strstr(line->line, "rot:"))
		new->rot = parse_vector(line->line);
	else if (ft_strstr(line->line, "cut:"))
		new->cut = parse_vector(line->line);
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

void create_cube(t_obj *cube)
{
        double  k;

        !(cube->comp = malloc(6 * sizeof(t_obj))) ? error(E_MALLOC, NULL, 0) : 0;
        k = cube->scale;
        cube->comp[0].pos = vec3_sub(cube->pos, vec3(-k / 2, -k / 2, -k / 2));
        cube->comp[0].pos2 = vec3_add(cube->comp[0].pos, (t_vec3) {k, 0, 0});
        cube->comp[0].pos3 = vec3_add(cube->comp[0].pos, (t_vec3) {0, k, 0});
        cube->comp[0].dir = vec3(0,0,-1);//vec3_norm(vec3_cross(cube->comp[0].pos2, cube->comp[0].pos3));
        cube->comp[1].pos = vec3_add(cube->comp[0].pos, (t_vec3) {k, 0, 0});
        cube->comp[1].pos2 = vec3_add(cube->comp[1].pos, (t_vec3) {0, 0, k});
        cube->comp[1].pos3 = vec3_add(cube->comp[1].pos, (t_vec3) {0, k, 0});
        cube->comp[1].dir = vec3(1,0,0);//vec3_norm(vec3_cross(cube->comp[1].pos2, cube->comp[1].pos3));
        cube->comp[2].pos = vec3_add(cube->comp[0].pos, (t_vec3) {0, 0, k});
        cube->comp[2].pos2 = vec3_add(cube->comp[2].pos, (t_vec3) {0, 0, -k});
        cube->comp[2].pos3 = vec3_add(cube->comp[2].pos, (t_vec3) {0, k, 0});
        cube->comp[2].dir = vec3(-1,0,0);//vec3_norm(vec3_cross(cube->comp[2].pos2, cube->comp[2].pos3));
        cube->comp[3].pos = vec3_add(cube->comp[0].pos, (t_vec3) {0, k, 0});
        cube->comp[3].pos2 = vec3_add(cube->comp[3].pos, (t_vec3) {k, 0, 0});
        cube->comp[3].pos3 = vec3_add(cube->comp[3].pos, (t_vec3) {0, 0, k});
        cube->comp[3].dir = vec3(0,1,0);//vec3_norm(vec3_cross(cube->comp[3].pos2, cube->comp[3].pos3));
        cube->comp[4].pos = cube->comp[0].pos;
        cube->comp[4].pos2 = vec3_add(cube->comp[4].pos, (t_vec3) {k, 0, 0});
        cube->comp[4].pos3 = vec3_add(cube->comp[4].pos, (t_vec3) {0, 0, k});
        cube->comp[4].dir = vec3(0,-1,0);//vec3_norm(vec3_cross(cube->comp[4].pos2, cube->comp[4].pos3));
        cube->comp[5].pos = vec3_add(cube->comp[0].pos, (t_vec3) {k, 0, k});
        cube->comp[5].pos2 = vec3_add(cube->comp[5].pos, (t_vec3) {-k, 0, 0});
        cube->comp[5].pos3 = vec3_add(cube->comp[5].pos, (t_vec3) {0, k, 0});
        cube->comp[5].dir = vec3(0,0,1);//vec3_norm(vec3_cross(cube->comp[5].pos2, cube->comp[5].pos3));
}


t_obj				*create_object(t_env *e, t_line *object_line)
{
	t_obj		*new;
	t_line		*line;

	line = object_line;
	!(new = (t_obj*)malloc(sizeof(t_obj))) ? error(E_OINIT, NULL, 1) : 0;
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
		create_normal_map(new);
	new->scale2 = new->scale * new->scale;
	new->pr *= new->pr;
	new->gr *= new->gr;
	new->k = tan(new->scale) * tan(new->scale);
	if (new->type == TRIANGLE || new->type == PARALLELOGRAM)
		new->dir = vec3_norm(vec3_cross(new->pos2, new->pos3));
	if (new->type == CUBE)
		create_cube(new);
	if (new->type == CSG)
		parse_csg(e, new, line);
	(new->type != BBOX && new->type != CUBE) ? new->comp = NULL : 0;
	new->mat.fresnel.defined ? set_fresnel(new) : 0;
	return (new);
}
