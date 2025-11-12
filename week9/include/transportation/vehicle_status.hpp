#pragma once

namespace transportation {

/**
 * @enum VehicleStatus
 * @brief Operational status of a vehicle
 */
enum class VehicleStatus {
    IDLE,             // Available but not assigned
    IN_SERVICE,       // Actively serving passengers
    EN_ROUTE,         // Traveling to pickup or destination
    CHARGING,         // At charging station
    MAINTENANCE,      // Undergoing maintenance
    OUT_OF_SERVICE    // Not operational
};

} // namespace transportation