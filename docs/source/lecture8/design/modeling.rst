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

This class diagram represents a simplified **vehicle control system**, showing how various entities
interact and relate to each other through inheritance, composition, aggregation, and association.
It models the structural organization of the system and the ownership or interaction patterns
between its classes.

.. note::

   All classes in the domain layer are organized within the ``transportation`` namespace, providing
   logical grouping and preventing naming conflicts with other system components.

~~~~~~~~~~~~~~~~
Key Components
~~~~~~~~~~~~~~~~

**Vehicle (Abstract Class)**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- **Purpose:** Defines the general structure and behavior common to all vehicle types.
- **Namespace:** ``transportation``
- **Attributes:**

  - ``color : String`` – The exterior color of the vehicle for identification purposes
  - ``model : String`` – The model name or designation of the vehicle (e.g., "Sedan", "SUV")
  - ``isRunning : Boolean`` – Indicates whether the vehicle's engine is currently running
  - ``maxSpeed : int`` – The maximum speed the vehicle can achieve (in km/h or mph)
  - ``engine : Engine`` – The vehicle's powertrain component (composition relationship)

- **Operations:**

  - ``startEngine()`` — Starts the vehicle's engine if not already running; returns error if already running
  - ``stopEngine()`` — Stops the engine safely; validates vehicle is in a safe state
  - ``{abstract} drive()`` — Must be implemented by subclasses to define type-specific driving behavior

.. note::
    The ``Vehicle`` class is abstract, meaning it cannot be instantiated directly.
    It provides a consistent interface for all concrete vehicles and enforces safety guards
    such as rejecting invalid state transitions (e.g., starting an already running engine).

**Concrete Vehicle Types**
^^^^^^^^^^^^^^^^^^^^^^^^^^

All concrete vehicle types reside in the ``transportation`` namespace and inherit from ``Vehicle``.

1. **Car**

   - **Additional Attributes:** ``numberOfDoors : int`` – Number of passenger doors
   - **Operations:**
     
     - ``openTrunk()`` – Opens the trunk compartment
     - ``drive()`` – Implements car-specific driving behavior

2. **Truck**

   - **Additional Attributes:** ``cargoCapacity : double`` – Maximum cargo weight capacity (in kg or tons)
   - **Operations:**
     
     - ``lowerTailgate()`` – Lowers the rear tailgate for loading
     - ``drive()`` – Implements truck-specific driving behavior with cargo considerations

3. **Train**

   - **Additional Attributes:** ``numberOfCars : int`` – Number of connected railway cars
   - **Operations:**
     
     - ``blowHorn()`` – Activates the train horn
     - ``drive()`` – Implements train-specific driving behavior along tracks

Each subclass specializes the ``Vehicle`` class by providing concrete driving behavior and
type-specific attributes and operations.

**Engine**
^^^^^^^^^^

- **Namespace:** ``transportation``
- **Attributes:** ``horsepower : int`` – Engine power rating
- **Operations:** 
  
  - ``start()`` – Initiates engine operation (completes within 200 ms)
  - ``stop()`` – Shuts down engine operation (completes within 200 ms)

- **Relationship:** Composition (``*--``) with ``Vehicle``.
  A vehicle contains exactly one engine; if the vehicle is destroyed,
  the engine is destroyed as well. This enforces the constraint that each
  vehicle has a single, bound powertrain.
- **Purpose:** Represents the mechanical subsystem responsible for power and motion.

.. important::
   **Encapsulation Rule:** Drivers and other external actors cannot interact directly with
   the Engine. All powertrain operations must pass through the Vehicle API, which manages
   engine state and enforces safety constraints.

**Driver**
^^^^^^^^^^

- **Namespace:** ``transportation``
- **Attributes:**

  - ``name : String`` – Driver's name
  - ``licenseId : String`` – Unique driver license identifier

- **Operations:**

  - ``takeControl(v: Vehicle)`` — Takes control of a vehicle; must succeed before issuing commands
  - ``releaseControl()`` — Releases control of the current vehicle
  - ``drive(v: Vehicle)`` — Commands a vehicle to drive; vehicle must be under control

- **Relationship:** Aggregation (``o--``) with ``Vehicle``.
  The driver operates a vehicle but does not own it; both exist independently.
  A driver may or may not be in control of a vehicle at any given time.

**Route**
^^^^^^^^^

- **Namespace:** ``transportation``
- **Attributes:**

  - ``routeId : String`` – Unique route identifier
  - ``startLocation : String`` – Starting point of the route
  - ``endLocation : String`` – Destination point of the route
  - ``distance : double`` – Total route distance (in km or miles)

- **Operations:** ``getRouteInfo()`` – Retrieves route segment information (< 50 ms per segment)
- **Relationship:** Association (``-->``) with ``Vehicle``.
  A vehicle may follow zero or one route, while a route may be associated with multiple vehicles.
  Route association is optional; vehicles can operate without an assigned route.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Relationship Summary
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. list-table::
   :widths: 20 45 35
   :header-rows: 1

   * - **Relationship**
     - **Description**
     - **Example**
   * - **Inheritance (Generalization)**
     - Indicates an "is-a" hierarchy where subclasses extend a base class.
     - .. only:: html

          .. figure:: /_static/lecture8/design/inheritance-light.png
             :alt: Inheritance (light)
             :width: 200
             :align: center
             :class: only-light

          .. figure:: /_static/lecture8/design/inheritance-dark.png
             :alt: Inheritance (dark)
             :width: 200
             :align: center
             :class: only-dark
   * - **Composition**
     - Strong ownership; the part cannot exist independently of the whole.
     - .. only:: html

          .. figure:: /_static/lecture8/design/composition-light.png
             :alt: Composition (light)
             :width: 200
             :align: center
             :class: only-light

          .. figure:: /_static/lecture8/design/composition-dark.png
             :alt: Composition (dark)
             :width: 200
             :align: center
             :class: only-dark
   * - **Aggregation**
     - Weak ownership; objects can exist independently of one another.
     - .. only:: html

          .. figure:: /_static/lecture8/design/aggregation-light.png
             :alt: Aggregation (light)
             :width: 200
             :align: center
             :class: only-light

          .. figure:: /_static/lecture8/design/aggregation-dark.png
             :alt: Aggregation (dark)
             :width: 200
             :align: center
             :class: only-dark
   * - **Association**
     - Simple connection indicating interaction between two objects.
     - .. only:: html

          .. figure:: /_static/lecture8/design/association-light.png
             :alt: Association (light)
             :width: 200
             :align: center
             :class: only-light

          .. figure:: /_static/lecture8/design/association-dark.png
             :alt: Association (dark)
             :width: 200
             :align: center
             :class: only-dark
   * - **Dependency**
     - A temporary or usage-based relationship.
     - .. only:: html

          .. figure:: /_static/lecture8/design/dependency-light.png
             :alt: Dependency (light)
             :width: 200
             :align: center
             :class: only-light

          .. figure:: /_static/lecture8/design/dependency-dark.png
             :alt: Dependency (dark)
             :width: 200
             :align: center
             :class: only-dark

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Conceptual Analysis
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- **Encapsulation of Behavior:**  
  The ``Vehicle`` encapsulates engine control internally. The ``Driver`` only interacts with the
  ``Vehicle`` interface, never with the ``Engine`` directly. This promotes abstraction and separation
  of concerns, and enforces the technical constraint that drivers cannot call Engine directly.

- **Polymorphism:**  
  Concrete vehicles override the abstract ``drive()`` method, enabling dynamic behavior depending
  on the vehicle type at runtime. This satisfies the requirement for polymorphic driving behavior
  across Car, Truck, and Train subtypes.

- **Optional Relationships:**  
  The ``Route`` association is optional; a vehicle can operate without being assigned a route.
  Similarly, a ``Driver`` may or may not be controlling a vehicle at a given time.

- **Ownership Hierarchy:**  

  - ``Vehicle`` **owns** ``Engine`` — composition (single engine per vehicle).  
  - ``Driver`` **operates** ``Vehicle`` — aggregation (independent lifecycles).  
  - ``Vehicle`` **follows** ``Route`` — association (optional relationship).

- **Safety and Error Handling:**
  The ``Vehicle`` enforces safety guards by rejecting invalid commands (e.g., starting an already
  running engine, driving without driver control) and returning descriptive error codes and messages.

~~~~~~~~~~~~~~~~~~~~~~~~~~
Performance Requirements
~~~~~~~~~~~~~~~~~~~~~~~~~~

.. note::

   **Performance Constraints:**
   
   - Engine ``start()`` and ``stop()`` operations complete within **200 ms**
   - Route ``getRouteInfo()`` retrieval completes within **50 ms per segment**
   - Control operations maintain **99.5% availability** during test sessions
   - All state transitions are logged with timestamps and entity identifiers

~~~~~~~~~~~~~~~~
Summary
~~~~~~~~~~~~~~~~

This class diagram demonstrates several key object-oriented principles:

- **Abstraction** through the abstract ``Vehicle`` class.  
- **Inheritance** and **polymorphism** in specialized vehicle types.  
- **Encapsulation** of functionality within cohesive classes.  
- **Composition** and **aggregation** to model strong and weak ownership.  
- **Clear separation of concerns** between control (Driver), behavior (Vehicle),
  and resources (Engine, Route).
- **Safety constraints** enforced through validated state transitions and error handling.

Overall, the design offers modularity, flexibility for extension, and
a realistic mapping between software classes and physical entities, while satisfying
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
      :width: 70%
      :class: only-light

   .. figure:: /_static/lecture8/design/sequence_diagram_dark.png
      :alt: Sequence Diagram
      :align: center
      :width: 70%
      :class: only-dark

~~~~~~~~~~~~~~~~~~~~~~
Participants
~~~~~~~~~~~~~~~~~~~~~~

All participants belong to the ``transportation`` namespace in the implementation:

- **Driver** – External actor initiating commands; must take control before issuing operations.  
- **Vehicle** – Responds to driver requests, manages internal state, and controls the engine.  
- **Engine** – Performs physical start/stop operations (200 ms completion target).  
- **Route** – (Optional) Provides path information for navigation (50 ms per segment retrieval).

~~~~~~~~~~~~~~~~~~~~~~
Message Flow
~~~~~~~~~~~~~~~~~~~~~~

1. **Driver takes control** of the vehicle (``takeControl(v)``).  
   - Vehicle validates the request and grants control.
   - Without control, subsequent commands will be rejected.

2. **Driver requests** the vehicle to start the engine (``startEngine()``).  
   - Vehicle checks ``isRunning`` state.  
   - If not running, Vehicle delegates ``start()`` to the Engine (completes within 200 ms).  
   - If already running, it returns an error status with descriptive message.
   - State transition is logged with timestamp and vehicle identifier.

3. **Driver initiates driving** (``drive()``).  
   - Vehicle validates that it is under control and engine is running.
   - Vehicle may optionally follow a ``Route`` if one is assigned.  
   - During driving, Vehicle adjusts engine power per segment (Route retrieval < 50 ms per segment).
   - Polymorphic ``drive()`` behavior executes based on vehicle subtype (Car, Truck, or Train).

4. **Driver stops and releases control**.  
   - Vehicle stops the engine (``stopEngine()`` → ``Engine.stop()``).
   - Engine stop completes within 200 ms.
   - State transition is logged.
   - Control returns to the driver via ``releaseControl()``.

~~~~~~~~~~~~~~~~~~~~~~
Control Constructs
~~~~~~~~~~~~~~~~~~~~~~

- **alt [isRunning == false / true]**: Vehicle decides whether to start or skip engine startup based on current state.  
- **opt [route assigned]**: Route interaction occurs only when a route exists (optional relationship).  
- **loop [for each segment]**: Vehicle iterates over route segments during driving.  

~~~~~~~~~~~~~~~~~~~~~~
Error Handling
~~~~~~~~~~~~~~~~~~~~~~

The sequence diagram demonstrates error handling for invalid state transitions:

- Attempting to start an already running engine returns an error message
- Commands issued without driver control are rejected
- All errors include machine-readable codes and human-readable descriptions
- State validation occurs before executing operations

~~~~~~~~~~~~~~~~~~~~~~
Observability
~~~~~~~~~~~~~~~~~~~~~~

All key lifecycle events are logged with structured information:

- Control acquired/released (driver ID, vehicle ID, timestamp)
- Engine started/stopped (vehicle ID, timestamp, operation duration)
- Route assigned/cleared (vehicle ID, route ID, timestamp)
- Command outcomes (success/failure, error codes if applicable)

~~~~~~~~~~~~~~~~~~~~~~
Summary
~~~~~~~~~~~~~~~~~~~~~~

The sequence diagram complements the class diagram by showing the **runtime collaboration**
of objects. It clarifies the responsibilities of each component:

- The **Driver** only issues commands and must establish control first.  
- The **Vehicle** owns the operational logic, enforces safety guards, and delegates engine control internally.  
- The **Engine** executes low-level start/stop actions within performance constraints.  
- The **Route** is consulted optionally to support navigation.

Together, the class, sequence, and state machine diagrams provide a complete behavioral
and structural model of the vehicle system that satisfies both functional requirements
(FR-1 through FR-10) and non-functional requirements (performance, safety, observability).
