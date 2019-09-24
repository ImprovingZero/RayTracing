#pragma once

#include"hitable.h"
#include"stdafx.h"
#include"material.h"
#include"sphere.h"

class hitable_list: public hitable
{
public:
	std::vector<hitable*> _list;

	inline const int size() const { return _list.size(); };
	hitable_list() { _list.clear(); }
	hitable_list(std::vector<hitable*>& l) :_list(l) {};

	hitable* randomScene(int n = 300);
	virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& rec) const;
};

