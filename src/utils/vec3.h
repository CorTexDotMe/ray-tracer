#pragma once
#include <cmath>
#include <iostream>
#include "utils.h"

class vec3
{
public:
    double x, y, z;

	vec3(): x(0), y(0), z(0) {}
	vec3(double x, double y, double z): x(x), y(y), z(z) {}

    const double r() const { return x; }
    const double g() const { return y; }
    const double b() const { return z; }

    double r() { return x; }
    double g() { return y; }
    double b() { return z; }

    vec3 operator-() const { return vec3(-x, -y, -z); }

    vec3& operator+=(const vec3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    vec3& operator*=(const double t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    vec3& operator/=(const double t) {
        return *this *= 1 / t;
    }

    double length() const {
        return sqrt(lengthSquared());
    }

    double lengthSquared() const {
        return x * x + y * y + z * z;
    }

    bool nearZero() const 
    {
        const double zeroThreshold = 1e-8;
        return
            fabs(x) < zeroThreshold &&
            fabs(y) < zeroThreshold &&
            fabs(z) < zeroThreshold;
    }
};


std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

vec3 operator+(const vec3 u, const vec3 v) {
    return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

vec3 operator+(const vec3 u, double x) {
    return vec3(u.x + x, u.y + x, u.z + x);
}

vec3 operator-(const vec3 u, const vec3 v) {
    return vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

vec3 operator*(const vec3 u, const vec3 v) {
    return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

vec3 operator*(double t, const vec3 v) {
    return vec3(t * v.x, t * v.y, t * v.z);
}

vec3 operator*(const vec3 v, double t) {
    return t * v;
}

vec3 operator/(vec3 v, double t) {
    return (1 / t) * v;
}

double dot(const vec3& u, const vec3& v) {
    return u.x * v.x
        + u.y * v.y
        + u.z * v.z;
}

vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x);
}

vec3 unitVector(vec3 v) {
    return v / v.length();
}

vec3 randomVector() {
    return vec3(randomDouble(), randomDouble(), randomDouble());
}

vec3 randomVector(double min, double max) {
    return vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

vec3 randomInUnitSphere() {
    while (true)
    {
        vec3 candidate = randomVector(-1, 1);
        if (candidate.lengthSquared() >= 1) continue;
        return candidate;
    }
}

vec3 reflect(const vec3& v, const vec3& n)
{
    return v - 2 * dot(v, n) * n;
}

vec3 refract(const vec3& inVector, const vec3& normal, double refractionRatio)
{
    double cosTheta = fmin(dot(-inVector, normal), 1.0);
    vec3 refractedVectorPerpendicularPart = refractionRatio * (inVector + cosTheta * normal);
    vec3 refractedVectorParallelPart = -sqrt(fabs(1.0 - refractedVectorPerpendicularPart.lengthSquared())) * normal;
    return refractedVectorPerpendicularPart + refractedVectorParallelPart;
}

vec3 randomInUnitDisk()
{
    while (true)
    {
        vec3 candidate = vec3(randomDouble(-1, 1), randomDouble(-1, 1), 0);
        if (candidate.lengthSquared() >= 1) continue;
        return candidate;
    }
}

using color = vec3;