#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_vec3 t_vec3;
typedef struct s_vec3 t_point3;
typedef struct s_vec3 t_color3;
typedef struct s_ray t_ray;
typedef struct s_camera t_camera;
typedef struct s_canvas t_canvas;
typedef struct s_sphere t_sphere;
typedef struct s_plane t_plane;
typedef struct s_cylinder t_cylinder;
typedef struct s_disk t_disk;
typedef struct s_cone t_cone;
typedef struct s_hit_record t_hit_record;
typedef struct s_object t_object;
typedef struct s_light t_light;
typedef struct s_scene t_scene;

typedef int	t_bool;
# define FALSE 0
# define TRUE 1

typedef int t_object_type;
# define SP 0
# define LIGHT_POINT 1
# define PL 2
# define CY 3
# define DSK 4
# define CN 5

# define EPSILON 1e-6 //0.000001
# define LUMEN 3

struct s_vec3
{
	double x;
	double y;
	double z;
};

struct	s_ray
{
	t_point3	org;
	t_vec3		dir;
};

struct s_camera
{
	t_point3	org;
	double		viewport_h;
	double		viewport_w;
	t_vec3		horizontal;
	t_vec3		vertical;
	double		focal_len;
	t_point3	left_bottom;
};

struct s_canvas
{
	int	width;
	int	height;
	double	aspect_ratio;
};

struct s_sphere
{
	t_point3	center;
	double radius;
	double radius2;
};

struct s_plane
{
	t_point3	pos;
	t_vec3		n;
};

struct s_cylinder
{
	t_point3	pos;
	t_vec3		n;
	double		diameter;
	double		r;
	double		h;
};

struct s_disk
{
	t_point3	pos;
	t_vec3		n;
	double		r;
};

struct s_cone
{
	t_point3	pos;
	t_vec3		n;
	double		r;
	double		h;
};

struct s_hit_record
{
	t_point3 p;
	t_vec3 normal;
	double tmin;
	double tmax;
	double t; //광선의 원점과 교점 사이의 거리
	t_bool front_face;
	t_color3 albedo;
};

struct s_object
{
	t_object_type type;
	void	*element;
	void	*next;
	t_color3 albedo;
};

struct s_light
{
	t_point3 org;
	t_color3 light_color;
	double bright_ratio;
};

struct s_scene
{
	t_canvas		canvas;
	t_camera		camera;
	t_object		*world;
	t_object		*light;
	t_color3			ambient;
	t_ray			ray;
	t_hit_record	rec;
};

#endif