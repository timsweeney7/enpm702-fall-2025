=====================
Requirements Analysis
=====================

The **requirements analysis** defines **what** the system must do before designing **how** it will work.
It captures functional capabilities, quality attributes, constraints, and measurable success criteria
for the robotaxi transportation domain (Person, Vehicle, RoboTaxi, RoboShuttle, Fleet, Route, Sensor, Location).

------------------------
Functional Requirements
------------------------

.. list-table::
   :widths: 25 60 15
   :header-rows: 1

   * - **ID**
     - **Requirement**
     - **Priority**
   * - FR-1
     - The system shall allow a Person to **request a ride** by specifying pickup and dropoff locations.
     - Must
   * - FR-2
     - The system shall allow a Fleet to **dispatch an available vehicle** to service a ride request.
     - Must
   * - FR-3
     - The system shall support **polymorphic vehicle behavior**: Vehicle subclasses (RoboTaxi, RoboShuttle) must implement type-specific capacity and operations.
     - Must
   * - FR-4
     - The system shall enforce that each Vehicle contains **one or more Sensors** for navigation and safety monitoring.
     - Must
   * - FR-5
     - The system shall allow a Vehicle to **follow an optional Route**; if a Route is assigned, the Vehicle shall navigate along the route waypoints.
     - Must
   * - FR-6
     - The system shall expose **status queries** (e.g., vehicle status, current location, battery level for RoboTaxi).
     - Should
   * - FR-7
     - The system shall **log key lifecycle events** (ride requested, vehicle dispatched, route assigned, passenger boarded/exited, trip completed).
     - Should
   * - FR-8
     - The system shall **read sensor data continuously** during vehicle operation for navigation and obstacle detection.
     - Must
   * - FR-9
     - The system shall allow **creating and optimizing Routes** with multiple waypoints at runtime.
     - Should
   * - FR-10
     - The system shall support **Fleet management operations** including adding/removing vehicles and querying available vehicles.
     - Must

----------------------------
Non-Functional Requirements
----------------------------

.. list-table::
   :widths: 25 75
   :header-rows: 1

   * - **Attribute**
     - **Requirement**
   * - Performance
     - Sensor data reading shall complete within **50 ms** per sensor, and route optimization shall complete within **500 ms** for routes with up to 20 waypoints.
   * - Reliability
     - The system shall handle sensor failures gracefully with redundancy; mean time between failures **> 1000 hours** for autonomous operation.
   * - Safety
     - The system shall prevent unsafe operations (e.g., passenger boarding while vehicle is in motion) via validated state checks in the Vehicle.
   * - Availability
     - Fleet dispatch and vehicle status operations shall be available **99.9%** during operational hours.
   * - Observability
     - All ride requests, vehicle dispatches, route assignments, and passenger events shall be logged with timestamps, location data, and entity identifiers.
   * - Maintainability
     - The system shall separate concerns by layers and achieve **< 10%** cyclic dependency density in static analysis.
   * - Extensibility
     - Adding a new Vehicle subtype (e.g., RoboBus) shall require **no changes** to existing Fleet or Route management logic.

----------------------
Technical Constraints
----------------------

.. list-table::
   :widths: 28 72
   :header-rows: 1

   * - **Constraint**
     - **Description**
   * - Namespace Organization
     - All domain classes (Vehicle, RoboTaxi, RoboShuttle, Sensor, Fleet, Person, Route, Location) shall be encapsulated within the ``transportation`` namespace to provide logical grouping and prevent naming conflicts.
   * - Encapsulation
     - External actors shall not access Sensors directly. All sensor operations are managed internally by Vehicle.
   * - Composition Rule
     - Each Vehicle contains one or more Sensors (composition). Sensor lifecycle is bound to Vehicle lifecycle.
   * - Aggregation Rule
     - Fleet aggregates Vehicles. Vehicles can exist independently of the Fleet and can be transferred between Fleets.
   * - Optional Route
     - Route association is optional at runtime. Vehicles can operate without a Route assigned (e.g., idle, charging).
   * - Type Abstraction
     - Diagram types are language agnostic (e.g., ``String``, ``Integer``), and mapping to concrete types (e.g., ``std::string``, ``int``) is an implementation detail.
   * - Error Handling
     - Operations must return typed results or exceptions with machine-readable codes and human-readable messages.

------------------------
Implementation Guidance
------------------------

**C++ Specific Constraints:**

All domain entities in the C++ implementation shall adhere to the following conventions:

- All domain classes shall be declared within the ``transportation`` namespace
- Header files shall use ``#pragma once`` or include guards with the pattern ``TRANSPORTATION_CLASSNAME_HPP``
- Member variables shall use camelCase convention (e.g., ``vehicleId``, ``batteryLevel``, ``maxPassengers``)
- Pass ``std::string`` parameters as ``const std::string&`` in constructors and methods to avoid unnecessary copies
- Use ``std::shared_ptr`` for aggregation relationships (Fleet–Vehicle) and association relationships (Vehicle–Route, Person–Vehicle)
- Use composition for Sensor ownership (Vehicle directly contains Sensors)
- Abstract methods shall be marked with ``= 0`` pure virtual specifier
- Class and method documentation shall follow Doxygen format with ``@file``, ``@class``, ``@brief``, ``@param``, and ``@return`` tags
- Virtual destructors shall be provided for all polymorphic base classes

**Namespace Structure:**

.. code-block:: cpp

   namespace transportation {
       // Core domain entities
       class Vehicle;      // Abstract base class
       class RoboTaxi;     // Autonomous taxi vehicle
       class RoboShuttle;  // Autonomous shuttle vehicle
       class Sensor;       // Navigation and safety sensor
       class Fleet;        // Vehicle fleet management
       class Person;       // Passenger/user
       class Route;        // Navigation route
       class Location;     // Geographic location
       
       // Enumerations
       enum class SensorType;
       enum class VehicleStatus;
   }

**Example Usage:**

.. code-block:: cpp

   #include "fleet.hpp"
   #include "robotaxi.hpp"
   #include "person.hpp"
   #include "route.hpp"
   #include "location.hpp"
   
   int main() {
       // Create fleet and vehicles
       transportation::Fleet fleet("Fleet-001", "RoboRide Inc");
       auto taxi = std::make_shared<transportation::RoboTaxi>(
           "TAXI-001", 85.5f, 4);
       
       fleet.addVehicle(taxi);
       
       // Create passenger and locations
       transportation::Person passenger("P-001", "Jane Doe", "555-1234");
       transportation::Location pickup(37.7749, -122.4194);  // San Francisco
       transportation::Location dropoff(37.8044, -122.2712); // Oakland
       
       // Request ride
       auto dispatchedVehicle = fleet.dispatchVehicle(pickup, dropoff);
       
       // Passenger boards vehicle
       passenger.boardVehicle(dispatchedVehicle);
       
       // Complete trip
       passenger.exitVehicle();
       
       return 0;
   }

----------------
Success Criteria
----------------

.. list-table::
   :widths: 35 65
   :header-rows: 1

   * - **Criterion**
     - **Measurable Outcome**
   * - Ride Request and Dispatch
     - Person requests ride with pickup/dropoff locations; Fleet dispatches available vehicle within **500 ms** and logs the event with timestamps and location data.
   * - Polymorphic Vehicle Behavior
     - For RoboTaxi and RoboShuttle, invoking type-specific methods produces correct behavior without code changes in Fleet management; verified by unit tests covering all subtypes (**> 95%** branch coverage).
   * - Sensor Data Collection
     - Vehicles continuously read sensor data with **< 50 ms** latency per sensor; sensor failures are detected and logged within **100 ms**.
   * - Route Navigation
     - Vehicle navigates successfully with and without a Route; when a Route is assigned, route optimization completes within **500 ms** for routes with up to 20 waypoints.
   * - Fleet Management
     - Fleet operations (add/remove vehicle, query available vehicles) complete within **100 ms**; fleet maintains accurate vehicle inventory in **100%** of test cases.
   * - Passenger Safety
     - Invalid operations (e.g., boarding while vehicle is moving) are rejected with explicit error codes in **100%** of negative test cases.
   * - Separation of Concerns
     - Static analysis reports **0** direct dependencies from Presentation to Domain or Infrastructure; only Application mediates.
   * - Observability
     - Logs contain complete audit trails (ride requests, dispatches, passenger events, route navigation) with **no missing events** in end-to-end tests across **N ≥ 50** scripted scenarios.
   * - Namespace Compliance
     - All domain classes reside within ``transportation`` namespace; static analysis confirms zero global namespace pollution from domain entities.

-------------------------
Assumptions and Scope
-------------------------

- A Vehicle contains one or more Sensors for navigation and safety.
- A Fleet may contain zero or more Vehicles; vehicles can be added or removed dynamically.
- A Person may ride in zero or one Vehicle at any given time.
- A Vehicle may follow **zero or one** current Route; Routes may be shared or reused across vehicles.
- Sensor readings are simulated; timings refer to software execution in the target environment.
- All domain entities are organized within the ``transportation`` namespace in the C++ implementation.
- Language-agnostic design allows implementation in multiple programming languages while maintaining conceptual integrity.
- The system focuses on core ride-hailing functionality; payment processing and user authentication are out of scope.

-----------------------
Verification Approach
-----------------------

- **Unit tests** for Vehicle state management, Sensor data reading, Fleet operations, and subtype-specific behavior within the ``transportation`` namespace.
- **Integration tests** for Person–Fleet–Vehicle interactions, route navigation, and passenger boarding/exiting across namespace boundaries.
- **Contract tests** for repository and gateway adapters (Infrastructure) to ensure stable interfaces with domain entities.
- **Static analysis** for dependency direction, absence of forbidden couplings, proper namespace usage, and cyclic dependency metrics.
- **Namespace verification** to ensure all domain classes are properly encapsulated within ``transportation`` and no global namespace pollution occurs.
- **Performance tests** to validate sensor reading completes within 50 ms per sensor and route optimization within 500 ms under nominal load.
- **Safety tests** to verify invalid state transitions (e.g., boarding while moving) are properly rejected with appropriate error codes in 100% of negative test cases.
- **Code coverage analysis** ensuring > 95% branch coverage on polymorphic vehicle behavior across RoboTaxi and RoboShuttle subtypes.
- **Reliability tests** for sensor failure handling and graceful degradation under fault conditions.