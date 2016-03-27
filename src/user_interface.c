/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/27 10:12:26 by scollon           #+#    #+#             */
/*   Updated: 2016/03/27 11:50:07 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		run_raytracer(GtkButton *button, t_env *e)
{
	(void)button;
	if (e->gui->loaded == 1)
		core(e);
}

void		load_file(GtkButton *button, t_env *e)
{
	(void)button;
	if (e->arg.file != NULL)
	{
		init_env(e);
		pthread_create(&e->thread1, NULL, (void*)parse_yml, e);
		//fill_progress_bar(e);
		pthread_join(e->thread1, NULL);
		e->gui->loaded = 1;
	}
}

void		check_swith(GObject *button, char *check)
{
	(void)button;
	if (*check == 0)
		*check = 1;
	else
		*check = 0;
}

void		get_file_name(GtkFileChooser *file_chooser, t_env *e)
{
	e->arg.file != NULL ? ft_strdel(&e->arg.file) : 0;
	e->arg.file = ft_strdup(gtk_file_chooser_get_filename(file_chooser));
	if (e->arg.file == NULL)
		error("something", NULL, 1);
}

void		fill_progress_bar(t_env *e)
{
	gdouble	new_value;

	new_value = 0;
	while (new_value != 1.0)
	{
		new_value += 0.1;
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(e->gui->pbar), new_value);
	}
}
