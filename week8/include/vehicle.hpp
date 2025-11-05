/**
 * @file vehicle.hpp
 * @author zeidk (zeidk@umd.edu)
 * @brief Defines the Vehicle class for representing vehicles with basic
 * properties
 * @version 0.1
 * @date 2025-11-03
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include <string>

namespace transportation {
class Vehicle {
 private:
  std::string color_;
  std::string model_;
  bool is_running_{false};
  int max_speed_;

 public:
  void start_engine();
  void stop_engine();
  void drive();

  /**
   * @brief This method is used for debugging only
   * @todo Remove in production code
   */
  void print_status();
};  // class Vehicle
}  // namespace transportation