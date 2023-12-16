#include "scene.h"

t_camera	camera(t_canvas *canvas, t_point3 org)
{
	t_camera	cam;
	double	focal_len;
	double	viewport_height;

	viewport_height = 2.0;
	focal_len = 2;
	cam.org = org;
	cam.viewport_h = viewport_height;
	cam.viewport_w = viewport_height * canvas->aspect_ratio;
	cam.focal_len = focal_len;
	cam.horizontal = vec3(cam.viewport_w, 0, 0);
	cam.vertical = vec3(0, cam.viewport_h, 0);
	cam.left_bottom = vplus(org, vec3(-cam.viewport_w / 2, -cam.viewport_h / 2, -focal_len));
	return (cam);
}