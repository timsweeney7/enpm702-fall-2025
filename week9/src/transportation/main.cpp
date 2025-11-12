#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Include all the necessary headers
#include "location.hpp"
#include "position.hpp"
#include "vehicle_status.hpp"
#include "sensor_type.hpp"
#include "sensor.hpp"
#include "driver.hpp"
#include "route.hpp"
#include "vehicle.hpp"
#include "robo_taxi.hpp"
#include "taxi.hpp"
#include "fleet.hpp"
#include "passenger.hpp"

// int main() {
//     std::cout << "Transportation System Simulation" << '\n';
//     std::cout << "==================================" << '\n' << '\n';

//     // 1. Create a Fleet
//     // Use std::make_shared for objects that will be passed around
//     auto fleet = std::make_shared<transportation::Fleet>("fleet_01", "Gemini Transit");

//     // 2. Create a RoboTaxi, add sensors, and add to fleet
//     std::cout << "--- Setting up RoboTaxi ---" << '\n';
//     auto robo_taxi = std::make_shared<transportation::RoboTaxi>("rt_101", 4);

//     // Create sensors (RoboTaxi owns these, so use unique_ptr)
//     auto lidar = std::make_unique<transportation::Sensor>("lidar_01", transportation::SensorType::LIDAR, transportation::Position(0, 0, 1.5));
//     auto camera = std::make_unique<transportation::Sensor>("cam_front", transportation::SensorType::CAMERA, transportation::Position(0.5, 0, 1.0));

//     robo_taxi->add_sensor(std::move(lidar));
//     robo_taxi->add_sensor(std::move(camera));

//     fleet->add_vehicle(robo_taxi);
//     std::cout << '\n';

//     // 3. Create a regular Taxi, add a driver, and add to fleet
//     std::cout << "--- Setting up Taxi ---" << '\n';
//     auto taxi = std::make_shared<transportation::Taxi>("taxi_202", 4);
//     auto driver = std::make_shared<transportation::Driver>("d_jane", "Jane Doe", "D12345");

//     taxi->assign_driver(driver);

//     fleet->add_vehicle(taxi);
//     std::cout << '\n';

//     // 4. Create a Passenger
//     std::cout << "--- Creating Passenger ---" << '\n';
//     // Passenger needs a shared_ptr to the fleet to make requests
//     auto passenger = std::make_shared<transportation::Passenger>("p_alex", "Alex", "555-0101", fleet);
//     std::cout << "Passenger " << passenger->get_name() << " created." << '\n' << '\n';

//     // 5. Define locations
//     transportation::Location pickup_loc(40.7128, -74.0060); // New York
//     transportation::Location dropoff_loc(40.7580, -73.9855); // Times Square

//     // 6. Simulate Ride 1 (should dispatch the RoboTaxi)
//     std::cout << "--- Requesting Ride 1 (RoboTaxi) ---" << '\n';
//     passenger->request_ride(pickup_loc, dropoff_loc);

//     // Get the vehicle from the passenger's perspective (weak_ptr)
//     if (auto ride1_vehicle_w = passenger->get_current_vehicle(); !ride1_vehicle_w.expired()) {
//         auto ride1_vehicle = ride1_vehicle_w.lock();

//         std::cout << "\n--- Ride 1 In Progress ---" << '\n';
//         ride1_vehicle->drive(); // En route to pickup
//         ride1_vehicle->update_location(pickup_loc);

//         // Pick up
//         ride1_vehicle->pickup_passenger(passenger);
//         std::cout << "Current passengers in " << ride1_vehicle->get_id() << ": " << ride1_vehicle->get_current_passenger_count() << '\n';

//         ride1_vehicle->drive(); // En route to dropoff
//         ride1_vehicle->update_location(dropoff_loc);

//         // Drop off
//         ride1_vehicle->dropoff_passenger(passenger);
//         std::cout << "Current passengers in " << ride1_vehicle->get_id() << ": " << ride1_vehicle->get_current_passenger_count() << '\n';

//         // Set vehicle back to IDLE for next ride
//         ride1_vehicle->set_status(transportation::VehicleStatus::IDLE);
//         ride1_vehicle->set_route(nullptr);
//     }
//     std::cout << '\n';

//     // 7. Simulate Ride 2 (should dispatch the Taxi)
//     std::cout << "--- Requesting Ride 2 (Taxi) ---" << '\n';
//     transportation::Location pickup_loc_2(40.7580, -73.9855); // Times Square
//     transportation::Location dropoff_loc_2(40.6892, -74.0445); // Statue of Liberty

//     passenger->request_ride(pickup_loc_2, dropoff_loc_2);

//     if (auto ride2_vehicle_w = passenger->get_current_vehicle(); !ride2_vehicle_w.expired()) {
//         auto ride2_vehicle = ride2_vehicle_w.lock();

//         std::cout << "\n--- Ride 2 In Progress ---" << '\n';
//         ride2_vehicle->drive(); // En route to pickup
//         ride2_vehicle->update_location(pickup_loc_2);

//         // Pick up
//         ride2_vehicle->pickup_passenger(passenger);

//         ride2_vehicle->drive(); // En route to dropoff
//         ride2_vehicle->update_location(dropoff_loc_2);

//         // Drop off
//         ride2_vehicle->dropoff_passenger(passenger);

//         // Set vehicle back to IDLE
//         ride2_vehicle->set_status(transportation::VehicleStatus::IDLE);
//         ride2_vehicle->set_route(nullptr);
//     }
//     std::cout << '\n';

//     std::cout << "==================================" << '\n';
//     std::cout << "Simulation complete." << '\n';
// }

void drive_vehicle(transportation::RoboTaxi &vehicle) { vehicle.drive(); }
void drive_vehicle(transportation::Taxi &vehicle) { vehicle.drive(); }
void drive_vehicle(std::unique_ptr<transportation::RoboTaxi> vehicle)
{
    vehicle->drive();
}
void drive_vehicle(std::unique_ptr<transportation::Taxi> vehicle)
{
    vehicle->drive();
}

int main()
{
    auto robo_taxi = transportation::RoboTaxi("rt_101", 4);
    auto taxi = transportation::Taxi("taxi_201", 4);
    drive_vehicle(robo_taxi);
    drive_vehicle(taxi);

    auto robo_taxi2 = std::make_unique<transportation::RoboTaxi>("rt_102", 4);
    auto taxi2 = std::make_unique<transportation::Taxi>("taxi_202", 4);
    drive_vehicle(std::move(robo_taxi2));
    drive_vehicle(std::move(taxi2));

    // transportation::Vehicle robo_taxi3 = transportation::RoboTaxi("rt_101", 4);
    // transportation::Vehicle taxi3 = transportation::Taxi("taxi_201", 4);

    // std::unique_ptr<transportation::Vehicle> robo_taxi4 = std::make_unique<transportation::RoboTaxi>("rt_103", 5);
    // std::unique_ptr<transportation::Vehicle> taxi4 = std::make_unique<transportation::Taxi>("taxi_202", 4);

}