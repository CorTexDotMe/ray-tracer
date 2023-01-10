#pragma once
#include "Hittable.h"

class Sphere : public Hittable
{
public:
	Sphere() {}
	Sphere(vec3 cen, double r, std::shared_ptr<Material> m): center(cen), radius(r), materialPtr(m) {}

	virtual bool hit(double t_min, double t_max, const ray& ray, hitRecord& record) const override;

public:
	vec3 center;
	double radius;
	std::shared_ptr<Material> materialPtr;
};

bool Sphere::hit(double t_min, double t_max, const ray& r, hitRecord& record) const 
{
	ray ray(r.origin() - center, r.direction());

	double a = dot(ray.direction(), ray.direction());
	double b = 2.0 * dot(ray.origin(), ray.direction());
	double c = dot(ray.origin(), ray.origin()) - radius * radius;

	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return false;

	
	double t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t < t_min || t_max < t)
	{
		t = (-b + sqrt(discriminant)) / (2.0 * a);
		if (t < t_min || t_max < t)
			return false;
	}

	record.t = t;
	record.point = r.at(record.t);
	vec3 normal = (record.point - center) / radius;
	record.setFaceOfNormal(r, normal);
	record.materialPtr = materialPtr;

	return true;
}