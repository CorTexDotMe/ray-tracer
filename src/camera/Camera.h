#pragma once
#include "../utils/ray.h"

class Camera {
public:
	Camera(
		vec3 lookFrom,
		vec3 lookAt,
		vec3 vectorUp,
		double verticalFOV,
		double aspectRatio
	): origin(lookFrom) {
		double radiansFOV = verticalFOV * (M_PI / 180);
		double viewportHeight = 2.0 * tan(radiansFOV / 2);
		double viewportWidth = viewportHeight * aspectRatio;

		vec3 lookAtDirection = unitVector(lookFrom - lookAt);
		vec3 horizontalDirection = unitVector(cross(vectorUp, lookAtDirection));
		vec3 verticalDirection = cross(lookAtDirection, horizontalDirection);

		
		horizontal = viewportWidth * horizontalDirection;
		vertical = viewportHeight * verticalDirection;
		lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - lookAtDirection;
	}

	ray getRay(double x, double y) const {
		return ray(origin, lowerLeftCorner + x * horizontal + y * vertical - origin);
	}

private:
	vec3 origin;
	vec3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
};