#pragma once

#include "objects/primitives/Sphere.h"
#include "objects/Materials.h"

#include "world/Scene.h"
#include "camera/Camera.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <cfloat>

#include <execution>

class RayTracer
{
public:
	RayTracer(int imageWidth = 1280, int imageHeight = 720) :
		imageWidth(imageWidth), imageHeight(imageHeight),
		imageData(std::make_shared<std::vector<unsigned char>>(imageWidth * imageHeight * 4, 128)),
		scene(getDefaultScene()),
		camera(getDefaultCamera()),
		samplesPerPixel(100), rayMaxDepth(50) {}

	RayTracer(
		std::shared_ptr<Scene> worldScene,
		std::shared_ptr<Camera> cameraForScene,
		int amountOfSamplesPerPixel = 100,
		int rayMaxAmountOfReflections = 50,
		int imageWidth = 1280,
		int imageHeight = 720
	) :
		imageWidth(imageWidth), imageHeight(imageHeight),
		imageData(std::make_shared<std::vector<unsigned char>>(imageWidth* imageHeight * 4, 128)),
		scene(worldScene),
		camera(cameraForScene),
		samplesPerPixel(amountOfSamplesPerPixel), rayMaxDepth(rayMaxAmountOfReflections)

	{}

	void run(bool showProgressPercentage = true) const;
	void runWithTimeInfo(bool showProgressPercentage = true) const;
	void runParallel() const;
	void runParallelWithTimeInfo() const;

	std::shared_ptr<std::vector<unsigned char>> getImageData() const { return imageData; }

	int getImageWidth() const { return imageWidth; }
	int getImageHeight() const { return imageHeight; }

	int getRayMaxDepth() const { return rayMaxDepth; }
	void setRayMaxDepth(int rayMaxAmountOfReflections) { rayMaxDepth = rayMaxAmountOfReflections; }

	int getSamplesPerPixel() const { return samplesPerPixel; }
	void setSamplesPerPixel(int amountOfSamplesPerPixel) { samplesPerPixel = amountOfSamplesPerPixel; }

private:
	int imageWidth;
	int imageHeight;

	std::shared_ptr<std::vector<unsigned char>> imageData;
	std::shared_ptr<Scene> scene;
	std::shared_ptr<Camera> camera;
	int samplesPerPixel;
	int rayMaxDepth;

	std::shared_ptr<Scene> getDefaultScene() const;
	std::shared_ptr<Camera> getDefaultCamera() const;

	color traceRay(const ray& r, int depth) const;
	void writeColor(const color& pixelColor, int samplesPerPixel, int, int, int) const;
};