#pragma once

#include <string>
#include <memory>
#include "location.hpp"

namespace transportation
{
    // Forward declarations
    class Vehicle;
    class Fleet;

    // Represents a passenger who can request rides.
    class Passenger : public std::enable_shared_from_this<Passenger>
    {
    public:
        // Constructor
        Passenger(const std::string &id, const std::string &name, const std::string &phone, std::shared_ptr<Fleet> fleet)
            : id_{id}, name_{name}, phone_number_{phone}, fleet_{fleet} {}

        // Getters
        [[nodiscard]] std::string get_id() const noexcept { return id_; }
        [[nodiscard]] std::string get_name() const noexcept { return name_; }
        [[nodiscard]] std::string get_phone_number() const noexcept { return phone_number_; }
        [[nodiscard]] std::weak_ptr<Vehicle> get_current_vehicle() const noexcept { return current_vehicle_; }
        [[nodiscard]] std::shared_ptr<Fleet> get_fleet() const noexcept { return fleet_; }

        // Setters
        void set_id(const std::string &id) { id_ = id; }
        void set_name(const std::string &name) { name_ = name; }
        void set_phone_number(const std::string &phone) { phone_number_ = phone; }
        void set_current_vehicle(std::weak_ptr<Vehicle> vehicle) { current_vehicle_ = vehicle; }
        void set_fleet(std::shared_ptr<Fleet> fleet) { fleet_ = fleet; }

        // Other methods
        void request_ride(const Location &pickup, const Location &dropoff);

    private:
        std::string id_;
        std::string name_;
        std::string phone_number_;
        // Passenger has a non-owning pointer to its vehicle to prevent cycles
        std::weak_ptr<Vehicle> current_vehicle_;
        // Passenger is associated with a fleet to make requests
        std::shared_ptr<Fleet> fleet_;
    };

} // namespace transportation