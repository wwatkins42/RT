/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aacuna <aacuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 11:27:53 by aacuna            #+#    #+#             */
/*   Updated: 2016/05/03 11:37:12 by aacuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	get_point(char *line, t_obj *parent)
{
	int		i;
	t_vec3	result;

	i = 0;
	while ((!ft_isdigit(line[i]) && line[i] != '-') && line[i])
		i++;
	result.x = ft_atof(line + i) * parent->scale;
	while (ft_isdigit(line[i]) || line[i] == '.' || line[i] == ','
			|| line[i] == '-' || line[i] == 'E')
		i++;
	while ((!ft_isdigit(line[i]) && line[i] != '-') && line[i])
		i++;
	result.y = ft_atof(line + i) * parent->scale;
	while (ft_isdigit(line[i]) || line[i] == '.' || line[i] == ','
			|| line[i] == '-' || line[i] == 'E')
		i++;
	while ((!ft_isdigit(line[i]) && line[i] != '-')
			&& line[i])
		i++;
	result.z = ft_atof(line + i) * parent->scale;
	result = vec3_add(result, parent->pos);
	return (result);
}

t_vec3	*increase_size(t_env *e, t_vec3 *original, int *size)
{
	t_vec3	*new;
	int		increment;

	increment = 1000;
	*size = *size + increment;
	if (!(new = (t_vec3*)malloc(sizeof(*new) * (*size))))
		error(e, E_MALLOC, NULL, 1);
	ft_memcpy(new, original, sizeof(*original) * (*size - increment));
	free(original);
	return (new);
}

t_obj	*parse_points(t_env *e, int fd, t_obj *parent)
{
	int		size;
	t_vec3	*points;
	int		i;
	char	*line;

	size = 1000;
	if (!(points = (t_vec3*)malloc(sizeof(*points) * 1000)))
		error(e, E_MALLOC, NULL, 1);
	i = 1;
	while (get_next_line(fd, &line) > 0)
	{
		i >= size - 1 ? points = increase_size(e, points, &size) : 0;
		if (line[0] == 'v' && line[1] == ' ')
		{
			points[i] = get_point(line, parent);
			i++;
		}
		else if (line[0] == 'f' && line[1] == ' ')
			if (!(parent->comp = add_triangle(line, points, parent, i - 1)))
				error(e, E_MALLOC, NULL, 1);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	free(points);
	return (parent);
}

t_obj	*parse_obj(char *file, t_env *e, t_obj *parent)
{
	int		fd;
	t_obj	*new_box_size;
	char	*trim;

	parent->type = BBOX;
	trim = ft_strtrim(file);
	(fd = open(trim, O_RDONLY)) == -1 ? error(e, strerror(errno), trim, 1) : 0;
	free(trim);
	parse_points(e, fd, parent);
	if (parent->comp)
	{
		new_box_size = create_bbox(parent->comp, e);
		parent->pos = new_box_size->pos;
		parent->pos2 = new_box_size->pos2;
		free(new_box_size);
		parent = divide_bbox(parent, e);
		e->count.obj = e->count.obj + count_objs(parent) - 1;
		close(fd);
	}
	return (parent);
}
