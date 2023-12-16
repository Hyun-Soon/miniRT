#include "scene.h"
#include "trace.h"
#include "print.h"

t_scene	*scene_init(void)
{
	t_scene		*scene;
	t_object	*world;
	t_object	*lights;
	double		ka;

	//malloc a할당 실패 시, 실습에서는 return NULL로 해두었지만, 적절한 에러 처리가 필요하다.
	if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL);
	scene->canvas = canvas(1200, 900);
	scene->camera = camera(&scene->canvas, point3(0, 0, 20));
	world = NULL;
	//object(SP, sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0));
	//oadd(&world, object(SP, sphere(point3(-5, 5, -5), 2), color3(0.6, 0.6, 0.15)));
	//oadd(&world, object(SP, sphere(point3(0, 0, 0), 5), color3(1, 1, 1)));
	oadd(&world, object(PL, plane(point3(0, -2, 0), vec3(0, 1, 0)), point3(0.3, 0.3, 0.3)));
	oadd(&world, object(PL, plane(point3(0, 6, 0), vec3(0, -1, 0)), point3(0.2, 0.2, 0.3)));
	oadd(&world, object(PL, plane(point3(5, 0, 0), vec3(-1, 1, 0)), point3(0.2, 0.7, 0.2)));
	//oadd(&world, object(PL, plane(point3(-5, 0, 0), vec3(1, 0, 0)), point3(0.7, 0.2, 0.2)));
	//oadd(&world, object(PL, plane(point3(0, 0, -15), vec3(0, 0, 1)), color3(0.2, 0.3, 0.6)));

	//cy1
	double		cy1_d = 4;
	double		cy1_h = 10;
	t_point3	cy1_pos = point3(0, -20, -10);
	t_vec3		cy1_n = vunit(vec3(0, 1, 0));
	t_point3	cy1_color = point3(0.4, 0.2, 0);

	oadd(&world, object(CY, cylinder(cy1_pos, cy1_n, cy1_d, cy1_h), cy1_color));
	oadd(&world, object(DSK, disk(cy1_pos, vmult(cy1_n, -1), cy1_d / 2), cy1_color));
	oadd(&world, object(DSK, disk(vplus(cy1_pos, vmult(cy1_n, cy1_h)), cy1_n, cy1_d / 2), cy1_color));

	//cone1
	t_vec3 cn_pos = vec3(0, -10, -10);
	t_vec3 cn_n = vec3(0, 1, 0);
	t_color3 cn_color = color3(0, 0.2, 0.01);
	double cn_r = 6;

	oadd(&world, object(CN, cone(cn_pos, cn_n, cn_r, 10), cn_color));
	oadd(&world, object(DSK, disk(cn_pos, vmult(cn_n, -1), cn_r), cn_color));

	//cone2
	cn_pos = vec3(0, -6, -10);
	cn_n = vec3(0, 1, 0);
	cn_color = color3(0, 0.25, 0.01);
	cn_r = 5;

	oadd(&world, object(CN, cone(cn_pos, cn_n, cn_r, 8), cn_color));
	oadd(&world, object(DSK, disk(cn_pos, vmult(cn_n, -1), cn_r), cn_color));

	//cone3
	cn_pos = vec3(0, -2, -10);
	cn_n = vec3(0, 1, 0);
	cn_color = color3(0, 0.27, 0.01);
	cn_r = 4;

	oadd(&world, object(CN, cone(cn_pos, cn_n, cn_r, 6), cn_color));
	oadd(&world, object(DSK, disk(cn_pos, vmult(cn_n, -1), cn_r), cn_color));


	//sphere
	oadd(&world, object(SP, sphere(point3(2, -5, -5.8), 0.3), color3(0.6, 0.5, 0.1)));
	oadd(&world, object(SP, sphere(point3(0, -1, -6), 0.3), color3(0.8, 0.2, 0.1)));
	oadd(&world, object(SP, sphere(point3(-3, -8, -5.5), 0.3), color3(0.7, 0.15, 0.9)));

	scene->world = world;
	lights = NULL;
	//object(LIGHT_POINT, light_point(point3(0, 20, 0), color3(1, 1, 1), 0.8), color3(0, 0, 0)); //더미 albedo
	oadd(&lights, object(LIGHT_POINT, light_point(point3(0, 0, 0), color3(1, 1, 1), 0.9), color3(0.5, 0.5, 0)));
	oadd(&lights, object(LIGHT_POINT, light_point(point3(0, -20, 0), color3(1, 1, 1), 0.9), color3(0.5, 0.5, 0)));
	oadd(&lights, object(LIGHT_POINT, light_point(point3(0, 4, -10), color3(0.6, 0.6, 0.15), 0.9), color3(0.5, 0.5, 0)));
	scene->light = lights;
	ka = 0.1;
	scene->ambient = vmult(color3(1, 1, 1), ka);
	return (scene);
}

int	main(void)
{
    int     i;
    int     j;
	double	u;
	double	v;

    t_color3	pixel_color;
	t_scene		*scene;


	scene = scene_init();

    // 랜더링
    // P3 는 색상값이 아스키코드라는 뜻, 그리고 다음 줄은 캔버스의 가로, 세로 픽셀 수, 마지막은 사용할 색상값
    printf("P3\n%d %d\n255\n", scene->canvas.width, scene->canvas.height);
    //j = canvas_height - 1;
	j = scene->canvas.height - 1;
    while (j >= 0)
    {
        i = 0;
        while (i < scene->canvas.width)
        {
        	u = (double)i / (scene->canvas.width - 1);
			v = (double)j / (scene->canvas.height - 1);
			scene->ray = ray_primary(&scene->camera, u, v);
			pixel_color = ray_color(scene);
			write_color(pixel_color);
        	++i;
        }
    	--j;
    }

	//printf("test : %d, %d\n", (int)(0.999 * 255), (int)(0.999 * 255.999));
    return (0);
}