/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_yml.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:09:33 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/22 09:02:32 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		is_yml(const char *str)
{
	char	*buffer;

	buffer = ft_strrchr(str, '.');
	if (buffer == NULL)
		return (0);
	if (ft_strcmp(buffer, ".yml") != 0 && ft_strcmp(buffer, ".yaml") != 0)
		return (0);
	return (1);
}

static t_line	*init_list(char *line, t_line *prev)
{
	t_line *new;

	!(new = (t_line*)malloc(sizeof(t_line))) ? error(E_MALLOC, NULL, 1) : 0;
	new->line = ft_strdup(line);
	new->next = NULL;
	new->prev = prev;
	return (new);
}

static char		*get_line(const int fd, t_line *first, char *c1, char *c2)
{
	char	*line;
	t_line	*prev;
	t_line	*cur;

	prev = first;
	cur = first;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strncmp(line, c1, ft_strlen(c1)) == 0 ||
			ft_strncmp(line, c2, ft_strlen(c2)) == 0)
			return (line);
		prev = cur;
		cur->next = init_list(line, prev);
		cur = cur->next;
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (NULL);
}

void			parse_yml(t_env *e)
{
	char		*line;
	char		*tmp;
	t_parse		core;

	!is_yml(e->arg.file) ? error(E_IFILE, e->arg.file, 1) : 0;
	if ((e->arg.fd = open(e->arg.file, O_RDWR)) == -1)
		error(strerror(errno), e->arg.file, 1);
	core.cam = init_list("cameras", NULL);
	core.lgt = init_list("lights", NULL);
	core.obj = init_list("objects", NULL);
	while (get_next_line(e->arg.fd, &line) > 0 && ft_strcmp(line, "...") != 0)
	{
		tmp = ft_strdup(line);
		if (ft_strncmp(tmp, "cameras:", 8) == 0 && ft_strdel(&tmp))
			tmp = get_line(e->arg.fd, core.cam, "lights:", "objects:");
		if (ft_strncmp(tmp, "lights:", 7) == 0 && ft_strdel(&tmp))
			tmp = get_line(e->arg.fd, core.lgt, "cameras:", "objects:");
		if (ft_strncmp(tmp, "objects:", 8) == 0 && ft_strdel(&tmp))
			tmp = get_line(e->arg.fd, core.obj, "cameras:", "lights:");
		ft_strdel(&tmp);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(e->arg.fd) == -1 ? error(strerror(errno), e->arg.file, 0) : 0;
	parse(e, &core);
}
