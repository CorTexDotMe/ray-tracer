#pragma once

#include "objects/primitives/Sphere.h"
#include "objects/Materials.h"

#include "world/Scene.h"
#include "camera/Camera.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <cfloat>


class RayTracer
{
public:
	RayTracer() :
		scene(getDefaultScene()),
		camera(getDefaultCamera()),
		samplesPerPixel(100), rayMaxDepth(50) {}

	RayTracer(
		std::shared_ptr<Scene> worldScene,
		std::shared_ptr<Camera> cameraForScene,
		int amountOfSamplesPerPixel = 100,
		int rayMaxAmountOfReflections = 50
	) :
		scene(worldScene),
		camera(cameraForScene),
		samplesPerPixel(amountOfSamplesPerPixel), rayMaxDepth(rayMaxAmountOfReflections) {}

	void run(bool showProgressPercentage = true) const;
	void runWithDebugInfo() const;

	int getRayMaxDepth() const { return rayMaxDepth; }
	void setRayMaxDepth(int rayMaxAmountOfReflections) { rayMaxDepth = rayMaxAmountOfReflections; }

	int getSamplesPerPixel() const { return samplesPerPixel; }
	void setSamplesPerPixel(int amountOfSamplesPerPixel) { samplesPerPixel = amountOfSamplesPerPixel; }

private:
	const int imageWidth = 1280;
	const int imageHeight = 720;

	std::shared_ptr<Scene> scene;
	std::shared_ptr<Camera> camera;
	int samplesPerPixel;
	int rayMaxDepth;

	std::shared_ptr<Scene> getDefaultScene() const;
	std::shared_ptr<Camera> getDefaultCamera() const;

	color traceRay(const ray& r, int depth) const;
	void writeColor(std::ofstream& out, const color& pixelColor, int samplesPerPixel) const;
};