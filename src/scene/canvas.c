#include "scene.h"

t_canvas	canvas(int width, int height)
{
	t_canvas	ret;

	ret.width = width;
	ret.height = height;
	ret.aspect_ratio = (double)width / (double)height;
	return (ret);
}