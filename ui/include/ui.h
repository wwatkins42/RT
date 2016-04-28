/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 11:17:38 by scollon           #+#    #+#             */
/*   Updated: 2016/04/27 11:56:19 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include <gtk/gtk.h>
# include <pthread.h>
# include <libftprintf.h>
# include <libft.h>
# include <stdlib.h>
# include <unistd.h>

# define ERR_FILE_FLAGS O_WRONLY | O_CREAT | O_APPEND
# define ERR_FILE_RIGHTS S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH


typedef struct		s_gui
{
	GtkBuilder	*builder;
	GObject		*win;

	GObject		*fchooser;
	GObject		*load_button;
	GObject		*pbar;
	char		loaded_bool;

	GObject		*resync_button;
	GObject		*mouse_inter_button;

	GObject		*run_button;

	GError		*error;
}					t_gui;


void				error(char *type, char *esrc, short ext);

#endif
