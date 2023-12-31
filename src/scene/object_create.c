#include "structures.h"
#include "scene.h"

t_object	*object(t_object_type type, void *element, t_color3 albedo)
{
	t_object *new;

	if (!(new = (t_object *)malloc(sizeof(t_object))))
		return (NULL);
	new->type = type;
	new->element = element;
	new->next = NULL;
	new->albedo = albedo;
	return (new);
}

t_sphere	*sphere(t_point3 center, double radius)
{
	t_sphere *sp;
	
	if (!(sp = (t_sphere *)malloc(sizeof(t_sphere))))
		return (NULL);
	sp->center = center;
	sp->radius = radius;
	sp->radius2 = radius * radius;
	return (sp);
}

t_plane	*plane(t_point3 pos, t_vec3 n)
{
	t_plane *pl;

	if (!(pl = (t_plane *)malloc(sizeof(t_plane))))
		return (NULL);
	pl->pos = pos;
	pl->n = n;
	return (pl);
}

t_cylinder *cylinder(t_point3 pos, t_vec3 n, double d, double h)
{
	t_cylinder *cy;

	if (!(cy = (t_cylinder *)malloc(sizeof(t_cylinder))))
		return (NULL);
	cy->pos = pos;
	cy->n = vunit(n);
	cy->diameter = d;
	cy->r = d / 2;
	cy->h = h;
	return (cy);
}

t_disk *disk(t_point3 pos, t_vec3 n, double r)
{
	t_disk *dsk;

	if (!(dsk = (t_disk *)malloc(sizeof(t_disk))))
		return (NULL);

	dsk->pos = pos;
	dsk->n = vunit(n);
	dsk->r = r;
	return (dsk);
}

t_cone *cone(t_point3 pos, t_vec3 n, double r, double h)
{
	t_cone *cone;

	if (!(cone = (t_cone *)malloc(sizeof(t_cone))))
		return (NULL);
	
	cone->pos = pos;
	cone->n = vunit(n);
	cone->r = r;
	cone->h = h;
	return (cone);
}

t_light	*light_point(t_point3 light_org, t_color3 light_color, double bright_ratio)
{
	t_light *light;

	if (!(light = (t_light *)malloc(sizeof(t_light))))
		return (NULL);
	light->org = light_org;
	light->light_color = light_color;
	light->bright_ratio = bright_ratio;
	return (light);
}