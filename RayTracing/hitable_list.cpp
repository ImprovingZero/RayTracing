#include "hitable_list.h"

bool hitable_list::hit(const ray& r, float tMin, float tMax, hitRecord& rec) const
{
	hitRecord tempRec;
	bool hitAnything = 0;
	double closest = tMax;
	for (unsigned int i = 0; i < list.size(); i++)
	{
		if (list[i]->hit(r, tMin, float(closest), tempRec))
		{
			hitAnything = true;
			closest = tempRec.t;
			rec = tempRec;
		}
	}
	/*
	for (auto &i : list)
	{
		if (i.hit(r, tMin, closest, tempRec))
		{
			hitAnything = true;
			closest = tempRec.t;
			rec = tempRec;
		}
	}
	*/
	return hitAnything;
}
