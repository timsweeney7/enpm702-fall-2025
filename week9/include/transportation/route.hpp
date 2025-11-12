#pragma once

#include "location.hpp"
#include <string>
#include <vector>
#include <memory>

namespace transportation
{

    // Represents a route with multiple waypoints.
    class Route
    {
    public:
        // Constructor
        Route(const std::string &id) : id_{id} {}

        // Getters
        [[nodiscard]] std::string get_id() const noexcept { return id_; }
        [[nodiscard]] const std::vector<Location> &get_waypoints() const noexcept { return waypoints_; }
        [[nodiscard]] int get_waypoint_count() const noexcept { return static_cast<int>(waypoints_.size()); }

        // Setters
        void set_id(const std::string &id) { id_ = id; }
        // No setter for waypoints, use add_waypoint

        // Other methods
        void add_waypoint(const Location &location);
        void optimize_route();
        double get_distance() const;

    private:
        std::string id_;
        std::vector<Location> waypoints_;
    };

} // namespace transportation