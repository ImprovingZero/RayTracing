#pragma once
#include"hitable.h"
#include"toolkits.h"

class material
{
public:
	virtual bool scatter(const ray& rIn, const hitRecord& rec, vec3& attenuation, ray& scattered) const = 0;
};

class lambertian : public material
{
private:
	vec3 _att;
public:
	lambertian(const vec3& a) : _att(a) {};
	virtual bool scatter(const ray& r, const hitRecord& rec, vec3& attenuation, ray& scattered) const;
};

class smooth : public material
{
private:
	vec3 _att;
	float _fuzz;
public:
	smooth(const vec3& att, const float fuzz = 0.f) :_att(att), _fuzz(fuzz) { if (fuzz < 0.f || fuzz>1.f) _fuzz = 0.f; }
	virtual bool scatter(const ray& r, const hitRecord& rec, vec3& attenuation, ray& scattered) const;
};

class transparent :public material
{
private:
	float _refract;
public:
	transparent(float r) :_refract(r) {}
	virtual bool scatter(const ray& r, const hitRecord& rec, vec3& attenuation, ray& scattered) const;

};
