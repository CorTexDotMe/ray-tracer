#define STB_IMAGE_IMPLEMENTATION

#include "Textures.h"

color Checker::value(const double u, const double v, const vec3& point) const
{
	// Checker on top
	double value = sin(10 * point.x) * sin(10 * point.z);
	// Checker from left to right
	// double value = sin(10*point.x) * sin(10*point.y);
	if (value < 0)
		return odd->value(u, v, point);
	else
		return even->value(u, v, point);

}

Image::Image(const char* filename)
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

color Image::value(const double u, const double v, const vec3& point) const
{
	if (!data)
		return color(1.0, 0.0, 1.0);

	int i = static_cast<int>(clamp(u, 0.0, 1.0) * width);
	int j = static_cast<int>((1 - clamp(v, 0.0, 1.0)) * height);

	if (i >= width) i = width - 1;
	if (j >= height) j = height - 1;

	unsigned int pixelIndex = i * bytesPerPixel + j * bytesPerRow;
	double scaler = 1.0 / 255.0;

	return color(scaler * data[pixelIndex], scaler * data[pixelIndex + 1], scaler * data[pixelIndex + 2]);
}
