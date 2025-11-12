#pragma once

#include "vehicle.hpp"
#include <memory>

namespace transportation
{
    // Forward declaration
    class Driver;

    // Driver-operated vehicle implementation.
    class Taxi : public Vehicle
    {
    public:
        // Constructor
        Taxi(const std::string &id, int max_passengers)
            : Vehicle(id, max_passengers) {}

        // Getters
        [[nodiscard]] std::shared_ptr<Driver> get_driver() const noexcept { return driver_; }

        // Setters
        void set_driver(std::shared_ptr<Driver> driver) { driver_ = driver; }

        // Overridden method
        void drive();

        // Other methods
        void assign_driver(std::shared_ptr<Driver> driver);
        void remove_driver();

    private:
        // Taxi has an association with a Driver
        std::shared_ptr<Driver> driver_{nullptr};
    };

} // namespace transportation