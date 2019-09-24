#include "camera.h"

#define _USE_MATH_DEFINES
#include<math.h>

camera::camera(vec3 lookFrom, vec3 lookAt, vec3 up,
	float vfov, float aspect)
	:_origin(lookFrom),_lensRadius(1.f)
{
	float theta = vfov * float(M_PI) / 180.f;
	float halfHeight = tan(theta / 2);
	float halfWidth = aspect * halfHeight;

	_w = Unit(lookFrom - lookAt);
	_u = Unit(Cross(up, _w));
	_v = Cross(_w, _u);

	_lowerLeftConer = lookFrom - _w - halfWidth * _u - halfHeight * _v;
	_horizontal = 2 * halfWidth * _u;
	_vertical = 2 * halfHeight * _v;
}

camera::camera(vec3 lookFrom, vec3 lookAt, vec3 up, 
	float vfov, float aspect, float apeture, float focusDist)
	:_origin(lookFrom),
	_lensRadius(apeture/2.f)
	
{
	float theta = vfov * float(M_PI) / 180.f;
	float halfHeight = tan(theta / 2);
	float halfWidth = aspect * halfHeight;

	_w = Unit(lookFrom - lookAt);
	_u = Unit(Cross(up, _w));
	_v = Cross(_w, _u);

	_lowerLeftConer = lookFrom - _w * focusDist - halfWidth * _u * focusDist - halfHeight * _v * focusDist;
	_horizontal = 2 * halfWidth * _u * focusDist;
	_vertical = 2 * halfHeight * _v * focusDist;
}