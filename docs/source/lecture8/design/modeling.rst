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
- **State Machine Diagrams** – Capture the lifecycle and state transitions of objects.
- **System Architecture Diagrams** – Show the high-level organization of components or layers
  that make up the entire system.

Each diagram contributes to a comprehensive understanding of both the **structural** and
**behavioral** aspects of the system.


.. note::

   The naming conventions for **classes**, **attributes**, and **methods** used in these diagrams
   are **language-agnostic**.  
   The same applies to data types (for example, ``String`` is used instead of ``std::string`` or
   ``string``). This abstraction ensures that the design can be applied across multiple programming
   languages and paradigms without being tied to a specific implementation syntax.


Class Diagram
---------------

.. The **Class Diagram** illustrates the static structure of the system by showing the main classes,
.. their attributes, operations, and the relationships among them. It is the foundation of object-oriented
.. design, helping to organize the system into modular and maintainable components.

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

~~~~~~~~~~~~~~~~
Key Components
~~~~~~~~~~~~~~~~

**Vehicle (Abstract Class)**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- **Purpose:** Defines the general structure and behavior common to all vehicle types.
- **Attributes:**

  - ``color : String``
  - ``model : String``
  - ``isRunning : Boolean``
- **Operations:**

  - ``startEngine()`` — Starts the vehicle's engine.
  - ``stopEngine()`` — Stops the engine safely.
  - ``{abstract} drive()`` — Must be implemented by subclasses.

.. note::
    The ``Vehicle`` class is abstract, meaning it cannot be instantiated directly.
    It provides a consistent interface for all concrete vehicles.

**Concrete Vehicle Types**
^^^^^^^^^^^^^^^^^^^^^^^^^^
1. **Car**

   - Adds ``numberOfDoors : int``
   - Defines ``openTrunk()`` and implements ``drive()``

2. **Truck**

   - Adds ``cargoCapacity : double``
   - Defines ``lowerTailgate()`` and implements ``drive()``

3. **Train**

   - Adds ``numberOfCars : int``
   - Defines ``blowHorn()`` and implements ``drive()``

Each subclass specializes the ``Vehicle`` class by providing concrete driving behavior and
type-specific attributes.

**Engine**
^^^^^^^^^^

- **Attributes:** ``horsepower : int``
- **Operations:** ``start()``, ``stop()``
- **Relationship:** Composition (``*--``) with ``Vehicle``.
  A vehicle contains exactly one engine; if the vehicle is destroyed,
  the engine is destroyed as well.
- **Purpose:** Represents the mechanical subsystem responsible for power and motion.

**Driver**
^^^^^^^^^^

- **Attributes:**

  - ``name : String``
  - ``licenseId : String``

- **Operations:**

  - ``takeControl(v: Vehicle)`` — Takes control of a vehicle.
  - ``releaseControl()`` — Releases control.
  - ``drive(v: Vehicle)`` — Commands a vehicle to drive.

- **Relationship:** Aggregation (``o--``) with ``Vehicle``.
  The driver operates a vehicle but does not own it; both exist independently.

**Route**
^^^^^^^^^

- **Attributes:**

  - ``routeId : String``
  - ``startLocation : String``
  - ``endLocation : String``
  - ``distance : double``
- **Operations:** ``getRouteInfo()``
- **Relationship:** Association (``-->``) with ``Vehicle``.
  A vehicle may follow zero or one route, while a route may be associated with multiple vehicles.

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
  of concerns.

- **Polymorphism:**  
  Concrete vehicles override the abstract ``drive()`` method, enabling dynamic behavior depending
  on the vehicle type at runtime.

- **Optional Relationships:**  
  The ``Route`` association is optional; a vehicle can operate without being assigned a route.
  Similarly, a ``Driver`` may or may not be controlling a vehicle at a given time.

- **Ownership Hierarchy:**  

  - ``Vehicle`` **owns** ``Engine`` — composition.  
  - ``Driver`` **operates** ``Vehicle`` — aggregation.  
  - ``Vehicle`` **follows** ``Route`` — association.

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

Overall, the design offers modularity, flexibility for extension, and
a realistic mapping between software classes and physical entities.

.. ~~~~~~~~~~~~~~~~~~~~~~
.. Class Box Structure
.. ~~~~~~~~~~~~~~~~~~~~~~

.. Each **class** is represented as a box divided into three sections:

.. 1. **Class Name**  
..    The top compartment contains the name of the class. 

..    - Abstract classes are usually written in *italics*.  
..    - Interfaces may include a stereotype such as ``<<interface>>``.

.. 2. **Attributes (Fields)**  
..    The middle compartment lists the data members.  
..    Format: ``visibility name : Type``  

..    - ``+`` = public  
..    - ``-`` = private  
..    - ``#`` = protected  
..    - ``~`` = package/internal

.. 3. **Methods (Operations)**  
..    The bottom compartment lists behaviors. 

..    - Format: ``visibility name(parameters) : ReturnType``  

.. ~~~~~~~~~~~~~~~~~~~~~~
.. Relationship Types
.. ~~~~~~~~~~~~~~~~~~~~~~

.. .. list-table::
..    :widths: 20 45 35
..    :header-rows: 1

..    * - **Relationship**
..      - **Description**
..      - **Example**
..    * - **Inheritance (Generalization)**
..      - Models an “is-a” relationship between a superclass and its subclasses.
..      - ``Vehicle <|-- Car`` or ``Vehicle <|-- Truck``
..    * - **Association**
..      - A simple connection between two classes indicating that one uses or interacts with the other.
..      - ``Vehicle --> Route : follows``
..    * - **Aggregation (open diamond)**
..      - A “has-a” relationship with shared ownership. The part can exist independently of the whole.
..      - ``Driver o-- Vehicle : operates``
..    * - **Composition (filled diamond)**
..      - A strong ownership relationship; if the whole is destroyed, the part is too.
..      - ``Vehicle *-- Engine : contains``
..    * - **Dependency (dashed arrow)**
..      - Indicates that one class temporarily depends on another (e.g., as a parameter or return type).
..      - ``Application Layer ..> Domain Layer``


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

- **Driver** – External actor initiating commands.  
- **Vehicle** – Responds to driver requests and controls internal behavior.  
- **Engine** – Performs physical start/stop operations.  
- **Route** – (Optional) Provides path information for navigation.

~~~~~~~~~~~~~~~~~~~~~~
Message Flow
~~~~~~~~~~~~~~~~~~~~~~

1. **Driver takes control** of the vehicle (``takeControl(v)``).  
2. **Driver requests** the vehicle to start the engine (``startEngine()``).  
   - Vehicle checks ``isRunning``.  
   - If not running, Vehicle delegates ``start()`` to the Engine.  
   - If already running, it returns a status message.  
3. **Driver initiates driving** (``drive()``).  
   - Vehicle may optionally follow a ``Route`` if one is assigned.  
   - During driving, Vehicle adjusts engine power per segment.  
4. **Driver stops and releases control**.  
   - Vehicle stops the engine (``stopEngine()`` → ``Engine.stop()``).  
   - Control returns to the driver.

~~~~~~~~~~~~~~~~~~~~~~
Control Constructs
~~~~~~~~~~~~~~~~~~~~~~

- **alt [isRunning == false / true]**: Vehicle decides whether to start or skip engine startup.  
- **opt [route assigned]**: Route interaction occurs only when a route exists.  
- **loop [for each segment]**: Vehicle iterates over route segments during driving.  

~~~~~~~~~~~~~~~~~~~~~~
Summary
~~~~~~~~~~~~~~~~~~~~~~

The sequence diagram complements the class diagram by showing the **runtime collaboration**
of objects. It clarifies the responsibilities of each component:

- The **Driver** only issues commands.  
- The **Vehicle** owns the operational logic and delegates engine control internally.  
- The **Engine** executes low-level start/stop actions.  
- The **Route** is consulted optionally to support navigation.

Together, the class, sequence, and state machine diagrams provide a complete behavioral
and structural model of the vehicle system.



State Machine Diagram
-----------------------

This diagram models the **Vehicle** object's lifecycle as it transitions through various operational states. It represents how the vehicle responds to events such as being controlled by a driver, starting or stopping its engine, driving, and encountering faults.


.. only:: html

   .. figure:: /_static/lecture8/design/state_machine_diagram_light.png
      :alt: Sequence Diagram
      :align: center
      :width: 100%
      :class: only-light

   .. figure:: /_static/lecture8/design/state_machine_diagram_dark.png
      :alt: Sequence Diagram
      :align: center
      :width: 100%
      :class: only-dark

~~~~~~~~~~~~~~~~~~~~
Top-Level Structure
~~~~~~~~~~~~~~~~~~~~

At the highest level, the vehicle has two main control states:

- **Uncontrolled** – The vehicle is not under a driver's control.  
- **Controlled** – The driver has taken control of the vehicle.

A driver initiates control using the ``takeControl(v)`` event, which transitions the vehicle from *Uncontrolled* to *Controlled*. Releasing control (``releaseControl()``) returns it to *Uncontrolled*.

~~~~~~~~~~~~~~~~~~~~~~
Controlled Substates
~~~~~~~~~~~~~~~~~~~~~~

When the vehicle is *Controlled*, it can be in one of several substates related to its engine status:

1. **EngineOff**
2. **EngineOn**
3. **Fault**

^^^^^^^^^^^^
EngineOff
^^^^^^^^^^^^

- The default state once the driver gains control.  
- Entry action: ``isRunning = false``.  
- Transition:
  - ``startEngine()`` moves the system to *EngineOn*, invoking ``Engine.start()``.
  - If the engine fails to start, transition to *Fault*.

^^^^^^^^^^^^
EngineOn
^^^^^^^^^^^^

A **composite state** representing the vehicle when the engine is running. It contains two substates:

- **Idle** – The engine is on, but the vehicle is stationary. Entry action: ``isRunning = true``.  
- **Driving** – The vehicle is moving. Transitioned by ``drive()`` from *Idle*.

Within *Driving*, the vehicle:

- Regulates its speed.
- Interacts with the ``Route`` object if one is assigned (optional).
- Adjusts power through its ``Engine`` based on terrain and speed.

Transitions:

- ``stopEngine()`` → returns to *EngineOff* after safely stopping.
- Internal error → moves to *Fault*.

^^^^^^^^^^^^
Fault
^^^^^^^^^^^^

Represents a condition where the vehicle encounters an operational error, such as a failed engine start or runtime issue.

- Entry action: diagnostic reporting and system check.
- Recovery transition: ``recover / reset`` returns to *EngineOff*.

~~~~~~~~~~~~~~~~~~~~~~
Route Integration
~~~~~~~~~~~~~~~~~~~~~~


The route-following behavior is **optional**.  
If a ``Route`` object is assigned, the vehicle queries it segment-by-segment while in the *Driving* state.  
If no route is assigned, the vehicle continues free driving.

~~~~~~~~~~~~~~~~~~~~~~
State Transitions
~~~~~~~~~~~~~~~~~~~~~~


.. list-table::
   :widths: 25 45
   :header-rows: 1

   * - **Event**
     - **Transition**
   * - ``takeControl(v)``
     - Uncontrolled → Controlled
   * - ``releaseControl()``
     - Controlled → Uncontrolled
   * - ``startEngine()``
     - EngineOff → EngineOn
   * - ``startEngine() / fail``
     - EngineOff → Fault
   * - ``drive()``
     - Idle → Driving
   * - ``stopEngine()``
     - EngineOn → EngineOff
   * - ``internal error``
     - EngineOn → Fault
   * - ``recover / reset``
     - Fault → EngineOff

~~~~~~~~~~~~~~~~~~~~~~
Summary
~~~~~~~~~~~~~~~~~~~~~~


This state machine formalizes the **Vehicle's dynamic behavior** within the system. It shows:

- Clear ownership of engine control by the vehicle.
- Optional route following during driving.
- Fault detection and recovery mechanisms.
- Control delegation between the driver and vehicle.

The design ensures separation of responsibilities:
the **Driver** issues commands, while the **Vehicle** autonomously manages its internal engine and driving logic.


System Architecture
---------------------

The **System Architecture** defines the high-level organization of the system by grouping related classes into
packages or layers. This structure clarifies the system's modular design and the direction of dependencies between components.
By separating responsibilities, it enhances maintainability, testability, and scalability.

**Context.** This system follows a **layered architecture**:

- **Presentation Layer**: Interfaces like ``DriverUI`` handle user input.  
- **Application Layer**: ``VehicleController`` coordinates actions and interacts with services.  
- **Domain Layer**: Core entities like ``Vehicle``, ``Engine``, ``Driver``, and ``Route`` encapsulate business logic.  
- **Infrastructure Layer**: Classes like ``VehicleRepository`` or ``MapServiceClient`` handle persistence and integration.

``Vehicle`` is an abstract base class with subclasses ``Car``, ``Truck``, and ``Train``.
It contains a single ``Engine`` (composition) and can optionally follow a ``Route``.
The ``Driver`` aggregates the ``Vehicle`` and issues commands.
``VehicleController`` orchestrates domain operations across the layers.

~~~~~~~~~~~~~~~~~~~~~
Layered Architecture
~~~~~~~~~~~~~~~~~~~~~

The system is divided into **four logical layers**, each responsible for a distinct set of concerns:

1. **Presentation Layer**
   - Handles user interaction and interface-related functionality.
   - Collects user input (e.g., from ``DriverUI``) and forwards requests to the application layer.
   - Does not contain business logic; its sole role is to communicate with the underlying services.

2. **Application Layer**
   - Coordinates use cases and workflows that involve multiple domain entities.
   - Contains classes like ``VehicleController`` and ``RoutingService`` that orchestrate domain logic.
   - Relies on the domain layer for rules and entities, and the infrastructure layer for persistence or external communication.

3. **Domain Layer**
   - Represents the **core business logic** and fundamental concepts of the system.
   - Includes entities such as ``Vehicle``, ``Engine``, ``Route``, and ``Driver``.
   - Implements rules like engine control, route following, and driver operations.
   - Should remain independent of infrastructure or presentation technologies.

4. **Infrastructure Layer**
   - Provides technical capabilities like persistence, communication, and data access.
   - Contains adapters and repositories such as ``VehicleRepository``, ``RouteRepository``, ``TelemetryGateway``, and ``MapServiceClient``.
   - Depends on the domain layer to understand entity structures but not vice versa.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Dependency Flow and Purpose
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


.. figure:: /_static/lecture8/design/system_architecture_diagram_light.png
   :alt: Layered System Architecture
   :align: center
   :width: 90%
   :class: only-light

.. figure:: /_static/lecture8/design/system_architecture_diagram_dark.png
   :alt: Layered System Architecture
   :align: center
   :width: 90%
   :class: only-dark

**Dependency Direction:**

- **Presentation → Application → Domain**  
  The Presentation layer calls Application services, which in turn coordinate Domain logic.

- **Application ↔ Infrastructure**  
  The Application layer depends on Infrastructure interfaces (repositories, gateways), while Infrastructure provides their implementations.

- **Infrastructure ..> Domain**  
  Infrastructure depends on the Domain for data structures and mapping definitions.

**Benefits of the Layered Approach:**

- **Modularity:** Each layer focuses on a specific concern, making it easier to understand and modify.  
- **Maintainability:** Changes in one layer have minimal impact on others.  
- **Testability:** Domain and Application logic can be tested independently of the UI or data storage.  
- **Replaceability:** Infrastructure components (e.g., databases, map clients) can be swapped with minimal code changes.  

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Inter-Layer Mapping
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


.. list-table::
   :widths: 25 25 50
   :header-rows: 1

   * - **Layer**
     - **Example Classes**
     - **Responsibilities**
   * - **Presentation**
     - ``DriverUI``
     - Collects user input, displays system output, and forwards user actions to the Application layer.
   * - **Application**
     - ``VehicleController``, ``RoutingService``
     - Manages use cases, orchestrates domain objects, and enforces system-level workflows.
   * - **Domain**
     - ``Vehicle``, ``Car``, ``Truck``, ``Train``, ``Engine``, ``Driver``, ``Route``
     - Implements business logic, relationships, and state transitions.
   * - **Infrastructure**
     - ``VehicleRepository``, ``RouteRepository``, ``TelemetryGateway``, ``MapServiceClient``
     - Handles persistence, communication, and external data integration.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Architectural View
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


The architecture enforces a **clean separation of concerns**, ensuring that:

- The **Domain Layer** remains technology-agnostic and reusable across projects.  
- The **Application Layer** drives behavior without knowing how infrastructure is implemented.  
- The **Presentation Layer** simply provides the interface for users or systems.  
- The **Infrastructure Layer** plugs in concrete implementations for persistence, messaging, and APIs.

Together, these layers support a **flexible, modular, and extensible system design** consistent with modern object-oriented
and domain-driven design principles.
