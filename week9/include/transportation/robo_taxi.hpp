#pragma once

#include <memory>
#include <vector>

#include "sensor.hpp"
#include "vehicle.hpp"

namespace transportation {
// Autonomous vehicle implementation.
class RoboTaxi final : public Vehicle {
 public:
  // Constructor
  RoboTaxi(const std::string& id, int max_passengers)
      : Vehicle(id, max_passengers) {
  }

  // Getters
  [[nodiscard]] const std::vector<std::unique_ptr<Sensor>>& get_sensors()
      const noexcept {
    return sensors_;
  }
  // No setter for list, use add_sensor

  // Overridden method
  virtual void drive() override;

  // Other methods
  void add_sensor(std::unique_ptr<Sensor> sensor);

 private:
  // RoboTaxi owns its sensors (Composition)
  std::vector<std::unique_ptr<Sensor>> sensors_;
};
}  // namespace transportation