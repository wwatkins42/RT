/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:09:33 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/17 10:28:59 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			parse(t_env *e)
{
	char	*line;

	if ((e->arg.fd = open(e->arg.file, O_RDWR)) == -1)
		error(strerror(errno), e->arg.file, 1);
	while (get_next_line(e->arg.fd, &line) > 0 && ft_strcmp(line, "...") != 0)
	{
		if (ft_strstr(line, "cameras:"))
			parse_camera(e, line);
		else if (ft_strstr(line, "lights:"))
			parse_lights(e, line);
		else if (ft_strstr(line, "objects:"))
			parse_objects(e, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

void			parse_gradient(t_cam *cam, char *str)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	if ((cam->gradient.color = (t_vec3*)malloc(sizeof(t_vec3) * 32)) == NULL)
		error(E_MALLOC, NULL, 1);
	if ((cam->gradient.pos = (float*)malloc(sizeof(float) * 32)) == NULL)
		error(E_MALLOC, NULL, 1);
	str = ft_strstr(str, ".");
	str[ft_strlen(str) - 1] = '\0';
	if ((fd = open(str, O_RDWR)) == -1)
		error(strerror(errno), str, 1);
	while (i < MAX_COLOR && get_next_line(fd, &line) > 0)
	{
		if (ft_strstr(line, "color:"))
		{
			cam->gradient.pos[i] = ft_atof(ft_strstr(line, "pos:") + 4);
			line[ft_strchr(line, ',') - line] = '\0';
			cam->gradient.color[i] = hex_vec3(ft_atoi_base(line, 16));
		}
		i++;
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

static short	get_texture_type(const char *line)
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

void			parse_texture(t_obj *obj, const char *line)
{
	short		type;

	type  = get_texture_type(line);
	if (type == NONE)
		return ;
	else if (type == BMP)
		obj->mat.texture = bmp_importer(ft_strstr(line, ":") + 2);
	else
		obj->mat.texture = texture_generator(type, T_RES_W, T_RES_H);
}

t_vec3			parse_vector(const char *line)
{
	int		i;
	char	**tab;
	t_vec3	vec3;

	i = -1;
	vec3 = (t_vec3) { 0, 0, 0 };
	tab = ft_strsplit(line, ' ');
	while (tab[++i] != NULL)
	{
		if (tab[i + 1] != NULL)
		{
			if (tab[i][1] == 'x')
				vec3.x = ft_atof(tab[i + 1]);
			if (tab[i][0] == 'y')
				vec3.y = ft_atof(tab[i + 1]);
			if (tab[i][0] == 'z')
				vec3.z = ft_atof(tab[i + 1]);
		}
		ft_strdel(&tab[i]);
	}
	vec3_clamp(&vec3, MIN_POS, MAX_POS);
	ft_memdel((void**)tab);
	return (vec3);
}
