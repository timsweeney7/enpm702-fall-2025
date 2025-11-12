Modeling Phase
================

Introduction
------------

The **Modeling Phase** focuses on defining *how* a system is structured and behaves to satisfy
its requirements. It bridges the gap between the problem domain and the implementation domain,
providing visual representations that make complex designs easier to understand, communicate,
and maintain.

During this phase, several diagrams are used to represent different perspectives of the system:

- **Class Diagrams** – Depict the static structure of the system, including its classes,
  attributes, methods, and relationships.
- **Sequence Diagrams** – Illustrate the dynamic flow of interactions between objects over time.


Each diagram contributes to a comprehensive understanding of both the **structural** and
**behavioral** aspects of the system.


.. note::

   The naming conventions for **classes**, **attributes**, and **methods** used in these diagrams
   are **language-agnostic**.  
   The same applies to data types (for example, ``String`` is used instead of ``std::string`` or
   ``string``). This abstraction ensures that the design can be applied across multiple programming
   languages and paradigms without being tied to a specific implementation syntax.

.. note::

   In the C++ implementation, all classes are organized within the ``transportation`` namespace.
   This provides a logical grouping of related components and prevents naming conflicts with other
   libraries or system components.

Class Diagram
---------------

.. only:: html

   .. figure:: /_static/lecture8/design/class_diagram_light.png
      :alt: Class Diagram
      :align: center
      :width: 100%
      :class: only-light

   .. figure:: /_static/lecture8/design/class_diagram_dark.png
      :alt: Class Diagram
      :align: center
      :width: 100%
      :class: only-dark

This class diagram represents a **robotaxi transportation system**, showing how various entities
interact and relate to each other through inheritance, composition, aggregation, and association.
It models the structural organization of an autonomous ride-hailing service and the ownership or
interaction patterns between its classes.

.. note::

   All classes in the domain layer are organized within the ``transportation`` namespace, providing
   logical grouping and preventing naming conflicts with other system components.

~~~~~~~~~~~~~~~~
Key Components
~~~~~~~~~~~~~~~~

**Vehicle (Abstract Class)**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- **Purpose:** Defines the general structure and behavior common to all autonomous vehicle types.
- **Namespace:** ``transportation``
- **Attributes:**

  - ``id : String`` – Unique vehicle identifier for tracking and fleet management
  - ``currentLocation : Location`` – Current geographic position of the vehicle
  - ``status : VehicleStatus`` – Current operational state (IDLE, IN_SERVICE, EN_ROUTE, CHARGING, MAINTENANCE, OUT_OF_SERVICE)
  - ``route : Route`` – Optional navigation route the vehicle is currently following
  - ``sensors : List<Sensor>`` – Collection of sensors for navigation and safety (composition)

- **Operations:**

  - ``{abstract} getCapacity() : Integer`` — Returns maximum passenger capacity; must be implemented by subclasses
  - ``updateLocation(location : Location) : void`` — Updates the vehicle's current geographic position
  - ``getStatus() : VehicleStatus`` — Returns the current operational status of the vehicle
  - ``setRoute(route : Route) : void`` — Assigns a navigation route to the vehicle
  - ``getRoute() : Route`` — Retrieves the currently assigned route

.. note::
    The ``Vehicle`` class is abstract, meaning it cannot be instantiated directly.
    It provides a consistent interface for all concrete autonomous vehicles and manages
    sensor integration for navigation and safety monitoring.

**Concrete Vehicle Types**
^^^^^^^^^^^^^^^^^^^^^^^^^^

All concrete vehicle types reside in the ``transportation`` namespace and inherit from ``Vehicle``.

1. **RoboTaxi**

   - **Additional Attributes:** 
     
     - ``batteryLevel : Float`` – Current battery charge level (0.0 to 100.0)
     - ``maxPassengers : Integer`` – Maximum number of passengers the taxi can accommodate
   
   - **Operations:**
     
     - ``getCapacity() : Integer`` – Returns the maximum passenger capacity
     - ``chargeBattery() : void`` – Initiates battery charging operation
     - ``completeTrip() : void`` – Finalizes the current ride and updates vehicle status

2. **RoboShuttle**

   - **Additional Attributes:** 
     
     - ``maxPassengers : Integer`` – Maximum passenger capacity for shuttle service
   
   - **Operations:**
     
     - ``getCapacity() : Integer`` – Returns the maximum passenger capacity
     - ``addStop(stop : Location) : void`` – Adds a stop location to the shuttle's route

Each subclass specializes the ``Vehicle`` class by providing type-specific attributes
and operations tailored to their service model (on-demand taxi vs. scheduled shuttle).

**Sensor**
^^^^^^^^^^

- **Namespace:** ``transportation``
- **Attributes:** 
  
  - ``sensorId : String`` – Unique sensor identifier
  - ``sensorType : SensorType`` – Type of sensor (LIDAR, CAMERA, RADAR, GPS, IMU)
  - ``locationOnVehicle : Location`` – Physical mounting position on the vehicle

- **Operations:** 
  
  - ``readData() : SensorData`` – Reads current sensor data (completes within 50 ms)
  - ``calibrate() : void`` – Performs sensor calibration procedure
  - ``getType() : SensorType`` – Returns the type of sensor

- **Relationship:** Composition (``*--``) with ``Vehicle``.
  A vehicle contains one or more sensors; if the vehicle is destroyed,
  the sensors are destroyed as well. This enforces that vehicles have
  integrated sensor systems for navigation and safety.
- **Purpose:** Represents sensor hardware for autonomous navigation, obstacle detection,
  and situational awareness.

.. important::
   **Encapsulation Rule:** External actors cannot interact directly with
   Sensors. All sensor operations are managed internally by the Vehicle, which
   processes sensor data for navigation decisions.

**Fleet**
^^^^^^^^^

- **Namespace:** ``transportation``
- **Attributes:**

  - ``id : String`` – Unique fleet identifier
  - ``operatorName : String`` – Name of the fleet operating company
  - ``serviceArea : List<Location>`` – Geographic regions where fleet operates
  - ``vehicles : List<Vehicle>`` – Collection of vehicles managed by the fleet

- **Operations:**

  - ``addVehicle(vehicle : Vehicle) : void`` — Adds a vehicle to the fleet inventory
  - ``removeVehicle(vehicle : Vehicle) : void`` — Removes a vehicle from the fleet
  - ``getAvailableVehicles() : List<Vehicle>`` — Returns all idle vehicles ready for dispatch
  - ``dispatchVehicle(pickup : Location, dropoff : Location) : Vehicle`` — Assigns an available vehicle to service a ride request

- **Relationship:** Aggregation (``o--``) with ``Vehicle``.
  The fleet manages vehicles but does not own them; vehicles exist independently
  and can be transferred between fleets or operate independently.

**Person**
^^^^^^^^^^

- **Namespace:** ``transportation``
- **Attributes:**

  - ``id : String`` – Unique person identifier
  - ``name : String`` – Person's name
  - ``phoneNumber : String`` – Contact phone number
  - ``currentVehicle : Vehicle`` – The vehicle the person is currently riding in (if any)

- **Operations:**

  - ``requestRide(pickup : Location, dropoff : Location) : void`` — Requests a ride from the fleet system
  - ``boardVehicle(vehicle : Vehicle) : void`` — Boards an assigned vehicle
  - ``exitVehicle() : void`` — Exits the current vehicle

- **Relationship:** Association (``-->``) with ``Vehicle``.
  A person may ride in a vehicle, but both exist independently. The person may or may
  not be in a vehicle at any given time.

**Route**
^^^^^^^^^

- **Namespace:** ``transportation``
- **Attributes:**

  - ``id : String`` – Unique route identifier
  - ``waypoints : List<Location>`` – Ordered list of geographic points defining the route path

- **Operations:** 
  
  - ``addWaypoint(location : Location) : void`` – Adds a waypoint to the route
  - ``optimizeRoute() : void`` – Optimizes waypoint order for efficiency (< 500 ms for 20 waypoints)
  - ``getDistance() : Double`` – Calculates total route distance

- **Relationship:** Association (``-->``) with ``Vehicle``.
  A vehicle may follow zero or one route, while a route may be followed by multiple vehicles.
  Route association is optional; vehicles can operate without an assigned route (e.g., idle, charging).

**Location**
^^^^^^^^^^^^

- **Namespace:** ``transportation``
- **Attributes:**

  - ``latitude : Double`` – Geographic latitude coordinate
  - ``longitude : Double`` – Geographic longitude coordinate

- **Operations:** 
  
  - ``distanceTo(other : Location) : Double`` – Calculates distance to another location

- **Relationship:** Used by Route (waypoints), Vehicle (currentLocation), Sensor (locationOnVehicle), and Fleet (serviceArea).
- **Purpose:** Represents geographic coordinates for navigation, service boundaries, and sensor positioning.



~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Conceptual Analysis
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- **Encapsulation of Behavior:**  
  The ``Vehicle`` encapsulates sensor management internally. External actors (Person, Fleet) only
  interact with the ``Vehicle`` interface, never with ``Sensors`` directly. This promotes abstraction
  and separation of concerns, and enforces the technical constraint that sensors cannot be accessed directly.

- **Polymorphism:**  
  Concrete vehicles (RoboTaxi, RoboShuttle) provide type-specific implementations of ``getCapacity()``
  and specialized operations, enabling dynamic behavior depending on the vehicle type at runtime.

- **Optional Relationships:**  
  The ``Route`` association is optional; a vehicle can operate without being assigned a route
  (e.g., idle, charging). Similarly, a ``Person`` may or may not be riding in a vehicle at a given time.

- **Ownership Hierarchy:**  

  - ``Vehicle`` **owns** ``Sensors`` — composition (sensors are integral parts of the vehicle).  
  - ``Fleet`` **manages** ``Vehicles`` — aggregation (vehicles can exist independently of fleet).  
  - ``Vehicle`` **follows** ``Route`` — association (optional relationship).
  - ``Person`` **rides in** ``Vehicle`` — association (temporary relationship).

- **Fleet Management:**
  The ``Fleet`` provides centralized management of vehicles, including dispatch logic, availability
  tracking, and service area management. This separates vehicle lifecycle from ride operations.

~~~~~~~~~~~~~~~~~~~~~~~~~~
Performance Requirements
~~~~~~~~~~~~~~~~~~~~~~~~~~

.. note::

   **Performance Constraints:**
   
   - Sensor ``readData()`` operations complete within **50 ms per sensor**
   - Route ``optimizeRoute()`` completes within **500 ms for routes with up to 20 waypoints**
   - Fleet dispatch operations complete within **100 ms**
   - Fleet maintains **99.9% availability** during operational hours
   - All ride events (requests, dispatches, passenger boarding/exiting) are logged with timestamps and location data

~~~~~~~~~~~~~~~~
Summary
~~~~~~~~~~~~~~~~

This class diagram demonstrates several key object-oriented principles:

- **Abstraction** through the abstract ``Vehicle`` class.  
- **Inheritance** and **polymorphism** in specialized vehicle types (RoboTaxi, RoboShuttle).  
- **Encapsulation** of functionality within cohesive classes.  
- **Composition** for sensors that are integral parts of vehicles.
- **Aggregation** for fleet management where vehicles maintain independent lifecycles.
- **Association** for optional relationships (routes, passengers).
- **Clear separation of concerns** between passengers (Person), fleet management (Fleet),
  vehicle operations (Vehicle), navigation (Route), and sensing (Sensor).

Overall, the design offers modularity, flexibility for extension, and
a realistic mapping between software classes and autonomous transportation entities, while satisfying
both functional and non-functional requirements.

Sequence Diagram
-----------------

The **Sequence Diagram** captures the dynamic interaction between objects over time.
It illustrates how messages are passed, which operations are invoked, and how control
flows through the system to accomplish a specific task.

.. only:: html

   .. figure:: /_static/lecture8/design/sequence_diagram_light.png
      :alt: Sequence Diagram
      :align: center
      :width: 100%
      :class: only-light

   .. figure:: /_static/lecture8/design/sequence_diagram_dark.png
      :alt: Sequence Diagram
      :align: center
      :width: 100%
      :class: only-dark

~~~~~~~~~~~~~~~~~~~~~~
Participants
~~~~~~~~~~~~~~~~~~~~~~

All participants belong to the ``transportation`` namespace in the implementation:

- **Person** – Passenger requesting and using ride services; initiates ride requests.
- **Fleet** – Manages vehicle inventory and dispatches vehicles to service ride requests.
- **RoboTaxi** (Vehicle) – Autonomous vehicle that navigates routes and transports passengers.
- **Route** – Provides navigation path with waypoints for vehicle to follow.
- **Sensor** – Continuously provides data for navigation and obstacle detection (50 ms per read).
- **Location** – Represents geographic coordinates for pickup, dropoff, and navigation waypoints.

~~~~~~~~~~~~~~~~~~~~~~
Message Flow
~~~~~~~~~~~~~~~~~~~~~~

1. **Person requests a ride** from the Fleet (``dispatchVehicle(pickup, dropoff)``).  
   - Fleet queries available vehicles.
   - Fleet selects an idle RoboTaxi for the ride.

2. **Fleet creates and assigns a route**.  
   - Fleet creates a new Route with a unique ID.
   - Fleet adds pickup and dropoff locations as waypoints.
   - Fleet optimizes the route (completes within 500 ms for 20 waypoints).
   - Fleet assigns the route to the selected RoboTaxi via ``setRoute(route)``.

3. **RoboTaxi navigates to pickup location**.  
   - Vehicle continuously reads sensor data (``readData()`` completes within 50 ms per sensor).
   - Vehicle updates its current location based on sensor input.
   - Vehicle calculates distance to pickup location using ``Location.distanceTo()``.
   - Loop continues until vehicle arrives at pickup.

4. **Passenger boards the vehicle**.  
   - Person calls ``boardVehicle(taxi)`` when vehicle arrives.
   - Vehicle status updates to IN_SERVICE.

5. **RoboTaxi navigates to dropoff location**.  
   - Vehicle continues reading sensor data and updating location.
   - Vehicle follows the assigned route to the destination.
   - Vehicle queries route distance to monitor progress.

6. **Passenger exits and trip completes**.  
   - Person calls ``exitVehicle()`` upon arrival at destination.
   - RoboTaxi calls ``completeTrip()`` to finalize the ride and update status to IDLE.

~~~~~~~~~~~~~~~~~~~~~~
Control Constructs
~~~~~~~~~~~~~~~~~~~~~~

- **loop [while en route to pickup]**: Vehicle continuously reads sensor data and updates location until it reaches the pickup point.
- **loop [while en route to dropoff]**: Vehicle navigates to the destination, reading sensors and monitoring route progress.
- **object creation**: Route and Location objects are created dynamically during the ride request process.  

~~~~~~~~~~~~~~~~~~~~~~
Error Handling
~~~~~~~~~~~~~~~~~~~~~~

The sequence diagram demonstrates error handling for invalid operations:

- Attempting to board a vehicle while it is in motion is rejected
- Ride requests when no vehicles are available return appropriate error messages
- Sensor failures are detected and logged for safety monitoring
- All errors include machine-readable codes and human-readable descriptions
- State validation occurs before executing passenger operations

~~~~~~~~~~~~~~~~~~~~~~
Observability
~~~~~~~~~~~~~~~~~~~~~~

All key lifecycle events are logged with structured information:

- Ride requests (person ID, pickup/dropoff locations, timestamp)
- Vehicle dispatches (fleet ID, vehicle ID, route ID, timestamp)
- Route creation and optimization (route ID, waypoint count, optimization time)
- Passenger boarding/exiting (person ID, vehicle ID, location, timestamp)
- Sensor readings (vehicle ID, sensor type, timestamp, data quality metrics)
- Trip completion (vehicle ID, route ID, total distance, duration)

~~~~~~~~~~~~~~~~~~~~~~
Summary
~~~~~~~~~~~~~~~~~~~~~~

The sequence diagram complements the class diagram by showing the **runtime collaboration**
of objects. It clarifies the responsibilities of each component:

- The **Person** initiates ride requests and interacts with vehicles for boarding/exiting.
- The **Fleet** manages vehicle dispatch, route creation, and optimization.
- The **RoboTaxi** (Vehicle) executes autonomous navigation using sensor data and follows assigned routes.
- The **Sensor** provides continuous data for navigation and safety (within performance constraints).
- The **Route** defines the navigation path through waypoints.
- The **Location** represents geographic coordinates for all spatial operations.

Together, the class and sequence diagrams provide a complete behavioral
and structural model of the robotaxi system that satisfies both functional requirements
(FR-1 through FR-10) and non-functional requirements (performance, safety, observability).