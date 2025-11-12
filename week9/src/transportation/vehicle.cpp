#include "vehicle.hpp"
#include "passenger.hpp" // Include full header for method implementations
#include "route.hpp"
#include <iostream>
#include <algorithm>

void transportation::Vehicle::drive()
{
    std::cout << "Vehicle::drive()";
}

void transportation::Vehicle::update_location(const Location &location)
{
    std::cout << "Vehicle " << id_ << " location updated." << '\n';
    set_current_location(location);
}

void transportation::Vehicle::pickup_passenger(std::shared_ptr<Passenger> passenger)
{
    if (current_passenger_count_ < max_passengers_)
    {
        current_passenger_count_++;
        passengers_.push_back(passenger);
        // Set the passenger's vehicle
        passenger->set_current_vehicle(shared_from_this()); // Requires Vehicle to be managed by shared_ptr
        std::cout << "Passenger " << passenger->get_name() << " picked up by " << id_ << '\n';
    }
    else
    {
        std::cout << "Vehicle " << id_ << " is full. Cannot pick up " << passenger->get_name() << '\n';
    }
}

void transportation::Vehicle::dropoff_passenger(std::shared_ptr<Passenger> passenger)
{
    auto it = std::find(passengers_.begin(), passengers_.end(), passenger);
    if (it != passengers_.end())
    {
        passengers_.erase(it);
        current_passenger_count_--;
        // Unset the passenger's vehicle
        passenger->set_current_vehicle(std::weak_ptr<Vehicle>());
        std::cout << "Passenger " << passenger->get_name() << " dropped off by " << id_ << '\n';
    }
    else
    {
        std::cout << "Passenger " << passenger->get_name() << " not found in " << id_ << '\n';
    }
}