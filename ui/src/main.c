/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 11:21:45 by scollon           #+#    #+#             */
/*   Updated: 2016/04/27 13:26:22 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ui.h>

static void	main_init(t_gui *gui)
{
	gui->error = NULL;
	gui->builder = gtk_builder_new();
	gui->loaded_bool = 0;
	if (!gtk_builder_add_from_file(gui->builder, "user.ui", &gui->error))
		error(gui->error->message, NULL, 1);
	if (!(gui->win = gtk_builder_get_object(gui->builder, "main")))
		error("window fail", NULL, 1);
}

int			main(int ac, char **av)
{
	t_gui	*gui;

	gtk_init(&ac, &av);
	if (!(gui = (t_gui*)malloc(sizeof(t_gui))))
		error("Failed to allocate memory area", NULL, 1);
	main_init(gui);
	gtk_main();
	return (EXIT_SUCCESS);
}
