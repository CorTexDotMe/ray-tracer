#pragma once
#include <random>

inline double randomDouble() {
    static std::random_device randomNumbersFromHardware;
    static std::mt19937 generator(randomNumbersFromHardware());

    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

inline double randomDouble(double min, double max) {
    static std::random_device randomNumbersFromHardware;
    static std::mt19937 generator(randomNumbersFromHardware());

    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}