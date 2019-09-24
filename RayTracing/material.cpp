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
	vec3 Normal;
	vec3 reflected = Reflect(r.getDirection(), rec.normal);
	float ind = 1.f;
	attenuation = vec3(1.f, 1.f, 1.f);
	vec3 refracted;
	float reflectProb;
	float cos;
	if (Dot(r.getDirection(), rec.normal) > 0)
	{
		Normal = -rec.normal;
		ind = _refract;
		cos = _refract * Dot(r.getDirection(), rec.normal) / r.getDirection().length();
	}
	else
	{
		Normal = rec.normal;
		ind = 1 / _refract;
		cos = -Dot(r.getDirection(), rec.normal) / r.getDirection().length();
	}
	if (tools::refract(r.getDirection(), Normal, ind, refracted))
	{
		reflectProb = tools::schlick(cos, _refract);
	}
	else {
		scattered = ray(rec.p, rec.p + reflected);
		reflectProb = 1.f;
	}
	if (tools::rand1()<reflectProb)
	{
		scattered = ray(rec.p, reflected + rec.p);  //Attention: ray(origin,DESTINATION); the 2nd parameter is NOT direction
	}
	else
	{
		scattered = ray(rec.p, rec.p + refracted);
	}
	return true;
}