/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aacuna <aacuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 11:27:53 by aacuna            #+#    #+#             */
/*   Updated: 2016/04/27 13:46:09 by aacuna           ###   ########.fr       */
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

t_obj	*parse_line(char *line, t_vec3 *tmp_array, t_obj *obj, int *i)
{
	t_vec3	res;

	if (line[0] == 'v' && line[1] == ' ')
	{
		res = get_point(line);
		tmp_array[*i] = res;
		(*i)++;
	}
	else if (line[0] == 'f' && line[1] == ' ')
		obj = add_triangle(line, tmp_array, obj, *i);
	return (obj);
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

t_obj	*parse_obj(char *file, t_env *e)
{
	int		fd;
	t_obj	*obj;
	t_vec3	*points;
	int		i;
	int		size;

	obj = NULL;
	if ((fd = open(file, O_RDONLY)) == -1)
		error(strerror(errno), file, 1);
	i = 1;
	size = 1000;
	points = (t_vec3*)malloc(sizeof(*points) * 1000);
	while (get_next_line(fd, &file))
	{
		if (i >= size - 1)
			points = increase_size(points, &size);
		obj = parse_line(file, points, obj, &i);
	}
	obj = create_bbox(obj);
	obj = divide_bbox(obj);
	e->count.obj = count_objs(obj);
	close(fd);
	return (obj);
}
