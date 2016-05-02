/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 16:31:16 by tbeauman          #+#    #+#             */
/*   Updated: 2016/05/02 18:15:22 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	intersect_triangle(t_ray *ray, t_obj *t)
{
	t_vec3		e1;
	t_vec3		e2;
	t_triangle	tri;
	double		intersection;

	e1 = vec3_sub(t->pos2, t->pos);
	e2 = vec3_sub(t->pos3, t->pos);
	tri.p = vec3_cross(ray->dir, e2);
	tri.det = vec3_dot(e1, tri.p);
	if (tri.det > -EPSILON && tri.det < EPSILON)
		return (INFINITY);
	tri.vertex_camera_direction = vec3_sub(ray->pos, t->pos);
	tri.u = vec3_dot(tri.vertex_camera_direction, tri.p) * (1 / tri.det);
	if (tri.u < 0 || tri.u > 1)
		return (INFINITY);
	tri.q = vec3_cross(tri.vertex_camera_direction, e1);
	tri.v = vec3_dot(ray->dir, tri.q) * (1 / tri.det);
	if (tri.v < 0 || (tri.u + tri.v) > 1)
		return (INFINITY);
	intersection = vec3_dot(e2, tri.q) * (1 / tri.det);
	if (intersection > EPSILON)
		return (intersection);
	return (INFINITY);
}

t_vec3	point_at_pos(t_vec3 *vect, int pos, int max, char sign)
{
	if (sign == '-')
		pos = max - pos;
	if (pos <= max && pos >= 0)
		return (vect[pos]);
	else
		return ((t_vec3){0, 0, 0});
}

int		next_number(char *line, int i)
{
	while (ft_isdigit(line[i]) || line[i] == '/' || line[i] == '-')
		i++;
	while (!ft_isdigit(line[i]) && line[i])
		i++;
	return (i);
}

t_obj	*add_triangle(char *line, t_vec3 *vect, t_obj *parent, int max)
{
	t_vec3	p1;
	t_vec3	p2;
	t_vec3	p3;
	int		i;

	i = 0;
	i = next_number(line, i);
	p1 = point_at_pos(vect, ft_atoi(line + i), max, line[i - 1]);
	i = next_number(line, i);
	p2 = point_at_pos(vect, ft_atoi(line + i), max, line[i - 1]);
	i = next_number(line, i);
	p3 = point_at_pos(vect, ft_atoi(line + i), max, line[i - 1]);
	parent->comp = new_triangle_node(p1, p2, p3, parent);
	while (line[i])
	{
		i = next_number(line, i);
		if (line[i])
			parent->comp = new_triangle_node(p1, parent->comp->pos3,
										vect[ft_atoi(line + i)], parent);
	}
	return (parent->comp);
}

t_obj	*new_triangle_node(t_vec3 p1, t_vec3 p2, t_vec3 p3, t_obj *parent)
{
	t_obj	*result;

	result = (t_obj*)malloc(sizeof(*result));
	if (!result)
	{
		ft_putstr("MALLOC ERROR\n");
		exit (1);
//		error(E_MALLOC, NULL, 1); DOES NOT COMPILE : too few arguments to function call
	}
	default_object(result);
	result->type = TRIANGLE;
	result->pos = p1;
	result->pos2 = p2;
	result->pos3 = p3;
	result->mat = parent->mat;
	result->dir = vec3_norm(vec3_cross(vec3_sub(result->pos2, result->pos),
										vec3_sub(result->pos3, result->pos)));
	result->normal = result->dir;
	result->next = parent->comp;
	return (result);
}
