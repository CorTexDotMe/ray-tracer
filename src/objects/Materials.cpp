#include "Materials.h"

bool Matte::scatter(const ray& inputRay, const hitRecord& record, color& attenuation, ray& scattered) const
{
	vec3 scatterDirection = record.normal + unitVector(randomInUnitSphere());

	if (scatterDirection.nearZero())
		scatterDirection = record.normal;

	scattered = ray(record.point, scatterDirection);
	attenuation = albedo->value(record.u, record.v, record.point);
	return true;
}

bool Metal::scatter(const ray& inputRay, const hitRecord& record, color& attenuation, ray& scattered) const
{
	vec3 reflected = reflect(unitVector(inputRay.direction()), record.normal);
	scattered = ray(record.point, reflected + fuzz * randomInUnitSphere());
	attenuation = albedo;
	return (dot(scattered.direction(), record.normal) > 0);
}

bool Dielectric::scatter(const ray& inputRay, const hitRecord& record, color& attenuation, ray& scattered) const
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

double Dielectric::reflectance(double cosine, double refraction)
{
	double r0 = (1 - refraction) / (1 + refraction);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}
