/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aacuna <aacuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 11:27:53 by aacuna            #+#    #+#             */
/*   Updated: 2016/04/29 12:26:38 by aacuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	get_point(char *line)
{
	int		i;
	t_vec3	result;

	i = 0;
	while ((!ft_isdigit(line[i]) && line[i] != '-') && line[i])
		i++;
	result.x = ft_atof(line + i);
	while (ft_isdigit(line[i]) || line[i] == '.' || line[i] == ','
			|| line[i] == '-' || line[i] == 'E')
		i++;
	while ((!ft_isdigit(line[i]) && line[i] != '-') && line[i])
		i++;
	result.y = ft_atof(line + i);
	while (ft_isdigit(line[i]) || line[i] == '.' || line[i] == ','
			|| line[i] == '-' || line[i] == 'E')
		i++;
	while ((!ft_isdigit(line[i]) && line[i] != '-')
			&& line[i])
		i++;
	result.z = ft_atof(line + i);
	return (result);
}

t_obj	*parse_line(char *line, t_vec3 *tmp_array, t_obj *parent, int *i)
{
	t_vec3	res;

	if (line[0] == 'v' && line[1] == ' ')
	{
		res = get_point(line);
		tmp_array[*i] = res;
		(*i)++;
	}
	else if (line[0] == 'f' && line[1] == ' ')
		parent->comp = add_triangle(line, tmp_array, parent, *i);
	return (parent->comp);
}

t_vec3	*increase_size(t_vec3 *original, int *size)
{
	t_vec3	*new;
	int		increment;

	increment = 1000;
	*size = *size + increment;
	new = (t_vec3*)malloc(sizeof(*new) * (*size));
	ft_memcpy(new, original, sizeof(*original) * (*size - increment));
	free(original);
	return (new);
}

t_obj	*parse_obj(char *file, t_env *e, t_obj *parent)
{
	int		fd;
	t_vec3	*points;
	int		i;
	int		size;
	t_obj	*new_box_size;

	parent->type = BBOX;
	(fd = open(file, O_RDONLY)) == -1 ? error(strerror(errno), file, 1) : 0;
	i = 1;
	size = 1000;
	points = (t_vec3*)malloc(sizeof(*points) * 1000);
	while (get_next_line(fd, &file))
	{
		i >= size - 1 ? points = increase_size(points, &size) : 0;
		parent->comp = parse_line(file, points, parent, &i);
		ft_strdel(&file);
	}
	new_box_size = create_bbox(parent->comp);
	parent->pos = new_box_size->pos;
	parent->pos2 = new_box_size->pos2;
	free(new_box_size);
	parent = divide_bbox(parent);
	e->count.obj = e->count.obj + count_objs(parent) - 1;
	close(fd);
	return (parent);
}
