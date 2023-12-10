#include "trace.h"

t_bool hit(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_bool hit_anything;
	t_hit_record temp_rec;

	temp_rec = *rec;
	hit_anything = FALSE;
	while (world)
	{
		if (hit_obj(world, ray, &temp_rec))
		{
			hit_anything = TRUE;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
			//here
		}
	}
}