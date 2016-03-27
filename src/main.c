/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 11:54:44 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/27 09:33:46 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		run(GtkButton *button, t_gui *e)
{
	(void)button;
	if (e->loaded == 1)
		core(&e->env);
}

void		load(GtkButton *button, t_gui *e)
{
	(void)button;
	if (e->filename != NULL)
	{
		e->env.arg.file = ft_strdup(e->filename);
		init_env(&e->env);
		parse_yml(&e->env);
		e->loaded = 1;
	}
}

void		check_swith(GObject *button, char *check)
{
	(void)button;
	if (*check == 0)
		*check = 1;
	else
		*check = 0;
	g_print("%d", (int)*check);
}

void		get_file_name(GObject *load_area, t_gui *e)
{
	GtkFileChooser	*tmp;

	tmp = GTK_FILE_CHOOSER(load_area);
	e->filename = gtk_file_chooser_get_filename(tmp);
	if (e->filename == NULL)
		error("something", NULL, 1);
}

int			main(int ac, char **av)
{
	t_gui	*e;

	gtk_init(&ac, &av);
	e = (t_gui*)malloc(sizeof(t_gui));
	e->error = NULL;
	e->filename = NULL;
	e->resync = 0;
	e->mouse_inter = 0;
	e->builder = gtk_builder_new();
	e->env.mlx = mlx_init();
	e->env.arg.w = 1200;
	e->env.arg.h = 800;
	e->loaded = 0;
	if (!gtk_builder_add_from_file(e->builder, "user.ui", &e->error))
		error(e->error->message, NULL, 1);

// Get Window
	if (!(e->window =
		gtk_builder_get_object(e->builder, "main")))
		error("window fail", NULL, 1);
	gtk_window_set_position(GTK_WINDOW(e->window), GTK_WIN_POS_CENTER_ALWAYS);
	g_signal_connect(e->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

// Get load file area
	if (!(e->load_area =
		gtk_builder_get_object(e->builder, "file_loader_button")))
		error("load area fail", NULL, 1);
	g_signal_connect(e->load_area, "file_set",
	G_CALLBACK(get_file_name), (gpointer*)e);

//Get resync button
	if (!(e->resync_button =
		gtk_builder_get_object(e->builder, "resync_mod_button")))
		error("resync", NULL, 1);
	g_signal_connect(e->resync_button, "toggled",
	G_CALLBACK(check_swith), (gpointer*)&e->resync);

//Get resync button
	if (!(e->mouse_inter_button =
		gtk_builder_get_object(e->builder, "mouse_interpolation_button")))
		error("inter", NULL, 1);
	g_signal_connect(e->mouse_inter_button, "toggled",
	G_CALLBACK(check_swith), (gpointer*)&e->mouse_inter);

	if (!(e->load = gtk_builder_get_object(e->builder, "load_button")))
		error("run", NULL, 1);
	g_signal_connect(e->load, "clicked", G_CALLBACK(load), (gpointer*)e);
	if (!(e->run = gtk_builder_get_object(e->builder, "run_button")))
		error("run", NULL, 1);
	g_signal_connect(e->run, "clicked", G_CALLBACK(run), (gpointer*)e);
	gtk_main();
	return (EXIT_SUCCESS);
}
