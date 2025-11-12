#include "taxi.hpp"
#include "driver.hpp" // Include full header
#include "route.hpp"
#include <iostream>

void transportation::Taxi::drive() {
    if (driver_) {
        std::cout << "Taxi " << id_ << " is being driven by " << driver_->get_name() << '\n';
        if (route_) {
            std::cout << "Following route " << route_->get_id() << '\n';
        }
    } else {
        std::cout << "Taxi " << id_ << " cannot drive without a driver." << '\n';
    }
}

void transportation::Taxi::assign_driver(std::shared_ptr<Driver> driver) {
    std::cout << "Assigning driver " << driver->get_name() << " to Taxi " << id_ << '\n';
    set_driver(driver);
}

void transportation::Taxi::remove_driver() {
    if (driver_) {
        std::cout << "Removing driver " << driver_->get_name() << " from Taxi " << id_ << '\n';
        driver_ = nullptr;
    }
}