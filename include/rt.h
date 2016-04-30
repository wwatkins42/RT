/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:07:48 by wwatkins          #+#    #+#             */
/*   Updated: 2016/04/30 10:31:09 by scollon          ###   ########.fr       */
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
# define IMG_PATH "./resource/images/"
# define FILE_ARG O_WRONLY | O_CREAT
# define FILE_RIGHTS S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
# define FILE_NAME_LENGTH 255
# define T_RES_W 2560
# define T_RES_H 1440
# define ASCII "@8N#Oo{?*|\\!;:,. "

/*
**	CAM TYPES
*/
enum {DEFAULT, STEREOSCOPIC};

/*
**	OBJECT TYPES
*/
enum { SPHERE, CONE, PLANE, CYLINDER, TRIANGLE, CUBE, PARALLELOGRAM, DISC,
		HYPERBOLOID_ONE, HYPERBOLOID_TWO, PARABOLOID, CHEWINGGUM, TORUS,
		QUADRIC, MOEBIUS, CSG, BBOX, CUBE_TROUE };

/*
** CSG OPERATORS
*/
enum { UNION, INTER, DIFF };


/*
**	LIGHT TYPES
*/
enum { POINT, SPOT, DIRECTIONAL };

/*
**	TEXTURE TYPES
*/
enum { NONE, MARBLE, WOOD, BMP, CHECKER };

/*
**	SHADOW TYPES
*/
enum { HARD, SOFT, PROJECTION };

/*
**	KEYMAP
*/
enum { CF = 13, CB = 1, CL = 0, CR = 2, CU = 49, CD = 257, OF = 126,
	OB = 125, OU = 116, OD = 121, OL = 123, OR = 124, KP = 69, KM = 78,
	I = 34, K = 40, J = 38, L = 37, CMD = 259, CTRL = 256, DEL = 51,
	FGP = 24, FGM = 27, FG = 19, FI = 18, STAT = 50, MOUSE = 46 };

typedef struct		s_arg
{
	char			*file;
	int				fd;
	int				w;
	int				h;
	int				shell;
}					t_arg;

typedef struct		s_mouse
{
	t_vec3			pos;
	double			sensibility;
	char			lerp;
	char			km;
	char			kp;
	char			lmb;
	char			rmb;
}					t_mouse;

typedef struct		s_texture
{
	t_rgb			**img;
	t_rgb			**bump;
	t_vec3			normal;
	int				w;
	int				h;
	int				sl;
	short			bpp;
	short			opp;
	short			type;
	short			filtering;
	short			defined;
	short			transparency_mapping;
	short			normal_map;
	double			normal_strength;
	double			scale;
	double			rotation;
	char			*name;
}					t_texture;

typedef struct		s_triangle
{
	t_vec3			p;
	double			det;
	t_vec3			vertex_camera_direction;
	t_vec3			q;
	double			u;
	double			v;
}					t_triangle;

typedef struct		s_noise
{
	double			*noise;
	int				w_max;
	int				h_max;
	int				len;
	int				pas;
	int				octave;
	t_rgb			(*noise_func[3])(struct s_noise*, int, int);
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

typedef struct		s_fresnel
{
	double			reflect;
	double			refract;
	char			defined;
}					t_fresnel;

typedef struct		s_mat
{
	t_vec3			color;
	t_texture		texture;
	t_fresnel		fresnel;
	double			ambient;
	double			diffuse;
	double			specular;
	double			shininess;
	double			glossiness;
	double			reflect;
	double			refract;
	double			transparency;
	double			absorbtion;
	short			receive_shadow;
	short			normal_perturbation;
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
	t_vec3			cut;
	t_mat			mat;
	t_coeff			co;
	short			type;
	double			m;
	double			pr;
	double			gr;
	double			scale;
	double			scale2;
	double			min;
	double			max;
	double			k;
	double			t;
	double			dist_attenuation;
	double			in;
	double			out;
	int				op;
	struct s_obj	*left;
	struct s_obj	*right;
	int 			comp_hit;
	unsigned short	id;
	struct s_obj	*comp;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_cam
{
	char			type;
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			origin;
	t_img			img;
	t_img			stereo;
	t_ray			ray;
	t_filter		filter;
	t_aa			aa;
	t_obj			*selection;
	int				index;
	int				x;
	int				y;
	double			xa;
	double			ya;
	double			fov;
	double			dist;
	struct s_cam	*prev;
	struct s_cam	*next;
	struct s_cam	*twin;
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


typedef	struct		s_lgt
{
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			color;
	t_ray			ray;
	short			type;
	short			shadow;
	double			shadow_intensity;
	double			scale;
	double			intensity;
	double			attenuation;
	double			cutoff;
	double			cutoff_outer;
	double			cutoff_intensity;
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
	int				rps;
	int				fps;
}					t_count;

typedef struct		s_scene
{
	short			resync;
	short			percent;
	short			progressive_loading;
	short			sampling;
	double			velocity;
	int				inc;
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

typedef struct		s_tick
{
	clock_t			current;
	clock_t			last;
	clock_t			frame_start;
	double			frame;
}					t_tick;

typedef struct		s_env
{
	void			*mlx;
	t_win			win;
	t_arg			arg;
	char			key[280];
	t_mouse			mouse;
	t_scene			scene;
	t_count			count;
	t_tick			tick;
	t_cam			*cam;
	t_obj			*obj;
	t_lgt			*lgt;
	t_ray			ray;
	t_vec3			color;
	t_reflect		reflect;
	t_refract		refract;
	double			stereo_nb;
	double			(*intersect[20])(t_ray *, t_obj *);
}					t_env;

/*
**	PARSING FUNCTIONS
*/

void				parse_yml(t_env *e);
void				parse(t_env *e, t_parse *core);
t_cam				*parse_camera(t_env *e, t_line *cam_line);
t_lgt				*parse_light(t_env *e, t_line *light_line);
t_obj				*parse_object(t_env *e, t_line *object_line);
t_obj				*create_object(t_env *e, t_line *object_line);
void				fill_object_attr(t_env *e, t_line *line, t_obj *new);
int					get_object_type(char *line);
void				create_cube(t_obj *cube);
void				parse_material(t_env *e, t_mat *mat, t_line *line);
short				parse_boolean(const char *line);
double				parse_value(const char *line, double min, double max);
t_vec3				parse_vector(const char *line);
t_vec3				parse_color(char *line);
t_obj				*parse_obj(char *file, t_env *e, t_obj *parent);
t_obj				*add_triangle(char *line, t_vec3 *vect, t_obj *obj_list,
									int max);
int					is_comment(const char *line);
void				default_object(t_obj *object);
void				parse_csg(t_env *e, t_obj *csg, t_line *line);



/*
** POLYNOM SOLVER
*/

typedef struct          s_cubic
{
        double			q;
        double			r;
        double			bq;
        double			br;
        double			bq3;
        double			br2;
        double			cr2;
        double			cq3;
        double			sqrtbq;
        double			sgnbr;
        double			ratio;
        double			theta;
        double			norm;
        double			r0;
        double			r1;
        double			r2;
        double			ba;
        double			bb;
        int             i;
}						t_cubic;

typedef struct		s_quartic
{
	double			u[3];
	double			v[3];
	double			zarr[4];
	double			args[3];
	double			aa;
	double			pp;
	double			qq;
	double			rr;
	double			rc;
	double			sc;
	double			tc;
	double			mt;
	double			w1r;
	double			w1i;
	double			w2r;
	double			w2i;
	double			w3r;
	double			v1;
	double			v2;
	double			arg;
	double			theta;
	double			disc;
	double			h;
	double			qcub;
	double			rcub;
	double			bq;
	double			br;
	double			bq3;
	double			br2;
	double			cr2;
	double			cq3;
	double			sqrtbq;
	double			sqrtbq3;
	double			sgnbr;
	double			modbr;
	double			norm;
	double			sqrt_disc;
	double			ba;
	double			bb;
	double			mod_diffbabb;
	int				k1;
	int				k2;
}					t_quartic;

int					solve_quadratic(double *a, double *r);
int					solve_cubic(double *a, double *r);
int					solve_quartic(double *a, double *r);
int					swapd(double *a, double *b);
double				max(double a, double b);
int					deal_with_degenerate(double *a, double *r);
void				find_solution_to_resolvent_cubic(t_quartic *q);
void				set_d3(double *u, double u0, double u1, double u2);
void				fonction_relativement_assez_nulle(double *r, double *zarr);
double				choose_root3(double *roots, int ret);
double				choose_root4(double *roots, int ret);

/*
**	ENVIRONNEMENT INIT FUNCTIONS
*/

void				init_env(t_env *e);
void				init_intersect(t_env *e);
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

void				object_select(t_env *e);
void				object_delete(t_env *e, t_obj *obj);
void				object_move(t_env *e, t_obj *obj);
void				object_mouse_move(t_env *e, t_obj *obj);
void				object_mouse_rotate(t_env *e, t_obj *obj);


/*
**	RAYTRACING FUNCTIONS
*/

/*
**			Main functions
*/

void				start_raytracing(t_env *e);
void				raytracing(t_env *e, t_cam *cam);
void				raytracing_progressive(t_env *e, t_cam *cam);
void				raytracing_shell(t_env *e, t_cam *cam);
void				raytracing_init(t_env *e, t_cam *cam, float x, float y);
t_vec3				raytracing_draw(t_env *e, t_cam *cam, t_ray ray);

/*
**			Primitives intersections
*/

typedef struct	s_moebius
{
	double		a;
	double		b;
	double		c;
	double		d;
	double		e;
	double		f;
	double		g;
}				t_moebius;

typedef struct	s_cal
{
	double		tmp;
	double		dirinv[2][2];
	double		point[2];
	double		det;
	double		p;
	double		q;
}				t_cal;

t_obj				*intersect_object(t_env *e, t_ray *ray, double *tmin,
										t_obj *obj);
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
double				intersect_chewing_gum(t_ray *ray, t_obj *obj);
double				intersect_cube_troue(t_ray *ray, t_obj *obj);
double				intersect_parallelogram(t_ray *r, t_obj *t);
double				intersect_cube(t_ray *ray, t_obj *cube);
double				intersect_quadric(t_ray *ray, t_obj *cube);
double				intersect_moebius(t_ray *ray, t_obj *obj);
double				intersect_disc(t_ray *r, t_obj *t);
double				intersects_bbox(t_ray *ray, t_obj *b);
double				intersect_cube_troue(t_ray *ray, t_obj *b);
void				set_normal(t_ray *ray, t_obj *obj);
double				compute_m(t_ray *ray, t_obj *obj, t_vec3 dir, double tmp);
/*
** CSG INTERSECTION
*/
double				intersect_csg(t_ray *r, t_obj *t);
double   			save_lin_lout(t_ray *r, t_obj *l, t_obj *ri, t_obj *dad);
double   			save_lin_rout(t_ray *r, t_obj *l, t_obj *ri, t_obj *dad);
double   			save_rin_lout(t_ray *r, t_obj *l, t_obj *ri, t_obj *dad);
double   			save_rin_rout(t_ray *r, t_obj *l, t_obj *ri, t_obj *dad);
double   			save_rout_lout(t_ray *r, t_obj *l, t_obj *ri, t_obj *dad);
double   			save_lin_rin(t_ray *r, t_obj *l, t_obj *ri, t_obj *dad);
double   			save_nothan(t_obj *dad);


/*
**			Reflection / Refraction
*/

t_vec3				raytracing_reflect(t_env *e, t_ray ray, t_cam *cam,
										t_obj *obj);
t_vec3				raytracing_reflect_glossy(t_env *e, t_ray ray, t_cam *cam,
												t_obj *obj);
t_vec3				raytracing_refract(t_env *e, t_ray ray, t_cam *cam,
										t_obj *obj);

/*
**			Color and light
*/

t_vec3				raytracing_color(t_env *e, t_ray *ray, t_cam *cam,
										t_obj *obj);
t_vec3				set_diffuse(t_obj *obj, t_lgt *light);
t_vec3				set_specular(t_obj *obj, t_cam *cam, t_lgt *light);
void				set_light(t_vec3 hit, t_obj *obj, t_lgt *light);
void				set_fresnel(t_obj *obj);
double				get_fresnel(t_vec3 v, t_vec3 n, double ir);
void				supersampling(t_env *e, t_cam *cam);
void				set_shadow(t_env *e, t_vec3 *color, t_lgt lgt, t_obj *obj);

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

t_vec3				texture_mapping(t_obj *obj, t_rgb **img, t_vec3 hit);

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

int					ispressed(char *key);
void				kswitch(char *k);
void				display_info(t_env *e, char *str);
void				display_loading(t_env *e, int u, int v);
void				display_texture(t_env *e, t_vec3 **img, t_texture texture);
void				display_stats(t_env *e);

/*
**	FILTER FUNCTIONS
*/

void				filter_invert(t_vec3 *color);
void				filter_gray_scale(t_vec3 *color);
void				filter_gamma(double gamma, t_vec3 *color);
void				filter_img_update(t_env *e);

/*
**	BMP IMPORTER / EXPORTER
*/

void				bmp_exporter(t_cam *cam, char *name);
void				bmp_importer(char *file_path, t_texture *texture);

/*
**	YML EXPORTER
*/

void				yml_exporter(t_env *e, char *name);
void				export_object(const int fd, t_env *e);
void				export_light(const int fd, t_env *e);
void				export_camera(const int fd, t_env *e);

void				generate_stereoscopy(t_env *e);

t_obj				*new_triangle_node(t_vec3 p1, t_vec3 p2, t_vec3 p3,
										t_obj *obj_list);

/*
**	BBOX FUNCTIONS
*/

t_obj				*create_bbox(t_obj *objs);
t_obj				*divide_bbox(t_obj *original_box);
int					count_objs(t_obj *obj);
double				min4(double nb1, double nb2, double nb3, double nb4);
double				max4(double nb1, double nb2, double nb3, double nb4);
double				min(double nb1, double nb2);
double				max(double nb1, double nb2);

#endif
