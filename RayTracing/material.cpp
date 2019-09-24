#include "material.h"

bool lambertian::scatter(const ray& r, const hitRecord& rec, vec3& attenuation, ray& scattered) const
{
	vec3 target = rec.p + rec.normal + tools::randomInUnitSphere();
	scattered = ray(rec.p, target);
	attenuation = _att;
	return true;
}

bool smooth::scatter(const ray& r, const hitRecord& rec, vec3& attenuation, ray& scattered) const
{
	vec3 target = rec.p + Reflect(Unit(r.getDirection()), rec.normal);
	scattered = ray(rec.p, target + _fuzz * tools::randomInUnitSphere());
	attenuation = _att;
	return (Dot(scattered.getDirection(), rec.normal) > 0);
}

bool transparent::scatter(const ray& r, const hitRecord& rec, vec3& attenuation, ray& scattered) const
{
	vec3 outNormal;
	vec3 reflected = Reflect(r.getDirection(), rec.normal);

	float ind;
	attenuation = vec3(1.f, 1.f, 1.f);
	vec3 refracted;
	float reflectProb;
	float cosine;

	if (Dot(r.getDirection(), rec.normal) > 0)
	{
		outNormal = -rec.normal;
		ind = _refract;
		cosine = _refract * Dot(r.getDirection(), rec.normal) / r.getDirection().length();
	}
	else
	{
		outNormal = rec.normal;
		ind = 1.f / _refract;
		cosine = -Dot(r.getDirection(), rec.normal) / r.getDirection().length();
	}
	
	if (tools::refract(r.getDirection(), outNormal, ind, refracted))
	{
		reflectProb = tools::schlick(cosine, _refract);
	}
	else {
		scattered = ray(rec.p, reflected);
		reflectProb = 1.f;
	}
	if(tools::rand1()>=reflectProb){
		scattered = ray(rec.p, refracted);
	}
	else {
		scattered = ray(rec.p, reflected);
	}
	return true;
}