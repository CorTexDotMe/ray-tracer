#pragma once
#include <vector>
#include "../objects/IHittable.h"


class Scene 
{
public:
	Scene() {}

	void add(std::shared_ptr<IHittable> IHittable) { objects.push_back(IHittable); }
	void clear() { objects.clear(); }

	bool traceRay(double tMin, double tMax, const ray& ray, hitRecord& record);


private:
	std::vector<std::shared_ptr<IHittable>> objects;
};
