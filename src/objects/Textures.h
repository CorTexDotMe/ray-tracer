#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include "../utils/vec3.h"
#include "../utils/utils.h"
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

	color value(const double u, const double v, const vec3& point) const override
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

class Image : public Texture
{
public:
	Image(const char* filename)
	{
		int components;
		data = stbi_load(filename, &width, &height, &components, bytesPerPixel);

		if (!data)
		{
			std::cout << "Failed to load image: " << filename << std::endl;
			width = 0;
			height = 0;
		}

		bytesPerRow = bytesPerPixel * width;
	}

	color value(const double u, const double v, const vec3& point) const override
	{
		if (!data)
			return color(1.0, 0.0, 1.0);

		int i = static_cast<int>(clamp(u, 0.0, 1.0) * width);
		int j = static_cast<int>((1 - clamp(v, 0.0, 1.0)) * height);

		if (i >= width) i = width - 1;
		if (j >= height) j = height - 1;

		unsigned char* pixel = data + i * bytesPerPixel + j * bytesPerRow;
		double scaler = 1.0 / 255.0;

		return color(scaler * pixel[0], scaler * pixel[1], scaler * pixel[2]);
	}

private:
	const static int bytesPerPixel = 3;
	unsigned char* data;
	int width;
	int height;
	int bytesPerRow;
};