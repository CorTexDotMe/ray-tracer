#pragma once
#include "ray.h"
#include "Hittable.h"
#include <cmath>

struct hitRecord;

class Material
{
public:
	virtual bool scatter(const ray& inputRay, const hitRecord& record, color& attenuation, ray& scattered) const = 0;
};

class Matte : public Material
{
public:
	Matte(const color& a) : albedo(a) {}

	virtual bool scatter(const ray& inputRay, const hitRecord& record, color& attenuation, ray& scattered) const override
	{
		vec3 scatterDirection = record.normal + randomInUnitSphere();

		if (scatterDirection.nearZero())
			scatterDirection = record.normal;

		scattered = ray(record.point, scatterDirection);
		attenuation = albedo;
		return true;
	}
private:
	color albedo;
};

class Metal : public Material {
public:
	Metal(const color& a, double f = 0) : albedo(a), fuzz(f < 1 ? f : 1) {}

	virtual bool scatter(const ray& inputRay, const hitRecord& record, color& attenuation, ray& scattered) const override
	{
		vec3 reflected = reflect(unitVector(inputRay.direction()), record.normal);
		scattered = ray(record.point, reflected + fuzz * randomInUnitSphere());
		attenuation = albedo;
		return (dot(scattered.direction(), record.normal) > 0);
	}

private:
	color albedo;
	double fuzz;
};

class Dielectric : public Material 
{
public:
	Dielectric(double indexOfRefract): indexOfRefraction(indexOfRefract) {}

	virtual bool scatter(const ray& inputRay, const hitRecord& record, color& attenuation, ray& scattered) const override
	{
		attenuation = color(1.0, 1.0, 1.0);
		double refractionRatio = record.frontFace ? (1.0 / indexOfRefraction) : indexOfRefraction;

		vec3 inputRayDirectionNormalized = unitVector(inputRay.direction());
		double cosTheta = fmin(dot(-inputRayDirectionNormalized, record.normal), 1.0);
		double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

		vec3 direction;
		bool cannotRefract = refractionRatio * sinTheta > 1.0;
		if (cannotRefract || reflectance(cosTheta, refractionRatio) > randomDouble())
			direction = reflect(inputRayDirectionNormalized, record.normal);
		else
			direction = refract(inputRayDirectionNormalized, record.normal, refractionRatio);


		scattered = ray(record.point, direction);
		return true;
	}

private:
	double indexOfRefraction;
	
	static double reflectance(double cosine, double refraction)
	{
		double r0 = (1 - refraction) / (1 + refraction);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
};