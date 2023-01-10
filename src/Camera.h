#pragma once
#define _USE_MATH_DEFINES

#include <cmath>
#include "utils/vec3.h"
#include "utils/ray.h"

class Camera {


public:
	Camera(
		vec3 lookFrom,
		vec3 lookAt,
		vec3 vectorUp,
		double verticalFOV,
		double aspectRatio,
		double aperture,
		double focusDist
	): origin(lookFrom), lensRadius(aperture / 2) {
		double radiansFOV = verticalFOV * (M_PI / 180);
		double viewportHeight = 2.0 * tan(radiansFOV / 2);
		double viewportWidth = viewportHeight * aspectRatio;

		vec3 lookAtDirection = unitVector(lookFrom - lookAt);
		horizontalDirection = unitVector(cross(vectorUp, lookAtDirection));
		verticalDirection = cross(lookAtDirection, horizontalDirection);

		
		horizontal = focusDist * viewportWidth * horizontalDirection;
		vertical = focusDist * viewportHeight * verticalDirection;
		lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - focusDist * lookAtDirection;
	}

	ray getRay(double x, double y) const {
		//vec3 rayDirection = lensRadius * randomInUnitDisk();
		//vec3 offset = horizontalDirection * rayDirection.x() + verticalDirection * rayDirection.y();

		//return ray(origin + offset, lowerLeftCorner + x * horizontal + y * vertical - origin - offset);
		return ray(origin, lowerLeftCorner + x * horizontal + y * vertical - origin);
	}

private:
	vec3 origin;
	vec3 lowerLeftCorner;
	vec3 horizontal;
	vec3 horizontalDirection;
	vec3 vertical;
	vec3 verticalDirection;
	double lensRadius;
};