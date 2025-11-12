#include "fleet.hpp"
#include "vehicle.hpp" // Include full header
#include "route.hpp"   // Include full header
#include "vehicle_status.hpp"
#include <iostream>
#include <algorithm>

void transportation::Fleet::add_vehicle(std::shared_ptr<Vehicle> vehicle)
{
    std::cout << "Adding vehicle " << vehicle->get_id() << " to fleet " << id_ << '\n';
    vehicles_.push_back(vehicle);
}

void transportation::Fleet::remove_vehicle(std::shared_ptr<Vehicle> vehicle)
{
    auto it = std::find(vehicles_.begin(), vehicles_.end(), vehicle);
    if (it != vehicles_.end())
    {
        std::cout << "Removing vehicle " << (*it)->get_id() << " from fleet " << id_ << '\n';
        vehicles_.erase(it);
    }
}

std::vector<std::shared_ptr<transportation::Vehicle>> transportation::Fleet::get_available_vehicles() const
{
    std::vector<std::shared_ptr<Vehicle>> available;
    for (const auto &vehicle : vehicles_)
    {
        if (vehicle->get_status() == VehicleStatus::IDLE)
        {
            available.push_back(vehicle);
        }
    }
    return available;
}

std::shared_ptr<transportation::Vehicle> transportation::Fleet::dispatch_vehicle(const Location &pickup, const Location &dropoff)
{
    std::cout << "Attempting to dispatch vehicle for fleet " << id_ << '\n';
    auto available_vehicles = get_available_vehicles();
    if (available_vehicles.empty())
    {
        std::cout << "No available vehicles in fleet " << id_ << '\n';
        return nullptr;
    }

    // Simple logic: pick the first available vehicle
    std::shared_ptr<Vehicle> dispatched_vehicle = available_vehicles.front();

    // Create and assign a new route
    // In a real app, route IDs would be generated
    std::string route_id = "route_for_" + dispatched_vehicle->get_id();
    auto new_route = std::make_shared<Route>(route_id);
    new_route->add_waypoint(pickup);
    new_route->add_waypoint(dropoff);
    new_route->optimize_route();

    dispatched_vehicle->set_route(new_route);
    dispatched_vehicle->set_status(VehicleStatus::EN_ROUTE);

    std::cout << "Dispatched vehicle " << dispatched_vehicle->get_id() << " for pickup." << '\n';
    return dispatched_vehicle;
}