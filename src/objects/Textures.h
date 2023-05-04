#pragma once

#include "../utils/ray.h"
#include "stb_image.h"

class Texture
{
public:
	virtual color value(const double u, const double v, const vec3& point) const = 0;
};

class SolidColor : public Texture
{
public:
	SolidColor(color c) : solidColor(c) {}
	SolidColor(double red, double green, double blue) : solidColor(red, green, blue) {}

	color value(const double u, const double v, const vec3& point) const override
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

	color value(const double u, const double v, const vec3& point) const override;

private:
	std::shared_ptr<Texture> odd;
	std::shared_ptr<Texture> even;
};

class Image : public Texture
{
public:
	Image(const char* filename);

	color value(const double u, const double v, const vec3& point) const override;

private:
	const static int bytesPerPixel = 3;
	unsigned char* data;
	int width;
	int height;
	int bytesPerRow;
};