#pragma once

#include "route.hpp"
#include "location.hpp"
#include "vehicle_status.hpp"
#include <string>
#include <memory>

namespace transportation
{

#pragma once

#include <string>
#include <memory>
#include <vector>
#include "location.hpp"
#include "vehicle_status.hpp"

    // Forward declarations to avoid circular dependencies
    class Route;
    class Passenger;

    // Abstract base class for all vehicles.
    class Vehicle : public std::enable_shared_from_this<Vehicle>
    {
    public:
        // Constructor
        Vehicle(const std::string &id, int max_passengers)
            : id_{id},
              max_passengers_{max_passengers} {}

        //destructor for base class
        ~Vehicle() = default;

        void drive();

        // Getters
        [[nodiscard]] std::string get_id() const noexcept { return id_; }
        [[nodiscard]] Location get_current_location() const noexcept { return current_location_; }
        [[nodiscard]] VehicleStatus get_status() const noexcept { return status_; }
        [[nodiscard]] std::shared_ptr<Route> get_route() const noexcept { return route_; }
        [[nodiscard]] int get_max_passengers() const noexcept { return max_passengers_; }
        [[nodiscard]] int get_current_passenger_count() const noexcept { return current_passenger_count_; }

        // Setters
        void set_id(const std::string &id) { id_ = id; }
        void set_status(VehicleStatus status) { status_ = status; }
        void set_route(std::shared_ptr<Route> route) { route_ = route; }
        // internal state setters
        void set_current_location(const Location &loc) { current_location_ = loc; }

        // Other methods
        void update_location(const Location &location);
        void pickup_passenger(std::shared_ptr<Passenger> passenger);
        void dropoff_passenger(std::shared_ptr<Passenger> passenger);

    protected:
        // Protected so subclasses can access them
        std::string id_;
        int max_passengers_;
        Location current_location_;
        VehicleStatus status_{VehicleStatus::IDLE};
        std::shared_ptr<Route> route_;
        int current_passenger_count_{0};
        std::vector<std::shared_ptr<Passenger>> passengers_;
    };

} // namespace transportation