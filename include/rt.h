/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:07:48 by wwatkins          #+#    #+#             */
/*   Updated: 2016/04/20 18:10:55 by tbeauman         ###   ########.fr       */
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

enum { SPHERE, CONE, PLANE, CYLINDER, TRIANGLE, CUBE, PARALLELOGRAM,
		HYPERBOLOID_ONE, HYPERBOLOID_TWO, PARABOLOID, TORUS, QUADRIC , MOEBIUS,
		DISC, CSG };
enum { POINT, SPOT, DIRECTIONAL };
enum { NONE, MARBLE, WOOD, EARTH, BMP };
enum { HARD, SOFT };
enum { UNION, DIFF, INTER };

typedef struct		s_arg
{
	char			*file;
	int				fd;
	int				w;
	int				h;
}					t_arg;

typedef struct		s_key
{
	char			ku;
	char			kd;
	char			kl;
	char			kr;
	char			i;
	char			k;
	char			j;
	char			l;
	char			kp;
	char			km;
	char			mouse;
	char			debug;
	char			invert;
	char			gray_scale;
	char			gamma_m;
	char			gamma_p;
}					t_key;

typedef struct		s_mouse
{
	t_vec3			pos;
	double			sensibility;
	char			lerp;
	char			km;
	char			kp;
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
	short			receive_shadow;
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
	double			d;
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

typedef struct		s_coeffs
{
	double			a;
	double			b;
	double			c;
	double			d;
	double			e;
	double			f;
	double			g;
	double			h;
	double			i;
	double			j;
}					t_coeff;

typedef struct		s_obj
{
	t_vec3			pos;
	t_vec3			pos2;
	t_vec3			pos3;
	t_vec3			dir;
	t_vec3			normal;
	t_mat			mat;
	t_coeff			co;
	short			type;
	double			m;
	double			pr;
	double			gr;
	double			scale;
	double			scale2;
	double			y_min;
	double			y_max;
	double			k;
	double			t;
	double			in;
	double			out;
	int 			comp_hit;
	int				op;
	struct s_obj	*left;
	struct s_obj	*right;
	struct s_obj	*comp;
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
	double			dist;
	double			(*intersect[15])(t_ray *, t_obj *);
}					t_env;

/*
**	PARSING FUNCTIONS
*/

void				parse_yml(t_env *e);
void				parse(t_env *e, t_parse *core);
t_cam				*parse_camera(t_env *e, t_line *cam_line);
t_lgt				*parse_light(t_env *e, t_line *light_line);
t_obj				*parse_object(t_env *e, t_line *object_line);
short				parse_boolean(const char *line);
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
int					mouse_hook(int button, int x, int y, t_env *e);

/*
**	MOVEMENT FUNCTIONS
*/

void				move_translate(t_env *e);
void				move_rotate(t_env *e);
void				move_zoom(t_env *e);
void				mouse_orientation(t_env *e);

/*
** polynomial solver
*/

typedef struct		s_poly6
{
	double			a[7];
	double			root[6];
}					t_poly6;

typedef struct		s_euclid
{
	t_poly6			q;
	t_poly6			r;
}					t_euclid;

typedef struct		s_sturm
{
	t_poly6			*s;
	int				len;
}					t_sturm;

typedef struct		s_poly4
{
	double			a0;
	double			a1;
	double			a2;
	double			a3;
	double			a4;
	double			root1;
	double			root2;
	double			root3;
	double			root4;
}					t_poly4;

int					solve_quadratic(t_poly4 *p);
int					solve_cubic(t_poly4 *p);
int					solve_quartic(t_poly4 *p);

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
double				intersect_triangle(t_ray *r, t_obj *t);
double				intersect_ellipsoid(t_ray *r, t_obj *e);
double				intersect_hyperboloid1(t_ray *r, t_obj *o);
double				intersect_hyperboloid2(t_ray *r, t_obj *o);
double				intersect_paraboloid(t_ray *ray, t_obj *o);
double				intersect_torus(t_ray *ray, t_obj *obj);
double				intersect_cube_troue(t_ray *ray, t_obj *obj);
double				intersect_parallelogram(t_ray *r, t_obj *t);
double				intersect_cube(t_ray *ray, t_obj *cube);
double				intersect_quadric(t_ray *ray, t_obj *cube);
double				intersect_moebius(t_ray *ray, t_obj *obj);
double				intersect_disc(t_ray *r, t_obj *t);
double				intersect_csg(t_ray *r, t_obj *t);
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
