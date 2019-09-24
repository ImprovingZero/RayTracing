#include "hitable_list.h"

bool hitable_list::hit(const ray& r, float tMin, float tMax, hitRecord& rec) const
{
	hitRecord tempRec;
	bool hitAnything = 0;
	double closest = tMax;
	for (unsigned int i = 0; i < _list.size(); i++)
	{
		if (_list[i]->hit(r, tMin, float(closest), tempRec))
		{
			hitAnything = true;
			closest = tempRec.t;
			rec = tempRec;
		}
	}
	return hitAnything;
}

hitable* hitable_list::randomScene(int n)
{
	_list.clear();
	_list.push_back(new sphere(vec3(0.f, -1000.f, 0.f), 1000.f, new lambertian(vec3(0.5f, 0.5f, 0.5f))));
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			using namespace tools;
			float choose_mat = rand1();
			vec3 center(a + 0.9f * rand1(), 0.2f, b + 0.9f * rand1());
			if ((center - vec3(4.f, 0.2f, 0.f)).length() > 0.9f)
			{
				if (choose_mat < 0.8f)
				{
					_list.push_back(new sphere(center, 0.2f, new lambertian(vec3(rand1() * rand1(), rand1() * rand1(), rand1() * rand1()))));
				}
				else if (choose_mat < 0.95f)
				{
					_list.push_back(new sphere(center, 0.2f,
						new smooth(vec3(0.5f * (1 + rand1()), 0.5f * (1 + rand1()), 0.5f * (1 + rand1())), 0.5f * rand1())));
				}
				else {
					_list.push_back(new sphere(center, 0.2f, new transparent(1.5f)));
				}
			}
		}
	}
	_list.push_back(new sphere(vec3(0.f, 1.f, 0.f), 1.f, new transparent(1.5f)));
	_list.push_back(new sphere(vec3(-4.f, 1.f, 0.f), 1.f, new lambertian(vec3(0.4f, 0.2f, 0.1f))));
	_list.push_back(new sphere(vec3(4.f, 1.f, 0.f), 1.f, new smooth(vec3(0.7f, 0.6f, 0.5f), 0.f)));

	return this;
}
