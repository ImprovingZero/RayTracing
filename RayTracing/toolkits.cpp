#include "toolkits.h"
const float tools::rand1()
{
	return static_cast<float>(rand() % 1000) / 1000.f;
}

const vec3 tools::randomInUnitSphere()
{
	vec3 p;
	do {
		p = 2.f * vec3(rand1(), rand1(), rand1()) - vec3(1.f, 1.f, 1.f);
	} while (p.length() >= 1.f);
	return p;
}

const bool tools::refract(const vec3& light, const vec3& n, float ind, vec3& refracted) //ind = tan(out)/tan(in)
{
	vec3 v = Unit(light);
	float dt = Dot(v, n);
	float delta = 1.f - ind * ind * (1.f - (dt * dt));
	if (delta > 0)
	{
		refracted = ind * (v - n * dt) - n * sqrt(delta);
		return true;
	}
	else return false;
}

const float tools::schlick(float cosine, float refInd)
{
	float r0 = (1 - refInd) / (1 + refInd);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}