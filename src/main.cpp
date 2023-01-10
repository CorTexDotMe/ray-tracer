#include "Camera.h"
#include "utils/vec3.h"
#include "utils/ray.h"
#include "objects/Sphere.h"
#include "Scene.h"
#include "objects/Materials.h"
#include <iostream>
#include <fstream>
#include <chrono>

void writeColor(std::ofstream& out, const color& pixelColor, int samplesPerPixel)
{
	double scale = 1.0 / samplesPerPixel;
	double r = sqrt(pixelColor.r() * scale);
	double g = sqrt(pixelColor.g() * scale);
	double b = sqrt(pixelColor.b() * scale);


	out << static_cast<int>(255 * clamp(r, 0, 1)) << ' '
		<< static_cast<int>(255 * clamp(g, 0, 1)) << ' '
		<< static_cast<int>(255 * clamp(b, 0, 1)) << std::endl;
}

color backgroundColor()
{
	return color(0.5, 0.7, 1.0);
}

color traceRay(Scene& scene, const ray& r, int depth)
{
	hitRecord record;

	if (depth <= 0)
		return color(0, 0, 0);

	if (scene.traceRay(0.001, DBL_MAX, r, record))
	{
		ray scattered;
		color attenualtion;
		if(record.materialPtr->scatter(r, record, attenualtion, scattered))
			return attenualtion * traceRay(scene, scattered, depth - 1);
		return color(0, 0, 0);
	}
	

	return color(0.5, 0.7, 1.0); // background color
}

void addRandomShere(Scene& world, vec3 sphereCenter)
{
	double randomForMaterial = randomDouble();
	if (randomForMaterial < 0.4)
	{
		color albedo = randomVector();
		auto matteMaterial = std::make_shared<Matte>(albedo);
		world.add(std::make_shared<Sphere>(sphereCenter, 0.2, matteMaterial));
	}
	else if (randomForMaterial < 0.8)
	{
		color albedo = randomVector();
		double fuzz = randomDouble();
		auto metalMaterial = std::make_shared<Metal>(albedo, fuzz);
		world.add(std::make_shared<Sphere>(sphereCenter, 0.2, metalMaterial));
	}
	else
	{
		auto dielectricMaterial = std::make_shared<Dielectric>(1.5);
		world.add(std::make_shared<Sphere>(sphereCenter, 0.2, dielectricMaterial));

	}
}

int main() 
{
	std::ofstream file("image.ppm");

	int imageWidth = 1280;
	int imageHeight = 720;
	//int imageWidth = 400;
	//int imageHeight = 255; 
	const double aspectRatio = static_cast<double>(imageWidth) / imageHeight;
	int samplesPerPixel = 100;
	int maxDepth = 50;


	vec3 lookFrom(0, 3, 8);
	vec3 lookAt(0, 0, -3);
	vec3 vectorUp(0, 1, 0);
	double aperture = 0.0;
	double distanceToFocus = (lookFrom - lookAt).length();

	Camera cam(lookFrom, lookAt, vectorUp, 40, aspectRatio, aperture, distanceToFocus);

	
	Scene world;
	auto groundMaterial = std::make_shared<Matte>(color(0.6, 0.6, 0.5));
	world.add(std::make_shared<Sphere>(vec3(0.0, -500, 0.0), 500.0, groundMaterial));

	auto metalMaterial = std::make_shared<Metal>(color(0.7, 0.6, 0.6), 0.0);
	world.add(std::make_shared<Sphere>(vec3(2.0, 1, 0.0), 1, metalMaterial));
	auto matteMaterial = std::make_shared<Matte>(color(0.9, 0.3, 0.3));
	world.add(std::make_shared<Sphere>(vec3(0.0, 1, 0.0), 1, matteMaterial));
	auto refractMaterial = std::make_shared<Dielectric>(1.5);
	world.add(std::make_shared<Sphere>(vec3(-2.0, 1, 0.0), 1, refractMaterial));

	for (double z = 1; z < 2; z += 0.2)
	{
		addRandomShere(world, vec3(randomDouble(-5, -3), 0.2, z));
		addRandomShere(world, vec3(randomDouble(-3, -0), 0.2, z));
		addRandomShere(world, vec3(randomDouble(0, 2), 0.2, z));
		addRandomShere(world, vec3(randomDouble(2, 4), 0.2, z));
	}
	

	/*
	Scene world;
	auto materialGround = std::make_shared<Matte>(color(0.8, 0.8, 0.0));
	auto materialCenter = std::make_shared<Matte>(color(0.1, 0.2, 0.5));
	auto materialLeft = std::make_shared<Dielectric>(1.5);
	auto materialRight = std::make_shared<Metal>(color(0.8, 0.6, 0.2), 0.0);
	auto materialAway = std::make_shared<Metal>(color(0.8, 0.6, 0.2), 0.5);

	world.add(std::make_shared<Sphere>(vec3( 0.0, -100.5, -1.0), 100.0, materialGround));
	world.add(std::make_shared<Sphere>(vec3( 0.0,    0.0, -1.0),   0.5, materialCenter));
	world.add(std::make_shared<Sphere>(vec3(-1.0,    0.0, -1.0),   0.5, materialLeft));
	world.add(std::make_shared<Sphere>(vec3(-1.0,    0.0, -1.0), -0.45, materialLeft));
	world.add(std::make_shared<Sphere>(vec3( 1.0,    0.0, -1.0),   0.5, materialRight));
	world.add(std::make_shared<Sphere>(vec3(0.0, 0.0, -2.5), 0.5, materialAway));
	*/


	/*
	for(int x = -10; x < 10; x+=2)
		for (int y = -10; y < 10; y+=2)
		{
			vec3 sphereCenter(x * 0.7 * randomDouble(), 0.4, y * 0.7 * randomDouble());
			double randomForMaterial = randomDouble(0, 30);

			if (randomForMaterial < 10)
			{
				color albedo = randomVector();
				auto matteMaterial = std::make_shared<Matte>(albedo);
				world.add(std::make_shared<Sphere>(sphereCenter, 0.2, matteMaterial));
			}
			else if (randomForMaterial < 20)
			{
				color albedo = randomVector();
				double fuzz = randomDouble();
				auto metalMaterial = std::make_shared<Metal>(albedo, fuzz);
				world.add(std::make_shared<Sphere>(sphereCenter, 0.2, metalMaterial));
			}
			else
			{
				auto dielectricMaterial = std::make_shared<Dielectric>(1.5);
				world.add(std::make_shared<Sphere>(sphereCenter, 0.2, dielectricMaterial));

			}
		}
			
	auto groundMaterial = std::make_shared<Matte>(color(0.6, 0.6, 0.4));
	world.add(std::make_shared<Sphere>(vec3(0.0, -500, 0.0), 500.0, groundMaterial));

	auto dielectricMaterial = std::make_shared<Dielectric>(1.5);
	world.add(std::make_shared<Sphere>(vec3(-3, 1.5, 1.0), 1.5, dielectricMaterial));

	auto metalMaterial = std::make_shared<Metal>(color(0.7, 0.7, 0.6), 0.0);
	world.add(std::make_shared<Sphere>(vec3(0, 1.5, 0.0), 1.5, metalMaterial));

	auto matteMaterial = std::make_shared<Matte>(color(0.9, 0.9, 0.3));
	world.add(std::make_shared<Sphere>(vec3(3.0, 1.5, -1.0), 1.5, matteMaterial));

	*/

	

	



	file << "P3" << std::endl;
	file << imageWidth << ' ' << imageHeight << ' ' << 255 <<  std::endl;

	auto start = std::chrono::high_resolution_clock::now();
	for (int y = imageHeight; y >= 0; y--)
	{
//#ifndef NDEBUG
		std::cout << 100 - static_cast<int> (static_cast<float>(y) / (imageHeight - 1) * 100) << "%" << std::endl;
//#endif // !NDUBUG

		for (int x = 0; x < imageWidth; x++)
		{
			color pixelColor(0, 0, 0);
			for (int i = 0; i < samplesPerPixel; i++) {
				double xCoord = (x + randomDouble()) / imageWidth;
				double yCoord = (y + randomDouble()) / imageHeight;

				ray perPixelRay = cam.getRay(xCoord, yCoord);
				pixelColor += traceRay(world, perPixelRay, maxDepth);
			}
			writeColor(file, pixelColor, samplesPerPixel);
		}
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "Done in: " << duration.count() << " miliseconds" << std::endl
			  << duration.count() / 1000.0 << " seconds" << std::endl
		      << duration.count() / 60000.0 << " minutes" << std::endl;
	file.close();
}