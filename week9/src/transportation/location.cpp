#include "location.hpp"
#include <iostream>

// Simple calculation for distance.
// A real implementation would use the Haversine formula.
double transportation::Location::distance_to(const Location& other) const {
    std::cout << "Calculating distance..." << '\n';
    double d_lat = latitude_ - other.latitude_;
    double d_lon = longitude_ - other.longitude_;
    return std::sqrt(d_lat * d_lat + d_lon * d_lon);
}