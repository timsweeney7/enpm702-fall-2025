#include "sensor.hpp"
#include<iostream>

double transportation::Sensor::read_data() const
{
    // Simulated sensor reading
    // In a real system, this would interface with hardware
    std::cout << "Sensor: Reading data\n";
    return 42.0; // Placeholder value
}

void transportation::Sensor::calibrate()
{
    // Simulated calibration procedure
    // In a real system, this would perform actual calibration
    std::cout << "Sensor: calibrating\n";
}