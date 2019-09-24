#pragma once

#include"ray.h"

class camera
{
private:
	vec3 _lowerLeftConer;
	vec3 _horizontal;
	vec3 _vertical;
	vec3 _origin;
public:
	camera(vec3 lowerLeftConer = vec3(-2.f, -1.f, -1.f),
		vec3 horizontal = vec3(4.f, 0.f, 0.f),
		vec3 vertical = vec3(0.f, 2.f, 0.f),
		vec3 origin = vec3(0.f, 0.f, 0.f))
		:_lowerLeftConer(lowerLeftConer), _horizontal(horizontal), _vertical(vertical), _origin(origin) {};
	const ray getRay(float u, float v) { return ray(_origin, _lowerLeftConer + u * _horizontal + v * _vertical); }
	inline const vec3 getOrigin() const { return _origin; }
	inline const vec3 getHorizontal() const { return _horizontal; }
	inline const vec3 getVertical() const { return _vertical; }
	inline const vec3 getLLC() const { return _lowerLeftConer; }
};

