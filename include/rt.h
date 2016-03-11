/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:07:48 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/11 15:35:33 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <libft.h>
# include <libvec.h>
# include <libftprintf.h>
# include <error_ft.h>
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <time.h>

# include <stdio.h> // TEMPORARY

# define ABS(x) (x < 0 ? -x : x)
# define MIN_POS -1000.0
# define MAX_POS 1000.0
# define EPSILON 1e-9
# define MAX_COLOR 32
# define IMG_PATH "./resource/images/"
# define IMG_EXTENSION ".mlx"
# define FILE_ARG O_WRONLY | O_CREAT
# define FILE_RIGHTS S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
# define FILE_NAME_LENGTH 255

enum { SPHERE, CONE, PLANE, CYLINDER };
enum { POINT, SPOT, DIRECTIONAL };
enum { HARD, SOFT };

typedef struct		s_arg
{
	char			*file;
	int				fd;
	int				w;
	int				h;
}					t_arg;

typedef struct		s_img
{
	void			*adr;
	char			*img;
	int				endian;
	int				bpp;
	int				opp;
	int				sl;
	int				w;
	int				h;
}					t_img;

typedef struct		s_mat
{
	t_vec3			color;
	double			ambient;
	double			diffuse;
	double			specular;
	double			shininess;
	double			reflect;
	double			refract;
}					t_mat;

typedef	struct		s_grad
{
	t_vec3			*color;
	float			*pos;
}					t_grad;

typedef struct		s_cam
{
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			rot;
	t_vec3			origin;
	t_grad			gradient;
	t_img			img;
	t_ray			ray;
	int				index;
	double			fov;
	struct s_cam	*prev;
	struct s_cam	*next;
}					t_cam;

typedef struct		s_obj
{
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			normal;
	t_mat			mat;
	short			type;
	double			scale;
	struct s_obj	*next;
}					t_obj;

typedef	struct		s_lgt
{
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			color;
	t_ray			ray;
	int				type;
	int				shadow;
	double			intensity;
	struct s_lgt	*next;
}					t_lgt;

typedef struct		s_reflect
{
	int				depth;
	int				depth_max;
}					t_reflect;

typedef struct		s_refract
{
	int				depth;
	int				depth_max;
}					t_refract;

typedef struct		s_ray
{
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			hit;
}					t_ray;

typedef struct		s_win
{
	void			*adr;
	int				w;
	int				h;
	int				dw;
	int				dh;
}					t_win;

typedef struct		s_env
{
	void			*mlx;
	t_win			win;
	t_arg			arg;
	t_cam			*cam;
	t_obj			*obj;
	t_lgt			*lgt;
	t_ray			ray;
	t_vec3			color;
	t_reflect		reflect;
	t_refract		refract;
	double			(*intersect[6])(struct s_env *, t_ray, t_obj *);
}					t_env;

/*
**	parse.c
*/

void				parse(t_env *e);
void				parse_gradient(t_env *e, char *str);
t_vec3				parse_vector(const char *line);
int					parse_load(t_env *e, int ac, char **av, int i);

/*
**	create_camera.c
*/

void				parse_camera(t_env *e, char *str);
t_cam				*create_camera(t_env *e, t_cam *prev);

/*
**	create_light.c
*/

void				parse_lights(t_env *e, char *str);
t_lgt				*create_light(t_env *e, char *type);

/*
**	create_object.c
*/

void				parse_objects(t_env *e, char *str);
t_obj				*create_object(t_env *e, char *type);

/*
**	raytracing.c
*/

void				raytracing(t_env *e);
void				raytracing_init(t_env *e);
t_vec3				raytracing_draw(t_env *e, t_ray ray);
t_vec3				raytracing_reflect(t_env *e, t_ray ray, t_obj *obj);
t_vec3				raytracing_refract(t_env *e, t_ray ray, t_obj *obj);

/*
**	raytracing_intersect.c
*/

t_obj				*ray_intersect(t_env *e, t_ray ray, double *tmin, double *t);

/*
**	draw.c
*/

t_img			img_init(t_env *e, int w, int h);
void			img_pixel_put(t_env *e, int x, int y, t_vec3 color);
void			img_pixel_put_hex(t_env *e, int x, int y, int hex);
t_vec3			hex_vec3(const int hex);

/*
**	utils.c
*/

int					str_digit(char *str);

/*
**	core.c
*/

void				core(t_env *e);

/*
**	hook.c
*/

int					loop_hook(t_env *e);
int					expose_hook(t_env *e);
int					key_pressed(int keycode,t_env *e);

/*
**	viewer_export.c
*/

void				viewer_export(t_env *e, t_img *img);

#endif
