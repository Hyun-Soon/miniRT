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
	scene->camera = camera(&scene->canvas, point3(0, 0, 0));
	world = object(SP, sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0));
	oadd(&world, object(SP, sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0)));
	//oadd(&world, object(SP, sphere(point3(0, 0, 0), 5), color3(1, 1, 1)));
	oadd(&world, object(PL, plane(point3(0, -3, 0), vec3(0, 1, 0)), point3(0.3, 0.3, 0.3)));
	oadd(&world, object(PL, plane(point3(0, 3, 0), vec3(0, -1, 0)), point3(0.2, 0.2, 0.7)));
	oadd(&world, object(PL, plane(point3(5, 0, 0), vec3(-1, 0, 0)), point3(0.2, 0.7, 0.2)));
	oadd(&world, object(PL, plane(point3(-5, 0, 0), vec3(1, 0, 0)), point3(0.7, 0.2, 0.2)));
	oadd(&world, object(PL, plane(point3(0, 0, -5), vec3(0, 0, 1)), point3(0.1, 0.1, 0.1)));
	scene->world = world;
	lights = object(LIGHT_POINT, light_point(point3(3, 0, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0)); //더미 albedo
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