/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:20:55 by scollon           #+#    #+#             */
/*   Updated: 2016/03/11 11:20:29 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWER_H
# define VIEWER_H

# include <libft.h>
# include <libftprintf.h>
# include <mlx.h>
# include <error_ft.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_img
{
	void			*adr;
	char			*img;
	int				bpp;
	int				sl;
	int				endian;
	int				opp;
	int				w;
	int				h;

}					t_img;

typedef struct		s_win
{
	void			*adr;
	int				w;
	int				h;
}					t_win;

typedef struct		s_view
{
	t_img			img;
	struct s_view	*prev;
	struct s_view	*next;
}					t_view;

typedef struct		s_env
{
	void			*mlx;
	t_win			win;
	t_view			*head_viewer;
	t_view			*tail_viewer;
	t_view			*current;
	char			*viewer_path;
}					t_env;

t_img				viewer_import(t_env *e);
int					expose_hook(t_env *e);
int					key_pressed(int kc, t_env *e);
int					loop_hook(t_env *e);
void				img_iter(t_env *e, void (*f)(char *, char *, char *));
void				invert(char *r, char *g, char *b);

#endif
