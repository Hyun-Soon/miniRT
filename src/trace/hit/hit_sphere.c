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

t_bool	hit_sphere(t_sphere *sp, t_ray *ray, t_hit_record *rec)
{
	t_vec3 oc;
	double a;
	double half_b;
	double c;
	double discriminant;

	double sqrtd;
	double root;

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
	set_face_normal(ray, rec);
	return (TRUE);
}