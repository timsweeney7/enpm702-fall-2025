#include "route.hpp"
#include <iostream>

void transportation::Route::add_waypoint(const Location &location)
{
    waypoints_.push_back(location);
    std::cout << "Added waypoint to route " << id_ << '\n';
}

void transportation::Route::optimize_route()
{
    std::cout << "Optimizing route " << id_ << "..." << '\n';
    // Logic for route optimization (e.g., TSP algorithm)
}

double transportation::Route::get_distance() const
{
    double total_distance = 0.0;
    if (waypoints_.size() < 2)
    {
        return total_distance;
    }

    for (size_t i = 0; i < waypoints_.size() - 1; ++i)
    {
        total_distance += waypoints_[i].distance_to(waypoints_[i + 1]);
    }
    return total_distance;
}