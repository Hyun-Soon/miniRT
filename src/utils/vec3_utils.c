#include "utils.h"

//벡터3 생성자
t_vec3	vec3(double x, double y, double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

//포인트3 생성자
t_point3    point3(double x, double y, double z)
{
    t_point3 point;

    point.x = x;
    point.y = y;
    point.z = z;
    return (point);
}

//색상3 생성자
t_point3    color3(double r, double g, double b)
{
    t_color3 color;

    color.x = r;
    color.y = g;
    color.z = b;
    return (color);
}

//벡터  값  설정
void	vset(t_vec3 *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

//벡터 길이 제곱
double	vlength2(t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

//벡터 길이
double	vlength(t_vec3 vec)
{
	return (sqrt(vlength2(vec)));
}

//벡터 합
t_vec3	vplus(t_vec3 vec1, t_vec3 vec2)
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
	vec1.z += vec2.z;
	return (vec1);
}

//벡터 합2
t_vec3	vplus_(t_vec3 vec, double x, double y, double z)
{
	vec.x += x;
	vec.y += y;
	vec.z += z;
	return (vec);
}

//벡터 차
t_vec3 vminus(t_vec3 vec1, t_vec3 vec2)
{
	vec1.x -= vec2.x;
	vec1.y -= vec2.y;
	vec1.z -= vec2.z;
	return (vec1);
}

//벡터 차2
t_vec3	vminus_(t_vec3 vec, double x, double y, double z)
{
	vec.x -= x;
	vec.y -= y;
	vec.z -= z;
	return (vec);
}

//벡터 스칼라 곱연산
t_vec3	vmult(t_vec3 vec, double t)
{
	vec.x *= t;
	vec.y *= t;
	vec.z *= t;
	return (vec);
}

//벡터 축 값끼리 곱연산
t_vec3	vmult_(t_vec3 vec1, t_vec3 vec2)
{
	vec1.x *= vec2.x;
	vec1.y *= vec2.y;
	vec1.z *= vec2.z;
	return (vec1);
}

//벡터 스칼라 나누기
t_vec3      vdivide(t_vec3 vec, double t)
{
    vec.x *= 1 / t;
    vec.y *= 1 / t;
    vec.z *= 1 / t;

    return vec;
}

//벡터 내적
double	vdot(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

//벡터 외적
t_vec3	vcross(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3 ret;

	ret.x = vec1.y * vec2.z - vec1.z * vec2.y;
	ret.y = vec1.z * vec2.x - vec1.x * vec2.z;
	ret.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (ret);
}

//단위 벡터
t_vec3	vunit(t_vec3 vec)
{
	double	size = vlength(vec);
	if (size == 0)
	{
		printf("Error\n:Devider is 0\n");
		exit(1);
	}
	vec.x /= size;
	vec.y /= size;
	vec.z /= size;
	return (vec);
}

//두 벡터의 원소를 비교하여 작은 값들만 반환
t_vec3	vmin(t_vec3 vec1, t_vec3 vec2)
{
	if (vec1.x > vec2.x)
		vec1.x = vec2.x;
	if (vec1.y > vec2.y)
		vec1.y = vec2.y;
	if (vec1.z > vec2.z)
		vec1.z = vec2.z;
	return (vec1);
}