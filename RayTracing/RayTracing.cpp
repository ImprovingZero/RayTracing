﻿// RayTracing.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include"stdafx.h"
#include"hitable_list.h"
#include"sphere.h"
#include"camera.h"
#include"material.h"
using namespace tools;

#define _USE_MATH_DEFINES
#include<math.h>

const vec3 color(ray& r, hitable_list* world, int depth)
{
	
	hitRecord rec;
	if (world->hit(r, 0.001f, 1000.f, rec))
	{
		//No light tracing version:
		//return 0.5 * vec3(rec.normal[0] + 1, rec.normal[1] + 1, rec.normal[2] + 1); 

		//light tracing version:
		/*
		vec3 target = rec.p + rec.normal + randomInUnitSphere();
		ray r(rec.p, target);
		return 0.5f * color(r, world,depth+1);
		*/

		//matirialized light tracing version:
		
		
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else return vec3(0.f, 0.f, 0.f);
		
	}
	else
	{
		vec3 unitDir(Unit(r.getDirection()));
		float t = 0.5f * (unitDir.y() + 1.f); //remap t from [-1,1] to [0,1]
		return (1.f - t) * vec3(1.f, 1.f, 1.f) + t * vec3(0.5f, 0.7f, 1.f);
	}
	//for where t in [0,1], alerp is alwas of the form: 
	//blended_value = (1-t) * star_value + t * end_value
}

int main()
{
	int nx = 1024;
	int ny = 960;
	int ns = 100;
	std::ofstream fout("output.ppm");
	fout << "P3\n" << nx << ' ' << ny << "\n255\n";

	
	float R = cos(float(M_PI) / 4.f);
	std::vector<hitable*>list(0);
	//list.push_back(new sphere(vec3(-R, 0.f, -1.f), R, new lambertian(vec3(0.f, 0.f, 1.f))));
	//list.push_back(new sphere(vec3(R, 0.f, -1.f), R, new lambertian(vec3(1.f, 0.f, 0.f))));
	//list.push_back(new sphere(vec3(0.f,0.f,-1.f),0.5f))

	hitable_list* world = new hitable_list(list);
	world->randomScene();

	vec3 lookfrom(6.f, 1.f, 2.f);
	vec3 lookat(0.f, 0.5f, 0.f);
	float distToFocus = (lookfrom - lookat).length();
	float aperture = 2.f;
	camera Cam(lookfrom, lookat, vec3(0.f, 1.f, 0.f), 60, float(nx) / float(ny), aperture, distToFocus);
	//camera Cam(vec3(-2.f,2.f,1.f),vec3(0.f,0.f,-1.f),vec3(0.f,1.f,0.f),
	//	50.f,float(nx)/float(ny));

	for (int j = ny - 1; j >= 0; j--)
	{
		std::cout << "Rendering: " << float(ny - j)*100 / ny <<"%"<< std::endl;
		for (int i = 0; i < nx; i++)
		{
			vec3 col(0.f, 0.f, 0.f);
			for (int s = 0; s < ns; s++) 
			{
				float u1 = static_cast<float>(i) + rand1();
				float v1 = static_cast<float>(j) + rand1();
				float u = u1 / static_cast<float>(nx);
				float v = v1 / static_cast<float>(ny);
				
				ray r = Cam.getRay(u, v);
				vec3 o = r.getOrigin();
				vec3 dir = r.getDirection();
				col += color(r, world, 0);
			}
			col /= static_cast<float>(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			fout << ir << ' ' << ig << ' ' << ib << std::endl;
		}
	}
}