#include "trace.h"

t_color3	phong_lighting(t_scene *scene)
{
	t_color3	light_color;
	t_object	*lights;

	light_color = color3(0,0,0);
	lights = scene->light;
	while (lights)
	{
		if (lights->type == LIGHT_POINT)
			light_color = vplus(light_color, point_light_get(scene, lights->element));
		lights = lights->next;
	}
	light_color = vplus(light_color, scene->ambient);
	return (vmin(vmult_(light_color, scene->rec.albedo), color3(1,1,1)));
}

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (vplus(vmult(v, -1), vmult(n, 2 * vdot(v, n))));
}

t_color3	point_light_get(t_scene *scene, t_light *light)
{
	t_color3	diffuse;
	t_vec3		light_dir;
	double		light_len;
	t_ray		light_ray;
	double		kd;
	t_color3	specular;
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	double		spec;
	double		ksn;
	double		ks;
	double		brightness;

	//shadow
	light_dir = vminus(light->org, scene->rec.p); //light_len을 구하려고 vunit 사용 안함.
	light_len = vlength(light_dir);
	light_ray = ray(vplus(scene->rec.p, vmult(scene->rec.normal, EPSILON)), light_dir);
	if (in_shadow(scene->world, light_ray, light_len))
		return (color3(0, 0, 0));

	//diffuse
	light_dir = vunit(vminus(light->org, scene->rec.p)); //교점에서 빛 방향 벡터
	kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);
	diffuse = vmult(light->light_color, kd);

	//specular
	view_dir = vmult(scene->ray.dir, -1);
	reflect_dir = reflect(light_dir, scene->rec.normal);
	ksn = 64;
	ks = 0.5;
	spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
	specular = vmult(vmult(light->light_color, ks), spec);
	brightness = light->bright_ratio * LUMEN;
	return (vmult(vplus(diffuse, specular), brightness));
}

t_bool	in_shadow(t_object *objs, t_ray light_ray, double light_len)
{
	t_hit_record rec;

	rec.tmin = 0;
	rec.tmax = light_len;
	if (hit(objs, &light_ray, &rec))
		return (TRUE);
	return (FALSE);
}