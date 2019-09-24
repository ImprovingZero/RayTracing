#pragma once

#include"hitable.h"
#include"stdafx.h"

class hitable_list: public hitable
{
public:
	std::vector<hitable*> list;

	inline const int size() const { return list.size(); };
	hitable_list() { list.clear(); }
	hitable_list(std::vector<hitable*>& l) :list(l) {};
	virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& rec) const;
};

