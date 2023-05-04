#include "Scene.h"

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