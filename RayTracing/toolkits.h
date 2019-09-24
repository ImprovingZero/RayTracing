#pragma once
#include"vec3.h"
namespace tools {
	class toolkits
	{
	};
	const float rand1();
	const vec3 randomInUnitSphere();
	const bool refract(const vec3& v, const vec3& n, float IdT, vec3& refracted);
	const float schlick(float cosine, float refInd);
}


