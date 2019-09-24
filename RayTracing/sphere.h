#pragma once

#include"hitable.h"

class sphere: public hitable
{
private:
	vec3 _center;
	float _radius;
	material* _mtr;
public:
	sphere() :_center(vec3()), _radius(0.f), _mtr(NULL) { };
	sphere(vec3 cen, float r, material* mtr) : _center(cen), _radius(r), _mtr(mtr) {};
	virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& rec) const;
	const material* getmaterial() { return _mtr; }
};
