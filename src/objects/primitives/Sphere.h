#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "../IHittable.h"

class Sphere : public IHittable
{
public:
	Sphere() {}
	Sphere(vec3 cen, double r, std::shared_ptr<Material> m): center(cen), radius(r), materialPtr(m) {}

	bool hit(double t_min, double t_max, const ray& ray, hitRecord& record) const override;


private:
	vec3 center;
	double radius;
	std::shared_ptr<Material> materialPtr;

	static void getSphereUV(const vec3& point, double& u, double& v);
};