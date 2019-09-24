#pragma once

#include"ray.h"

class camera
{
private:
	vec3 _lowerLeftConer;
	vec3 _horizontal;
	vec3 _vertical;
	vec3 _origin;
	vec3 _u, _v, _w;
	float _lensRadius;
public:
	camera(vec3 lookFrom, vec3 lookAt, vec3 up,
		float vfov, float aspect);
	camera(vec3 lookFrom, vec3 lookAt, vec3 up,
		float vfov, float aspect, float apeture ,float focusDist);
	const ray getRay(float u, float v) { return ray(_origin, _lowerLeftConer + u * _horizontal + v * _vertical); }
	inline const vec3 getOrigin() const { return _origin; }
	inline const vec3 getHorizontal() const { return _horizontal; }
	inline const vec3 getVertical() const { return _vertical; }
	inline const vec3 getLLC() const { return _lowerLeftConer; }
};

