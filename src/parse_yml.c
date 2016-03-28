/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_yml.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:09:33 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/28 13:59:32 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_line	*init_list(char *line, t_line *prev)
{
	t_line *new;

	!(new = (t_line*)malloc(sizeof(t_line))) ? error(E_MALLOC, NULL, 1) : 0;
	new->line = ft_strdup(line);
	new->next = NULL;
	new->prev = prev;
	return (new);
}

static int		get_condition(int line_type, char *line)
{
	if (line_type == 0)
	{
		return (ft_strncmp(line, "cameras:", 8) == 0 ||
				ft_strncmp(line, "lights:", 7) == 0 ||
				ft_strncmp(line, "objects:", 8) == 0);
	}
	else if (line_type == 1)
	{
		return (ft_strncmp(line, "scenes:", 6) == 0 ||
				ft_strncmp(line, "lights:", 7) == 0 ||
				ft_strncmp(line, "objects:", 8) == 0);
	}
	else if (line_type == 2)
	{
		return (ft_strncmp(line, "cameras:", 8) == 0 ||
				ft_strncmp(line, "scenes:", 6) == 0 ||
				ft_strncmp(line, "objects:", 8) == 0);
	}
	else
	{
		return (ft_strncmp(line, "cameras:", 8) == 0 ||
				ft_strncmp(line, "lights:", 7) == 0 ||
				ft_strncmp(line, "scenes:", 6) == 0);
	}
}

static char		*get_line(const int fd, t_line *first, int line_type)
{
	char	*line;
	t_line	*prev;
	t_line	*cur;

	prev = first;
	cur = first;
	while (get_next_line(fd, &line) > 0)
	{
		if (get_condition(line_type, line))
			return (line);
		if (!is_comment(line))
		{
			prev = cur;
			cur->next = init_list(line, prev);
			cur = cur->next;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (NULL);
}

static void		parse_loop(const int fd, t_parse *core)
{
	char		*tmp;
	char		*line;

	while (get_next_line(fd, &line) > 0 && ft_strcmp(line, "...") != 0)
	{
		tmp = ft_strdup(line);
		if (ft_strncmp(tmp, "scene:", 6) == 0 && ft_strdel(&tmp))
			tmp = get_line(fd, core->scene, 0);
		if (ft_strncmp(tmp, "cameras:", 8) == 0 && ft_strdel(&tmp))
			tmp = get_line(fd, core->cam, 1);
		if (ft_strncmp(tmp, "lights:", 7) == 0 && ft_strdel(&tmp))
			tmp = get_line(fd, core->lgt, 2);
		if (ft_strncmp(tmp, "objects:", 8) == 0 && ft_strdel(&tmp))
			tmp = get_line(fd, core->obj, 3);
		ft_strdel(&tmp);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

void			parse_yml(t_env *e)
{
	t_parse		core;

	if ((e->arg.fd = open(e->arg.file, O_RDWR)) == -1)
		error(strerror(errno), e->arg.file, 1);
	core.scene = init_list("scene", NULL);
	core.cam = init_list("cameras", NULL);
	core.lgt = init_list("lights", NULL);
	core.obj = init_list("objects", NULL);
	parse_loop(e->arg.fd, &core);
	close(e->arg.fd) == -1 ? error(strerror(errno), e->arg.file, 0) : 0;
	parse(e, &core);
}
