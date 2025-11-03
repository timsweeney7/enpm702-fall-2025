=====================
Requirements Analysis
=====================

The **requirements analysis** defines **what** the system must do before designing **how** it will work.
It captures functional capabilities, quality attributes, constraints, and measurable success criteria
for the vehicle domain (Driver, Vehicle, Engine, Route).

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
     - The system shall allow a Driver to **take control** of a Vehicle and **release control**.
     - Must
   * - FR-2
     - The system shall allow a Driver to **start** and **stop** the Vehicle's engine through the Vehicle interface.
     - Must
   * - FR-3
     - The system shall support **polymorphic driving behavior**: a Vehicle subclass (Car, Truck, Train) must implement ``drive()``.
     - Must
   * - FR-4
     - The system shall enforce a **single Engine per Vehicle** and prevent engine operations when the Vehicle is not under control or in an invalid state.
     - Must
   * - FR-5
     - The system shall allow a Vehicle to **follow an optional Route**; if a Route is assigned, the Vehicle shall retrieve route segments during driving.
     - Must
   * - FR-6
     - The system shall expose **status queries** (e.g., ``isRunning``, current route presence, vehicle type).
     - Should
   * - FR-7
     - The system shall **log key lifecycle events** (control acquired/released, engine started/stopped, route assigned/cleared).
     - Should
   * - FR-8
     - The system shall **reject invalid commands** (e.g., starting an already running engine, driving without control) and return descriptive errors.
     - Must
   * - FR-9
     - The system shall allow **assigning** and **clearing** a Route on a Vehicle at runtime.
     - Should
   * - FR-10
     - The system shall support **type-specific capabilities** (e.g., Car: ``openTrunk()``, Truck: ``lowerTailgate()``, Train: ``blowHorn()``).
     - Could

----------------------------
Non-Functional Requirements
----------------------------

.. list-table::
   :widths: 25 75
   :header-rows: 1

   * - **Attribute**
     - **Requirement**
   * - Performance
     - Engine start/stop commands shall complete within **200 ms** (simulated subsystem), and route segment retrieval shall not add more than **50 ms** latency per segment under nominal load.
   * - Reliability
     - The system shall handle transient failures (e.g., start failure) with retries or clear error reporting; mean time between recoverable faults **> 24 h** for demo workloads.
   * - Safety
     - The system shall prevent unsafe transitions (e.g., stopping engine while in motion without safe deceleration logic) via validated state checks in the Vehicle.
   * - Availability
     - Control and status operations shall be available **99.5%** during test sessions.
   * - Observability
     - All state transitions and command outcomes shall be emitted as structured events with timestamps and identifiers (vehicle ID, driver ID, route ID).
   * - Maintainability
     - The system shall separate concerns by layers (Presentation, Application, Domain, Infrastructure) and achieve **< 10%** cyclic dependency density in static analysis.
   * - Extensibility
     - Adding a new Vehicle subtype shall require **no changes** to existing Vehicle consumers beyond configuration or registration.

----------------------
Technical Constraints
----------------------

.. list-table::
   :widths: 28 72
   :header-rows: 1

   * - **Constraint**
     - **Description**
   * - Layered Architecture
     - Presentation → Application → Domain; Application ↔ Infrastructure via repositories/gateways; Domain independent of frameworks.
   * - Encapsulation
     - Drivers shall not call Engine directly. All powertrain operations pass through the Vehicle API.
   * - Composition Rule
     - Exactly one Engine per Vehicle (composition). Engine lifecycle is bound to Vehicle lifecycle.
   * - Optional Route
     - Route association is optional at runtime. Driving shall function without a Route assigned.
   * - Type Abstraction
     - Diagram types are language agnostic (e.g., ``String``), and mapping to concrete types (e.g., ``std::string``) is an implementation detail.
   * - Error Handling
     - Commands must return typed results or exceptions with machine-readable codes and human-readable messages.

----------------
Success Criteria
----------------

.. list-table::
   :widths: 35 65
   :header-rows: 1

   * - **Criterion**
     - **Measurable Outcome**
   * - Engine Lifecycle Control
     - Issuing ``startEngine()`` from a controlled state sets ``isRunning = true`` within **200 ms** and logs the event; ``stopEngine()`` resets the flag and logs within **200 ms**.
   * - Polymorphic Drive
     - For Car, Truck, Train, invoking ``drive()`` produces type-specific behavior without code changes in callers; verified by unit tests covering all subtypes (**> 95%** branch coverage on drive logic).
   * - Route Optionality
     - Vehicle drives successfully with and without a Route; when a Route is assigned, at least **90%** of segments are retrieved within **50 ms** each under nominal load.
   * - Safety Guards
     - Invalid commands (e.g., start when already running) are rejected with explicit error codes in **100%** of negative test cases.
   * - Separation of Concerns
     - Static analysis reports **0** direct dependencies from Presentation to Domain or Infrastructure; only Application mediates.
   * - Observability
     - Logs contain complete audit trails (control, engine, routing) with **no missing events** in end-to-end tests across **N ≥ 50** scripted scenarios.

-------------------------
Assumptions and Scope
-------------------------

- A single Vehicle has exactly one Engine.  
- A Driver may or may not be in control at any given time.  
- A Vehicle may follow **zero or one** current Route; Routes may be reused across vehicles over time.  
- Real hardware effects are simulated; timings refer to software execution in the target environment.

-----------------------
Verification Approach
-----------------------

- **Unit tests** for Vehicle state guards, Engine delegation, and subtype-specific ``drive()`` behavior.  
- **Integration tests** for Driver–Vehicle interactions and Route assignment and traversal.  
- **Contract tests** for repository and gateway adapters (Infrastructure) to ensure stable interfaces.  
- **Static analysis** for dependency direction and absence of forbidden couplings.
