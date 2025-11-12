#pragma once

#include <cmath>

namespace transportation
{
    // Represents a geographical location.
    class Location
    {
    public:
        // Default constructor
        Location() = default;

        // Parameterized constructor
        Location(double latitude, double longitude)
            : latitude_(latitude), longitude_(longitude) {}

        // Getters
        [[nodiscard]] double get_latitude() const noexcept { return latitude_; }
        [[nodiscard]] double get_longitude() const noexcept { return longitude_; }

        // Setters
        void set_latitude(double latitude) { latitude_ = latitude; }
        void set_longitude(double longitude) { longitude_ = longitude; }

        // Other methods
        double distance_to(const Location &other) const;

    private:
        double latitude_{0.0};
        double longitude_{0.0};
    }; // class Location
} // namespace transportatin