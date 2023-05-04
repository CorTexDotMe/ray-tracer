#pragma once

#include "../utils/ray.h"
#include <memory>
class Material;


struct hitRecord
{
	vec3 point;
	vec3 normal;
	std::shared_ptr<Material> materialPtr;
	double t;
	double u;
	double v;
	bool frontFace;

	void setFaceOfNormal(const ray& r, const vec3 outNormal)
	{
		frontFace = dot(r.direction(), outNormal) < 0;
		normal = frontFace ? outNormal : -outNormal;
	}
};

class IHittable
{
public:
	virtual ~IHittable() {};
	virtual bool hit(double t_min, double t_max, const ray& r, hitRecord& record) const = 0;
};