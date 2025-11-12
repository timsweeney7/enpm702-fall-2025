#include "passenger.hpp"
#include "fleet.hpp" // Include full header
#include "vehicle.hpp"
#include <iostream>

void transportation::Passenger::request_ride(const Location &pickup, const Location &dropoff)
{
    if (fleet_)
    {
        std::cout << "Passenger " << name_ << " is requesting a ride from fleet " << fleet_->get_id() << '\n';
        auto vehicle = fleet_->dispatch_vehicle(pickup, dropoff);
        if (vehicle)
        {
            std::cout << "Ride request accepted, vehicle " << vehicle->get_id() << " is on the way." << '\n';
        }
        else
        {
            std::cout << "Ride request failed, no available vehicles." << '\n';
        }
    }
    else
    {
        std::cout << "Passenger " << name_ << " is not associated with any fleet." << '\n';
    }
}