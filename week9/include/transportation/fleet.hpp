#pragma once

#include <string>
#include <vector>
#include <memory>
#include "location.hpp"

namespace transportation
{
    // Forward declarations
    class Vehicle;
    class Route; // Needed for dispatch_vehicle implementation

    // Manages a fleet of vehicles.
    class Fleet
    {
    public:
        // Constructor
        Fleet(const std::string &id, const std::string &operator_name)
            : id_{id}, operator_name_{operator_name} {}

        // Getters
        [[nodiscard]] std::string get_id() const noexcept { return id_; }
        [[nodiscard]] std::string get_operator_name() const noexcept { return operator_name_; }
        [[nodiscard]] const std::vector<Location> &get_service_area() const noexcept { return service_area_; }
        [[nodiscard]] const std::vector<std::shared_ptr<Vehicle>> &get_vehicles() const noexcept { return vehicles_; }

        // Setters
        void set_id(const std::string &id) { id_ = id; }
        void set_operator_name(const std::string &name) { operator_name_ = name; }
        void set_service_area(const std::vector<Location> &area) { service_area_ = area; }

        // Other methods
        void add_vehicle(std::shared_ptr<Vehicle> vehicle);
        void remove_vehicle(std::shared_ptr<Vehicle> vehicle);
        std::vector<std::shared_ptr<Vehicle>> get_available_vehicles() const;
        std::shared_ptr<Vehicle> dispatch_vehicle(const Location &pickup, const Location &dropoff);

    private:
        std::string id_;
        std::string operator_name_;
        std::vector<Location> service_area_;
        // Fleet has an aggregation of Vehicles
        std::vector<std::shared_ptr<Vehicle>> vehicles_;
    };
} // namespace transportation