#include "robo_taxi.hpp"
#include <iostream>

void transportation::RoboTaxi::drive()
{
    std::cout << "RoboTaxi " << id_ << " is driving autonomously." << '\n';
    if (route_)
    {
        std::cout << "Following route " << route_->get_id() << '\n';
    }
    // Read data from all sensors
    for (const auto &sensor : sensors_)
    {
        sensor->read_data();
    }
}

void transportation::RoboTaxi::add_sensor(std::unique_ptr<Sensor> sensor)
{
    std::cout << "Adding sensor " << sensor->get_sensor_id() << " to " << id_ << '\n';
    sensors_.push_back(std::move(sensor));
}