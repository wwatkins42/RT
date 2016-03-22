/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:07:48 by wwatkins          #+#    #+#             */
/*   Updated: 2016/03/22 14:21:40 by wwatkins         ###   ########.fr       */
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
# include <bmp_exporter.h>
# include <stdio.h> // TEMPORARY

# define ABS(x) (x < 0 ? -x : x)
# define MIN_POS -1000.0
# define MAX_POS 1000.0
# define EPSILON 1e-9
# define PIOVER4 0.78539816
# define MAX_COLOR 32
# define IMG_PATH "./resource/images/"
# define IMG_EXTENSION ".mlx"
# define FILE_ARG O_WRONLY | O_CREAT
# define FILE_RIGHTS S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
# define FILE_NAME_LENGTH 255
# define T_RES_W 2560
# define T_RES_H 1440

enum { SPHERE, CONE, PLANE, CYLINDER };
enum { POINT, SPOT, DIRECTIONAL };
enum { NONE, MARBLE, WOOD, EARTH, BMP };
enum { HARD, SOFT };

typedef struct		s_arg
{
	char			*file;
	int				fd;
	int				w;
	int				h;
}					t_arg;

typedef struct		s_key
{
	short			ku;
	short			kd;
	short			kl;
	short			kr;
	short			i;
	short			k;
	short			j;
	short			l;
	char			mouse;
	short			debug;
	short			invert;
	short			gray_scale;
	short			gamma_m;
	short			gamma_p;
}					t_key;

typedef struct		s_mouse
{
	t_vec3			pos;
	double			sensibility;
}					t_mouse;

typedef struct		s_texture
{
	t_vec3			**img;
	t_vec3			**bump;
	t_vec3			normal;
	int				w;
	int				h;
	int				sl;
	short			bpp;
	short			opp;
	short			type;
	short			filtering;
	short			defined;
	short			normal_map;
}					t_texture;

typedef struct		s_noise
{
	double			*noise;
	int				w_max;
	int				h_max;
	int				len;
	int				pas;
	int				octave;
}					t_noise;

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

typedef struct		s_filter
{
	t_img			img;
	char			invert;
	char			gray_scale;
	double			gamma;
}					t_filter;

typedef struct		s_mat
{
	t_vec3			color;
	t_texture		texture;
	double			ambient;
	double			diffuse;
	double			specular;
	double			shininess;
	double			reflect;
	double			refract;
	double			transparency;
	double			absorbtion;
	short			shadow;
}					t_mat;

typedef struct		s_ray
{
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			hit;
	double			refract_index;
}					t_ray;

typedef struct		s_aa
{
	int				supersampling;
	double			inc;
	double			coef;
}					t_aa;

typedef struct		s_cam
{
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			origin;
	t_img			img;
	t_ray			ray;
	t_filter		filter;
	t_aa			aa;
	int				index;
	double			xa;
	double			ya;
	double			fov;
	double			dist;
	struct s_cam	*prev;
	struct s_cam	*next;
}					t_cam;

typedef struct		s_calc
{
	double			a;
	double			b;
	double			c;
	double			disc;
	double			eq;
	t_vec3			len;
}					t_calc;

typedef struct		s_bfi
{
	int				x;
	int				y;
	double			ur;
	double			vr;
	double			uo;
	double			vo;
	t_vec3			c[4];
}					t_bfi;

typedef struct		s_obj
{
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			normal;
	t_mat			mat;
	short			type;
	double			scale;
	double			scale2;
	double			k;
	double			t;
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
	double			attenuation;
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
	double			n1;
	double			n2;
}					t_refract;

typedef struct		s_count
{
	int				cam;
	int				lgt;
	int				obj;
}					t_count;

typedef struct		s_scene
{
	short			resync;
	short			percent;
	double			velocity;
}					t_scene;

typedef struct		s_win
{
	void			*adr;
	int				w;
	int				h;
	int				dw;
	int				dh;
}					t_win;

typedef struct		s_line
{
	char			*line;
	struct s_line	*next;
	struct s_line	*prev;
}					t_line;

typedef struct		s_parse
{
	t_line			*scene;
	t_line			*cam;
	t_line			*obj;
	t_line			*lgt;
}					t_parse;

typedef struct		s_env
{
	void			*mlx;
	t_win			win;
	t_arg			arg;
	t_key			key;
	t_mouse			mouse;
	t_scene			scene;
	t_count			count;
	t_cam			*cam;
	t_obj			*obj;
	t_lgt			*lgt;
	t_ray			ray;
	t_vec3			color;
	t_reflect		reflect;
	t_refract		refract;
	double			(*intersect[10])(t_ray *, t_obj *);
}					t_env;

/*
**	PARSING FUNCTIONS
*/

void				parse_yml(t_env *e);
void				parse(t_env *e, t_parse *core);
t_cam				*parse_camera(t_env *e, t_line *cam_line);
t_lgt				*parse_light(t_env *e, t_line *light_line);
t_obj				*parse_object(t_env *e, t_line *object_line);
double				parse_value(const char *line, double min, double max);
t_vec3				parse_vector(const char *line);
t_vec3				parse_color(char *line);
void				parse_material(t_env *e, t_mat *mat, t_line *line);

/*
**	ENVIRONNEMENT INIT FUNCTIONS
*/

void				init_env(t_env *e);
void				init_cam(t_env *e, t_cam *cam);
void				init_key(t_env *e);

/*
**	CORE FUNCTIONS
*/

void				core(t_env *e);
int					loop_hook(t_env *e);
int					expose_hook(t_env *e);
int					key_pressed(int keycode, t_env *e);
int					key_released(int keycode, t_env *e);
int					mouse_pos(int x, int y, t_env *e);

/*
**	MOVEMENT FUNCTIONS
*/

void				move_translate(t_env *e);
void				move_rotate(t_env *e);
void				mouse_orientation(t_env *e);

/*
**	RAYTRACING FUNCTIONS
*/

/*
**			Main functions
*/

void				raytracing(t_env *e);
void				raytracing_init(t_env *e, float x, float y);
t_vec3				raytracing_draw(t_env *e, t_ray ray);

/*
**			Primitives intersections
*/

t_obj				*intersect_object(t_env *e, t_ray *ray, double *tmin);
double				intersect_plane(t_ray *ray, t_obj *obj);
double				intersect_sphere(t_ray *ray, t_obj *obj);
double				intersect_cone(t_ray *ray, t_obj *obj);
double				intersect_cylinder(t_ray *ray, t_obj *obj);
void				set_normal(t_ray *ray, t_obj *obj);

/*
**			Reflection / Refraction
*/

t_vec3				raytracing_reflect(t_env *e, t_ray ray, t_obj *obj);
t_vec3				raytracing_refract(t_env *e, t_ray ray, t_obj *obj);


/*
**			Color and light
*/

t_vec3				raytracing_color(t_env *e, t_ray *ray, t_obj *obj);
t_vec3				set_diffuse(t_obj *obj, t_lgt *light);
t_vec3				set_specular(t_env *e, t_vec3 hit, t_obj *obj, t_lgt *lgt);
void				set_light(t_vec3 hit, t_obj *obj, t_lgt *light);
void				set_shadow(t_env *e, t_vec3 *color, t_lgt lgt, t_obj *obj);
void				supersampling(t_env *e, int x, int y);

/*
**	TEXTURE FUNCTIONS
*/

/*
**			Texture generator && perlin noise
*/

t_texture			texture_generator(int type, int width, int height);
double				noise(t_noise *noise, double x, double y);
t_noise				init_noise_structure(int w, int h, int pas, int octave);

/*
**			Texture mapping
*/

t_vec3				texture_mapping(t_obj *obj, t_vec3 **img, t_vec3 hit);

/*
**			Normal mapping
*/

void				create_normal_map(t_obj *obj);
t_vec3				bump_normal(t_obj *obj, t_ray *ray);


/*
**	IMAGES HANDLES FUNCTIONS
*/

t_img				img_init(t_env *e);
void				img_pixel_put(t_img *img, int x, int y, t_vec3 color);
void				img_pixel_put_hex(t_img *img, int x, int y, int hex);
t_vec3				hex_vec3(const int hex);
int					vec3_hex(const t_vec3 vec);

/*
**	UTILS FUNCTIONS
*/

int					str_digit(char *str);
void				kswitch(char *k);
void				display_info(t_env *e, char *str);
void				display_loading(t_env *e, int u, int v);
void				display_texture(t_env *e, t_vec3 **img, t_texture texture);

/*
**	FILTER FUNCTIONS
*/

void				filter(t_img *img, const t_filter filter);
void				filter_invert(t_vec3 *color);
void				filter_gray_scale(t_vec3 *color);
void				filter_gamma(double gamma, t_vec3 *color);

/*
**	VIEWER
*/

void				viewer_export(t_env *e, t_img *img);

/*
**	BMP IMPORTER / EXPORTER
*/

void				bmp_exporter(t_img image, char *name);
t_texture			bmp_importer(char *file_path);

/*
**	YML EXPORTER
*/

void				yml_exporter(t_env *e, char *name);
void				export_object(const int fd, t_env *e);
void				export_light(const int fd, t_env *e);
void				export_camera(const int fd, t_env *e);

#endif
