#pragma once

namespace transportation {

/**
 * @enum SensorType
 * @brief Types of sensors used in autonomous vehicles
 */
enum class SensorType {
    LIDAR,    // Light Detection and Ranging
    CAMERA,   // Visual camera
    RADAR,    // Radio Detection and Ranging
    GPS,      // Global Positioning System
    IMU       // Inertial Measurement Unit
};

} // namespace transportation