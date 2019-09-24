#include "sphere.h"

bool sphere::hit(const ray& r, float tMin, float tMax, hitRecord& rec) const
{
	//dot(A+t*B-C,A+t*B-C))=R*R
	//t*t*dot(B,B) + 2*t*dot(B,A-C) + dot(A-C,A-C) - R*R = 0
	//solve t in this equation
	//use delta = b*b-4*a*c
	//to accelerate, let b/=2
	vec3 oc(r.getOrigin() - _center);
	float a = Dot(r.getDirection(), r.getDirection());
	float b = Dot(r.getDirection(), oc);
	float c = Dot(oc, oc) - _radius * _radius;
	float delta = b * b - a * c;
	if (delta > 0)
	{
		float temp = (-b - sqrt(delta)) / a;
		if (temp<tMax && temp>tMin)
		{
			rec.t = temp;
			rec.p = r.PointAtParameter(rec.t);
			rec.normal = (rec.p - _center) / _radius;
			rec.mat = _mtr;
			return true;
		}
		temp = (-b + sqrt(delta)) / a;
		if (temp<tMax && temp>tMin)
		{
			rec.t = temp;
			rec.p = r.PointAtParameter(rec.t);
			rec.normal = (rec.p - _center) / _radius;
			rec.mat = _mtr;
			return true;
		}
	}
	return false;
}