#pragma once

#include <string>
#include "position.hpp"
#include "sensor_type.hpp"

namespace transportation
{

    // Represents a single sensor on a RoboTaxi.
    class Sensor
    {
    public:
        // Constructor
        Sensor(const std::string &sensor_id, SensorType sensor_type, const Position &position)
            : sensor_id_{sensor_id}, sensor_type_{sensor_type}, position_on_vehicle_{position} {}

        // Getters
        [[nodiscard]] std::string get_sensor_id() const noexcept { return sensor_id_; }
        [[nodiscard]] SensorType get_type() const noexcept { return sensor_type_; }
        [[nodiscard]] Position get_position_on_vehicle() const noexcept { return position_on_vehicle_; }

        // Setters
        void set_sensor_id(const std::string &sensor_id) { sensor_id_ = sensor_id; }
        void set_type(SensorType sensor_type) { sensor_type_ = sensor_type; }
        void set_position_on_vehicle(const Position &position) { position_on_vehicle_ = position; }

        // Other methods
        double read_data() const;
        void calibrate();

    private:
        std::string sensor_id_;
        SensorType sensor_type_;
        Position position_on_vehicle_;
    };

} // namespace transportation