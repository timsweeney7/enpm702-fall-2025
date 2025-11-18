#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Include all the necessary headers
#include "driver.hpp"
#include "fleet.hpp"
#include "location.hpp"
#include "passenger.hpp"
#include "position.hpp"
#include "robo_taxi.hpp"
#include "route.hpp"
#include "sensor.hpp"
#include "sensor_type.hpp"
#include "taxi.hpp"
#include "vehicle.hpp"
#include "vehicle_status.hpp"

//========================================
// Full demo of the transportation domain
//========================================
// int main() {
//   using transportation::Driver;
//   using transportation::Fleet;
//   using transportation::Location;
//   using transportation::Passenger;
//   using transportation::RoboTaxi;
//   using transportation::Route;
//   using transportation::Taxi;
//   using transportation::Vehicle;

//   // Fleet is shared because Passenger holds a shared_ptr<Fleet>
//   auto fleet = std::make_shared<Fleet>("Fleet-001", "RideShare Inc");

//   // Vehicles (id, max_passengers)
//   auto robotaxi = std::make_shared<RoboTaxi>("ROBOTAXI-001", 4);
//   auto taxi     = std::make_shared<Taxi>("TAXI-001", 4);

//   // Assign a driver to Taxi (id, name, license)
//   auto driver = std::make_shared<Driver>("D-001", "John Smith", "DL-12345");
//   taxi->assign_driver(driver);

//   // Base route for RoboTaxi
//   auto robo_route = std::make_shared<Route>("R-ROBO-001");
//   robo_route->add_waypoint(Location{37.7749, -122.4194}); // San Francisco
//   robo_route->add_waypoint(Location{37.7890, -122.4010}); // Financial
//   District robo_route->add_waypoint(Location{37.7955, -122.3937}); //
//   Embarcadero robo_route->optimize_route(); robotaxi->set_route(robo_route);

//   // Base route for Taxi
//   auto taxi_route = std::make_shared<Route>("R-TAXI-001");
//   taxi_route->add_waypoint(Location{37.7749, -122.4194}); // San Francisco
//   taxi_route->add_waypoint(Location{37.7980, -122.3770}); // Bay Bridge
//   (west) taxi_route->add_waypoint(Location{37.8044, -122.2712}); // Oakland
//   taxi_route->optimize_route();
//   taxi->set_route(taxi_route);

//   // Register vehicles in the fleet
//   fleet->add_vehicle(robotaxi);
//   fleet->add_vehicle(taxi);

//   // Passenger requires (id, name, phone, shared_ptr<Fleet>)
//   auto passenger = std::make_shared<Passenger>("P-001", "Jane Doe",
//   "555-1234", fleet);

//   // Trip endpoints
//   Location pickup{37.7749, -122.4194};   // San Francisco
//   Location dropoff{37.8044, -122.2712};  // Oakland

//   // Dispatch an available vehicle
//   std::shared_ptr<Vehicle> dispatched = fleet->dispatch_vehicle(pickup,
//   dropoff);

//   // Trip-specific route: pickup -> dropoff
//   auto trip_route = std::make_shared<Route>("TRIP-0001");
//   trip_route->add_waypoint(pickup);
//   trip_route->add_waypoint(dropoff);
//   trip_route->optimize_route();
//   dispatched->set_route(trip_route);

//   // Execute trip
//   dispatched->pickup_passenger(passenger);
//   dispatched->dropoff_passenger(passenger);
// }

//========================================
// Polymorphism: Non-Polymorphic Overloads
//========================================
// // Overloads choose at compile time based on the static type.
// void run_shift(transportation::RoboTaxi& v) {
//   v.drive();
// }
// void run_shift(transportation::Taxi& v) {
//   v.drive();
// }

// int main() {
//   transportation::RoboTaxi rt{"ROBOTAXI-001", 4};
//   transportation::Taxi tx{"TAXI-001", 4};
//   run_shift(rt);  // Calls RoboTaxi version
//   run_shift(tx);  // Calls Taxi version
// }

//========================================
// Polymorphism: Polymorphic Solution
//========================================
// One function works for ALL current and future derived vehicle types
void run_shift(transportation::Vehicle& v) {
  v.drive();  // Runtime dispatch - calls the actual object's drive()
}
// Pointer variant (e.g., ownership with unique_ptr)
void run_shift(std::unique_ptr<transportation::Vehicle> v) {
  v->drive();  // Runtime dispatch
}

int main() {
  auto rt = std::make_unique<transportation::RoboTaxi>("ROBOTAXI-001", 4);
  auto tx = std::make_unique<transportation::Taxi>("TAXI-001", 4);
  run_shift(*rt);            // Calls RoboTaxi::drive()
  run_shift(std::move(tx));  // Calls Taxi::drive()
}