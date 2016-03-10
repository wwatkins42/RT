/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:09:33 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/10 15:13:51 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse(t_env *e)
{
	char	*line;

	if ((e->arg.fd = open(e->arg.file, O_RDWR)) == -1)
		error(strerror(errno), NULL, 1);
	ft_strdel(&e->arg.file);
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

void	parse_gradient(t_env *e, char *str)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	if ((e->cam->gradient.color = (t_vec3*)malloc(sizeof(t_vec3) * 32)) == NULL)
		error(E_MALLOC, NULL, 1);
	if ((e->cam->gradient.pos = (float*)malloc(sizeof(float) * 32)) == NULL)
		error(E_MALLOC, NULL, 1);
	str = ft_strstr(str, ".");
	str[ft_strlen(str) - 1] = '\0';
	if ((fd = open(str, O_RDWR)) == -1)
		error(strerror(errno), str, 1);
	while (i < MAX_COLOR && get_next_line(fd, &line) > 0)
	{
		if (ft_strstr(line, "color:"))
		{
			e->cam->gradient.pos[i] = ft_atof(ft_strstr(line, "pos:") + 4);
			line[ft_strchr(line, ',') - line] = '\0';
			e->cam->gradient.color[i] = hex_vec3(ft_atoi_base(line, 16));
		}
		i++;
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

t_vec3	parse_vector(const char *line)
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
			if (tab[i][0] == 'x')
				vec3.x = ft_atof(tab[i + 1]);
			else if (tab[i][0] == 'y')
				vec3.y = ft_atof(tab[i + 1]);
			else if (tab[i][0] == 'z')
				vec3.z = ft_atof(tab[i + 1]);
		}
		ft_strdel(&tab[i]);
	}
	vec3_clamp(&vec3, MIN_POS, MAX_POS);
	ft_memdel((void**)tab);
	return (vec3);
}

// int		parse_load(t_env *e, int ac, char **av, int i)
// {
// 	t_view	*prev;
// 	t_view	*current;
//
// 	e->win.w = 0;
// 	e->win.h = 0;
// 	if (!(current = (t_view*)malloc(sizeof(t_view))))
// 		error(E_MALLOC, NULL, 1);
// 	e->viewer = current;
// 	prev = NULL;
// 	while (++i < ac && av[i][0] != '-')
// 	{
// 		current->prev = prev;
// 		e->arg.viewer_path = ft_strdup(av[i]);
// 		printf("%s\n", e->arg.viewer_path);
// 		current->img = viewer_import(e);
// 		current->img.w > e->win_v.w ? e->win_v.w = current->img.w : 0;
// 		current->img.h > e->win_v.h ? e->win_v.h = current->img.h : 0;
// 		prev = current;
// 		if (i + 1 < ac && av[i + 1][0] != '-')
// 		{
// 			if (!(current->next = (t_view*)malloc(sizeof(t_view))))
// 				error(E_MALLOC, NULL, 1);
// 			current = current->next;
// 		}
// 	}
// 	current->next = NULL;
// 	return (i - 1);
// }
