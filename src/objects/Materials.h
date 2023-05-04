#pragma once
#include "IHittable.h"
#include "Textures.h"

struct hitRecord;

class Material
{
public:
	
	virtual color emitted(const double u, const double v, const vec3& point) const { return color(0, 0, 0); }
	virtual bool scatter(const ray& inputRay, const hitRecord& record, color& attenuation, ray& scattered) const = 0;
};

class Matte : public Material
{
public:
	Matte(const color& color) : albedo(std::make_shared<SolidColor>(color)) {}
	Matte(std::shared_ptr<Texture> texture) : albedo(texture) {}

	bool scatter(const ray& inputRay, const hitRecord& record, color& attenuation, ray& scattered) const override;
private:
	std::shared_ptr<Texture> albedo;
};

class Metal : public Material {
public:
	Metal(const color& a, double f = 0) : albedo(a), fuzz(f < 1 ? f : 1) {}

	bool scatter(const ray& inputRay, const hitRecord& record, color& attenuation, ray& scattered) const override;

private:
	color albedo;
	double fuzz;
};

class Dielectric : public Material 
{
public:
	Dielectric(double indexOfRefract): indexOfRefraction(indexOfRefract) {}

	bool scatter(const ray& inputRay, const hitRecord& record, color& attenuation, ray& scattered) const override;

private:
	double indexOfRefraction;
	
	static double reflectance(double cosine, double refraction);
};

class Light : public Material
{
public:
	Light(color color):albedo(std::make_shared<SolidColor>(color)) {}

	bool scatter(const ray& inputRay, const hitRecord& record, color& attenuation, ray& scatterd) const override
	{
		return false;
	}

	color emitted(const double u, const double v, const vec3& point) const override
	{
		return albedo->value(u, v, point);
	}

private:
	std::shared_ptr<Texture> albedo;
};