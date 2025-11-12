#pragma once

namespace transportation
{
    // Represents a 3D position, used for sensor mounting.
    // Treated as a class for consistency with attribute rules.
    class Position
    {
    public:
        // Default constructor
        Position() : x_{0.0}, y_{0.0}, z_{0.0} {}

        // Parameterized constructor
        Position(double x, double y, double z) : x_(x), y_(y), z_(z) {}

        // Getters
        [[nodiscard]] double get_x() const noexcept { return x_; }
        [[nodiscard]] double get_y() const noexcept { return y_; }
        [[nodiscard]] double get_z() const noexcept { return z_; }

        // Setters
        void set_x(double x) { x_ = x; }
        void set_y(double y) { y_ = y; }
        void set_z(double z) { z_ = z; }

    private:
        double x_;
        double y_;
        double z_;
    };
} // namespace transportation