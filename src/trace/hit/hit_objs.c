#include "structures.h"
#include "utils.h"
#include "trace.h"

//double	hit_sphere(t_sphere *sp, t_ray *ray)
//{
//	t_vec3	oc;
//	//a, b, c는 각각 t에 관한 2차 방정식의 계수
//	double a;
//	double b;
//	double c;
//	double discriminant; //판별식

//	oc = vminus(ray->org, sp->center);
//	a = vdot(ray->dir, ray->dir);
//	b = vdot(ray->dir, oc) * 2;
//	c = vdot(oc, oc) - sp->radius2;
//	discriminant = b * b - 4 * a * c;

//	if (discriminant < 0)
//		return (-1.0);
//	else
//		return ((-b -sqrt(discriminant)) / (2.0 * a)); //두 근 중 작은 근 because of parametric eq.
//}

t_bool	hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
	t_vec3 oc;
	double a;
	double half_b;
	double c;
	double discriminant;

	double sqrtd;
	double root;
	t_sphere *sp;

	sp = sp_obj->element;
	oc = vminus(ray->org, sp->center);
	a = vlength2(ray->dir);
	half_b = vdot(ray->dir, oc);
	c = vlength2(oc) - sp->radius2;
	discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(discriminant);
	//두 실근(t) 중 tmin과 tmax 사이에 있는 근이 있는지 체크, 작은 근부터 체크.
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius);
	rec->albedo = sp_obj->albedo;
	set_face_normal(ray, rec);
	return (TRUE);
}

t_bool hit_plane(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
	t_plane *pl = sp_obj->element;

	double	temp_a = vdot(pl->n, pl->pos) - vdot(pl->n, ray->org);
	double	temp_b = vdot(ray->dir, pl->n);
	double	root = temp_a / temp_b;

	if (root < rec->tmin || root > rec->tmax)
		return (FALSE);

	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = pl->n;
	rec->albedo = sp_obj->albedo;
	set_face_normal(ray, rec);
	return (TRUE);
	
}

t_bool hit_cylinder(t_object *sb_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder *cy = sb_obj->element;

	t_vec3	D_xz = vec3(ray->dir.x, 0, ray->dir.z);
	t_vec3	C_xz = vec3(ray->org.x, 0, ray->org.z);
	t_vec3	Pos_xz = vec3(cy->pos.x, 0, cy->pos.z);
	t_vec3	A = vminus(C_xz, Pos_xz);

	double	a = vdot(D_xz, D_xz);
	double	b_prime = vdot(D_xz, A);
	double	c = vdot(A, A) - cy->r * cy->r;
	double discriminant = b_prime * b_prime - a * c;
	double	t;
	t_point3 isp;
	
	if (discriminant < 0)
		return (FALSE);
	t = (-b_prime - sqrt(discriminant)) / a;
	isp = vplus(ray->org, vmult(ray->dir, t));

	if (t < rec->tmin || rec->tmax < t || isp.y < cy->pos.y || isp.y > cy->pos.y + cy->h)
	{
		t = (-b_prime + sqrt(b_prime * b_prime - a * c)) / a;
		isp = vplus(ray->org, vmult(ray->dir, t));
		if (t < rec->tmin || rec->tmax < t || isp.y < cy->pos.y || isp.y > cy->pos.y + cy->h)
			return (FALSE);
	}

	rec->t = t;
	rec->p = ray_at(ray, t);
	rec->normal = vunit(vminus(vplus(ray->org, vmult(ray->dir, t)), vec3(cy->pos.x, isp.y, cy->pos.z)));
	rec->albedo = sb_obj->albedo;
	set_face_normal(ray, rec);
	return (TRUE);
}