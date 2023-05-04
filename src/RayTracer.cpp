#include "RayTracer.h"

void RayTracer::writeColor(std::ofstream& out, const color& pixelColor, int samplesPerPixel) const
{
	double scale = 1.0 / samplesPerPixel;
	double r = sqrt(pixelColor.r() * scale);
	double g = sqrt(pixelColor.g() * scale);
	double b = sqrt(pixelColor.b() * scale);


	out << static_cast<int>(255 * clamp(r, 0, 1)) << ' '
		<< static_cast<int>(255 * clamp(g, 0, 1)) << ' '
		<< static_cast<int>(255 * clamp(b, 0, 1)) << std::endl;
}

color RayTracer::traceRay(const ray& r, int depth) const
{
	hitRecord record;

	if (depth <= 0)
		return color(0, 0, 0);

	if (scene->traceRay(0.001, DBL_MAX, r, record))
	{
		ray scattered;
		color attenuation;
		color emitted = record.materialPtr->emitted(record.u, record.v, record.point);
		if (record.materialPtr->scatter(r, record, attenuation, scattered))
			return emitted + attenuation * traceRay(scattered, depth - 1);
		return emitted;
	}


	return color(0.5, 0.7, 1.0); // background color
	//return color(0.0, 0.0, 0.0); // background color
}

void RayTracer::run(bool showProgressPercentage) const
{
	std::ofstream file("image.ppm");
	file << "P3" << std::endl;
	file << imageWidth << ' ' << imageHeight << ' ' << 255 << std::endl;


	for (int y = imageHeight; y >= 0; y--)
	{
		if (showProgressPercentage)
			std::cout << 100 - static_cast<int> (static_cast<float>(y) / (imageHeight - 1) * 100) << "%" << std::endl;

		for (int x = 0; x < imageWidth; x++)
		{
			color pixelColor(0, 0, 0);
			for (int i = 0; i < samplesPerPixel; i++) {
				double xCoord = (x + randomDouble()) / imageWidth;
				double yCoord = (y + randomDouble()) / imageHeight;

				ray perPixelRay = camera->getRay(xCoord, yCoord);
				pixelColor += traceRay(perPixelRay, rayMaxDepth);
			}
			writeColor(file, pixelColor, samplesPerPixel);
		}
	}
	file.close();
}

void RayTracer::runWithDebugInfo() const
{
	auto start = std::chrono::high_resolution_clock::now();

	run();

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "Done in: " << duration.count() << " miliseconds" << std::endl
		<< duration.count() / 1000.0 << " seconds" << std::endl
		<< duration.count() / 60000.0 << " minutes" << std::endl;
}


void addRandomShere(Scene& scene, vec3 sphereCenter)
{
	double randomForMaterial = randomDouble();
	if (randomForMaterial < 0.4)
	{
		color albedo = randomVector();
		auto matteMaterial = std::make_shared<Matte>(albedo);
		scene.add(std::make_shared<Sphere>(sphereCenter, 0.2, matteMaterial));
	}
	else if (randomForMaterial < 0.8)
	{
		color albedo = randomVector();
		double fuzz = randomDouble();
		auto metalMaterial = std::make_shared<Metal>(albedo, fuzz);
		scene.add(std::make_shared<Sphere>(sphereCenter, 0.2, metalMaterial));
	}
	else
	{
		auto dielectricMaterial = std::make_shared<Dielectric>(1.5);
		scene.add(std::make_shared<Sphere>(sphereCenter, 0.2, dielectricMaterial));

	}
}

std::shared_ptr<Scene> RayTracer::getDefaultScene() const
{
	auto scene = std::make_shared<Scene>();

	// Floor
	auto checker = std::make_shared<Checker>(color(0.6, 0.6, 0.5), color(0.0, 0.0, 0.0));
	auto groundMaterial = std::make_shared<Matte>(checker);
	scene->add(std::make_shared<Sphere>(vec3(0.0, -100, 0.0), 100.0, groundMaterial));


	scene->add(std::make_shared<Sphere>(vec3(-2.0, 3, 0.0), 1, std::make_shared<Light>(color(20, 20, 20))));
	//auto matteMaterial = std::make_shared<Matte>(color(0.9, 0.3, 0.3));

	auto metalMaterial = std::make_shared<Metal>(color(0.7, 0.6, 0.6), 0.0);
	scene->add(std::make_shared<Sphere>(vec3(2.0, 1, 0.0), 1, metalMaterial));

	auto matteMaterial = std::make_shared<Matte>(std::make_shared<Image>("resources/textures/jupiter.jpg"));
	scene->add(std::make_shared<Sphere>(vec3(0.0, 1, 0.0), 1, matteMaterial));

	//auto refractMaterial = std::make_shared<Dielectric>(1.5);
	//scene->add(std::make_shared<Sphere>(vec3(-2.0, 1, 0.0), 1, refractMaterial));


	/*
	for (double z = 1; z < 2; z += 0.2)
	{
		addRandomShere(scene, vec3(randomDouble(-5, -3), 0.2, z));
		addRandomShere(scene, vec3(randomDouble(-3, -0), 0.2, z));
		addRandomShere(scene, vec3(randomDouble(0, 2), 0.2, z));
		addRandomShere(scene, vec3(randomDouble(2, 4), 0.2, z));
	}
	*/
	return scene;
}

std::shared_ptr<Camera> RayTracer::getDefaultCamera() const
{
	const double aspectRatio = static_cast<double>(imageWidth) / imageHeight;

	vec3 lookFrom(0, 3, 8);
	vec3 lookAt(0, 0, -3);
	vec3 vectorUp(0, 1, 0);
	double verticalFOV = 40;
	double aperture = 0.0;
	double distanceToFocus = (lookFrom - lookAt).length();

	return std::make_shared<Camera>(lookFrom, lookAt, vectorUp, verticalFOV, aspectRatio, aperture, distanceToFocus);
}