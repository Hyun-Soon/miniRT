#include "trace.h"

//ray 생성자(정규화 된 ray)
t_ray	ray(t_point3 org, t_vec3 dir)
{
	t_ray ret;

	ret.org = org;
	ret.dir = vunit(dir);
	return (ret);
}

//ray origin point부터 방향벡터 ray dir * t 만큼 떨어진 점
t_point3	ray_at(t_ray *ray, double t)
{
	t_point3 at;

	at = vplus(ray->org, vmult(ray->dir, t));
	return (at);
}

//primary_ray 생성자
t_ray	ray_primary(t_camera *cam, double u, double v)
{
	t_ray	ray;

	ray.org = cam->org;
	ray.dir = vunit(vminus(vplus(vplus(cam->left_bottom, vmult(cam->horizontal, u)), vmult(cam->vertical, v)), cam->org));
	return(ray);
}

//광선이 최종적으로 얻게 된 픽셀의 색상 값을 리턴
t_color3	ray_color(t_ray *r, t_sphere *sphere)
{
	double	t;
	t_hit_record rec;

	rec.tmin = 0;
	rec.tmax = INFINITY;
	//t = hit_sphere(sphere, r);
	//if (t > 0.0)
	//{
	//	//정규화 된 표면에서의 법선
	//	n = vunit(vminus(ray_at(r, t), sphere->center));
	//	return (vmult(color3(n.x + 1, n.y + 1, n.z + 1), 0.5));
	//}
	if (hit_sphere(sphere, r, &rec))
		return (vmult(vplus(rec.normal, color3(1, 1, 1)), 0.5));
	t = 0.5 * (r->dir.y + 1.0);
	//(1-t) * white + t * skyblue
	return (vplus(vmult(color3(1, 1, 1), 1.0 - t), vmult(color3(0, 0, 0), t)));
}