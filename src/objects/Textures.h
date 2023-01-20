#pragma once
#include "../utils/vec3.h"

class Texture
{
public:
	virtual color value(double u, double v, const vec3& point) const = 0;
};

class SolidColor : public Texture
{
public:
	SolidColor(color c) : solidColor(c) {}
	SolidColor(double red, double green, double blue) : solidColor(red, green, blue) {}

	color value(double u, double v, const vec3& point) const override
	{
		return solidColor;
	}

private:
	color solidColor;
};

class Checker : public Texture
{
public:
	Checker(color first, color second) : 
		odd(std::make_shared<SolidColor>(first)), 
		even(std::make_shared<SolidColor>(second)) {}

	color value(double u, double v, const vec3& point) const override
	{
		// Checker on top
		double value = sin(10*point.x) * sin(10*point.z);
		// Checker from left to right
		// double value = sin(10*point.x) * sin(10*point.y);
		if (value < 0)
			return odd->value(u, v, point);
		else
			return even->value(u, v, point);

	}

private:
	std::shared_ptr<Texture> odd;
	std::shared_ptr<Texture> even;
};