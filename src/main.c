/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 11:54:44 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/27 11:28:07 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	main_init(t_env *e)
{
	e->gui->error = NULL;
	e->gui->builder = gtk_builder_new();
	e->mlx = mlx_init();
	e->arg.file = NULL;
	e->arg.w = 1200;
	e->arg.h = 800;
	e->gui->loaded = 0;
	if (!gtk_builder_add_from_file(e->gui->builder, "user.ui", &e->gui->error))
		error(e->gui->error->message, NULL, 1);
	if (!(e->gui->win = gtk_builder_get_object(e->gui->builder, "main")))
		error("window fail", NULL, 1);
	if (!(e->gui->file_chooser =
		gtk_builder_get_object(e->gui->builder, "file_loader_button")))
		error("chooser button fail", NULL, 1);
	if (!(e->gui->resync_button =
		gtk_builder_get_object(e->gui->builder, "resync_mod_button")))
		error("resync", NULL, 1);
	if (!(e->gui->mouse_inter_button =
		gtk_builder_get_object(e->gui->builder, "mouse_interpolation_button")))
		error("inter", NULL, 1);
	if (!(e->gui->load = gtk_builder_get_object(e->gui->builder, "load_button")))
		error("load", NULL, 1);
	if (!(e->gui->run = gtk_builder_get_object(e->gui->builder, "run_button")))
		error("run", NULL, 1);
	if (!(e->gui->pbar = gtk_builder_get_object(e->gui->builder, "pbar")))
		error("pbar", NULL, 1);
	gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(e->gui->pbar), 0.1);
}

int			main(int ac, char **av)
{
	t_env	*e;

	gtk_init(&ac, &av);
	if (!(e = (t_env*)malloc(sizeof(t_env))))
		error("environemment failed", NULL, 1);
	if (!(e->gui = (t_gui*)malloc(sizeof(t_gui))))
		error("user interface can't be load", NULL, 1);
	main_init(e);
	gtk_window_set_position(GTK_WINDOW(e->gui->win), GTK_WIN_POS_CENTER_ALWAYS);
	g_signal_connect(e->gui->win, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(e->gui->file_chooser, "file_set",
	G_CALLBACK(get_file_name), (gpointer*)e);
	// g_signal_connect(e->resync_button, "toggled",
	// G_CALLBACK(check_swith), (gpointer*)e);
	// g_signal_connect(e->gui->mouse_inter_button, "toggled",
	// G_CALLBACK(check_swith), (gpointer*)e);
	g_signal_connect(e->gui->load, "clicked", G_CALLBACK(load_file),
					(gpointer*)e);
	g_signal_connect(e->gui->run, "clicked", G_CALLBACK(run_raytracer),
					(gpointer*)e);
	gtk_main();
	return (EXIT_SUCCESS);
}
