#pragma once

#include"ray.h"

class material;

struct hitRecord
{
	float t = 0.f;
	vec3 p;
	vec3 normal;
	material* mat;
};

class hitable
{
public:
	virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& rec) const = 0;
};

