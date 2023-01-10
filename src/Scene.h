#pragma once
#include <vector>
#include "objects/Hittable.h"


class Scene 
{
public:
	Scene() {}
	Scene(std::shared_ptr<Hittable> Hittable) {}

	void add(std::shared_ptr<Hittable> Hittable) { objects.push_back(Hittable); }
	void clear() { objects.clear(); }

	bool traceRay(double tMin, double tMax, const ray& ray, hitRecord& record);


private:
	std::vector<std::shared_ptr<Hittable>> objects;
};

bool Scene::traceRay(double tMin, double tMax, const ray& ray, hitRecord& record)
{
	hitRecord recordForClosestHit;
	double closestHit = tMax;
	bool hitAnything = false;


	for (const auto& object : objects)
	{
		if (object->hit(tMin, closestHit, ray, recordForClosestHit))
		{
			hitAnything = true;
			closestHit = recordForClosestHit.t;
			record = recordForClosestHit;
		}
	}

	return hitAnything;
}
