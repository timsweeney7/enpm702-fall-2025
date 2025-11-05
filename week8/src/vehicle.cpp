#include "vehicle.hpp"

#include <iostream>

void transportation::Vehicle::start_engine() {
}

void transportation::Vehicle::stop_engine() {
}

void transportation::Vehicle::drive() {
}

void transportation::Vehicle::print_status() {
  std::cout << "Status" << '\n';
  std::cout << "======" << '\n';
  std::cout << "Color: " << color_ << '\n';
  std::cout << "Model: " << model_ << '\n';
  std::cout << "Running? " << std::boolalpha << is_running_ << '\n';
  std::cout << "Max Speed: " << max_speed_ << '\n';
}