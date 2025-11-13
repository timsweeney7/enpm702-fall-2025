===========
Abstraction
===========

**Definition:** Abstraction exposes a *stable interface* and hides *implementation details*. Users depend on *what* the type does (the contract), not *how* it does it (the implementation).

Key Benefits
------------

**Simplicity**
  Small public surface with clear semantics

**Modularity**
  Independent evolution of internals without breaking clients

**Maintainability**
  Fewer ripple effects across codebase

**Testability**
  Mock the interface, validate behavior independently

**Flexibility**
  Swap implementations without changing client code

When to Use Abstract Classes
-----------------------------

Create abstract classes when you want to:

1. **Define a contract** that multiple concrete types must follow
2. **Enable polymorphic behavior** across different implementations
3. **Prevent direct instantiation** of incomplete/conceptual types
4. **Share common behavior** while requiring specialization
5. **Design plugin architectures** where clients provide implementations

Example Scenarios
~~~~~~~~~~~~~~~~~

**Device drivers**
  Implement ``Device`` interface

**Geometric shapes**
  Implement ``Shape`` interface

**Data sources**
  Implement ``DataSource`` interface

**UI widgets**
  Implement ``Widget`` interface

**Strategy patterns**
  Implement ``Strategy`` interface

How is Abstraction Implemented in C++?
---------------------------------------

**Abstract Classes**
  Define behavior as a contract using pure ``virtual`` methods

**Pure** ``virtual`` **Methods**
  Enforce implementation in derived types (``= 0``)

**Encapsulation**
  Keep data private or protected; expose intent through methods

**Example:**

.. code-block:: cpp

   class Vehicle {
   public:
       virtual ~Vehicle() = default;
       
       // Pure virtual - must be implemented in derived classes
       virtual void drive() = 0;
       
       // Pure virtual - must be implemented in derived classes
       virtual void update_location(const Location& location) = 0;
   };

Pure ``virtual`` Methods (``= 0``)
-----------------------------------

**Definition:** A **pure** ``virtual`` **method** is declared with ``= 0`` and:

- **Makes the class abstract** — cannot be instantiated
- **Requires derived classes to implement** the method
- **Defines a contract** that concrete classes must fulfill
- Can optionally provide a default implementation (rare)

Basic Example
~~~~~~~~~~~~~

.. code-block:: cpp

   class Vehicle {
   public:
       virtual ~Vehicle() = default;
       virtual void drive() = 0;  // Pure virtual method
   };

   // transportation::Vehicle v;  // ERROR: cannot instantiate abstract class

   class RoboTaxi : public Vehicle {
   public:
       void drive() override { 
           /* implementation required */ 
       }
   };

   RoboTaxi rt;  // OK - RoboTaxi has overridden drive()

.. note::

   A caller invokes ``vehicle->drive()`` without knowledge of internal details. Any conforming concrete type satisfies the same contract.

Abstract Class Requirements
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A class is **abstract** if it has at least one pure ``virtual`` method. An abstract class:

- **Cannot be instantiated** directly
- **Can have constructors** (for derived classes to call)
- **Can have data members** (typically ``protected``)
- **Can mix pure and regular virtual methods**
- **Can have non-virtual methods**

.. code-block:: cpp

   class Shape {
   protected:
       Point center_;  // Data member
       
   public:
       // Constructor (for derived classes)
       Shape(const Point& center) : center_{center} {}
       
       // Pure virtual - must override
       virtual double area() const = 0;
       virtual void draw() const = 0;
       
       // Regular virtual - can override
       virtual void move(const Vector& offset) {
           center_ = center_ + offset;
       }
       
       // Non-virtual - cannot override
       Point get_center() const { return center_; }
       
       // Virtual destructor
       virtual ~Shape() = default;
   };

Pure Virtual with Default Implementation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A pure ``virtual`` method can optionally provide a default implementation that derived classes can call explicitly:

.. code-block:: cpp

   class Logger {
   public:
       virtual ~Logger() = default;
       
       // Pure virtual with implementation
       virtual void log(const std::string& message) = 0 {
           // Default implementation
           std::cout << "[LOG] " << message << '\n';
       }
   };

   class FileLogger : public Logger {
   public:
       void log(const std::string& message) override {
           // Can call base implementation
           Logger::log(message);
           // Add file-specific behavior
           write_to_file(message);
       }
   };

.. note::

   This pattern is rare but useful when you want to enforce implementation while providing a fallback.

Concrete Classes
----------------

**Definition:** A concrete class is a class that can be instantiated. It provides complete implementations for all inherited pure ``virtual`` methods.

Key Characteristics
~~~~~~~~~~~~~~~~~~~

**Fully defined**
  Implements all inherited pure ``virtual`` methods

**Instantiable**
  Can create objects directly

**Observable behavior**
  Provides complete, working functionality

**Safe to use**
  All methods have defined behavior

Example: Complete Hierarchy
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: cpp

   // Abstract base - defines interface contract
   class Vehicle {
   public:
       virtual ~Vehicle() = default;
       virtual void drive() = 0;
       virtual void stop() = 0;
   };

   // Concrete derived class - implements all pure virtuals
   class RoboTaxi : public Vehicle {
   public:
       ~RoboTaxi() override = default;
       
       void drive() override { 
           /* RoboTaxi-specific driving logic */ 
       }
       
       void stop() override  { 
           /* RoboTaxi-specific stopping logic */ 
       }
   };

   // Usage
   transportation::RoboTaxi robo_taxi{"ROBOT001", 6};  // OK - fully concrete
   robo_taxi.drive();  // OK
   
   // transportation::Vehicle v;  // ERROR - abstract class

Incomplete Implementation
~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: cpp

   // Abstract base
   class Vehicle {
   public:
       virtual ~Vehicle() = default;
       virtual void drive() = 0;
       virtual void stop() = 0;
   };

   // Still abstract - missing stop() implementation
   class Taxi : public Vehicle {
   public:
       ~Taxi() override = default;
       void drive() override { /* Taxi-specific driving logic */ }
       // Missing: void stop() override { }
   };

   // ERROR: cannot instantiate abstract class
   // transportation::Taxi taxi{"TAXI001", 6};

.. warning::

   A derived class has to implement **ALL** pure ``virtual`` methods from the base class to become a concrete class. We forgot to implement ``stop()`` and therefore, ``Taxi`` is also an abstract class.

Design Patterns with Abstraction
---------------------------------

Strategy Pattern
~~~~~~~~~~~~~~~~

.. code-block:: cpp

   // Abstract strategy interface
   class SortStrategy {
   public:
       virtual ~SortStrategy() = default;
       virtual void sort(std::vector<int>& data) = 0;
   };

   // Concrete strategies
   class QuickSort : public SortStrategy {
   public:
       void sort(std::vector<int>& data) override {
           // QuickSort implementation
       }
   };

   class MergeSort : public SortStrategy {
   public:
       void sort(std::vector<int>& data) override {
           // MergeSort implementation
       }
   };

   // Client uses abstraction
   class DataProcessor {
   private:
       std::unique_ptr<SortStrategy> strategy_;
   public:
       void set_strategy(std::unique_ptr<SortStrategy> strategy) {
           strategy_ = std::move(strategy);
       }
       
       void process(std::vector<int>& data) {
           strategy_->sort(data);  // Uses abstract interface
       }
   };

Factory Pattern
~~~~~~~~~~~~~~~

.. code-block:: cpp

   // Abstract product
   class Document {
   public:
       virtual ~Document() = default;
       virtual void open() = 0;
       virtual void save() = 0;
   };

   // Concrete products
   class PDFDocument : public Document {
   public:
       void open() override { /* PDF opening logic */ }
       void save() override { /* PDF saving logic */ }
   };

   class WordDocument : public Document {
   public:
       void open() override { /* Word opening logic */ }
       void save() override { /* Word saving logic */ }
   };

   // Factory creates objects polymorphically
   class DocumentFactory {
   public:
       static std::unique_ptr<Document> create(const std::string& type) {
           if (type == "pdf") {
               return std::make_unique<PDFDocument>();
           } else if (type == "word") {
               return std::make_unique<WordDocument>();
           }
           return nullptr;
       }
   };

Observer Pattern
~~~~~~~~~~~~~~~~

.. code-block:: cpp

   // Abstract observer interface
   class Observer {
   public:
       virtual ~Observer() = default;
       virtual void update(const std::string& event) = 0;
   };

   // Concrete observers
   class EmailNotifier : public Observer {
   public:
       void update(const std::string& event) override {
           send_email("Event occurred: " + event);
       }
   };

   class LoggerObserver : public Observer {
   public:
       void update(const std::string& event) override {
           log_to_file("Event occurred: " + event);
       }
   };

   // Subject maintains list of observers
   class EventManager {
   private:
       std::vector<Observer*> observers_;
   public:
       void attach(Observer* obs) {
           observers_.push_back(obs);
       }
       
       void notify(const std::string& event) {
           for (auto* obs : observers_) {
               obs->update(event);  // Polymorphic call
           }
       }
   };

Best Practices
--------------

1. **Keep interfaces minimal and focused**
   
   .. code-block:: cpp

      // Good - focused interface
      class Drawable {
      public:
          virtual ~Drawable() = default;
          virtual void draw() const = 0;
      };
      
      // Avoid - interface too broad
      class GraphicsObject {
      public:
          virtual void draw() const = 0;
          virtual void rotate(double angle) = 0;
          virtual void scale(double factor) = 0;
          virtual void translate(const Vector& offset) = 0;
          virtual void set_color(const Color& color) = 0;
          // Too many responsibilities!
      };

2. **Use abstract classes for contracts, not implementation sharing**
   
   - If you need shared implementation, consider composition
   - Abstract classes define "what", not "how"

3. **Prefer pure virtual methods over virtual methods with default implementations**
   
   - Forces derived classes to think about implementation
   - Avoids silent bugs from forgotten overrides

4. **Make destructors virtual in abstract classes**
   
   .. code-block:: cpp

      class AbstractBase {
      public:
          virtual ~AbstractBase() = default;  // Essential!
          virtual void do_something() = 0;
      };

5. **Use the Interface Segregation Principle (ISP)**
   
   - Many small, specific interfaces are better than one large interface
   - Clients shouldn't depend on methods they don't use

6. **Document the contract clearly**
   
   .. code-block:: cpp

      class DataSource {
      public:
          virtual ~DataSource() = default;
          
          /**
           * Reads data from the source.
           * 
           * @return Data buffer, or empty on error
           * @throws std::runtime_error if source is not open
           */
          virtual std::vector<uint8_t> read() = 0;
          
          /**
           * Writes data to the source.
           * 
           * @param data Buffer to write
           * @return true on success, false on error
           */
          virtual bool write(const std::vector<uint8_t>& data) = 0;
      };

Common Pitfalls
---------------

Pitfall 1: Too Many Pure Virtuals
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: cpp

   // Avoid - forces too much implementation
   class Vehicle {
   public:
       virtual void start_engine() = 0;
       virtual void stop_engine() = 0;
       virtual void open_door() = 0;
       virtual void close_door() = 0;
       virtual void honk_horn() = 0;
       virtual void turn_lights_on() = 0;
       virtual void turn_lights_off() = 0;
       // ... 50 more methods
   };

**Fix:** Break into smaller, focused interfaces.

Pitfall 2: Abstract Class with Data Members
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: cpp

   // Questionable - mixes interface and implementation
   class Shape {
   private:
       Color color_;  // Implementation detail in abstract class?
   public:
       virtual double area() const = 0;
   };

**Better:** Keep abstract classes focused on interface, use composition for shared data.

Pitfall 3: Forgetting Virtual Destructor
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: cpp

   class Base {
   public:
       // Missing: virtual ~Base() = default;
       virtual void foo() = 0;
   };

**Always** add virtual destructor to abstract base classes.

Key Takeaways
-------------

- **Abstraction** exposes interface, hides implementation
- **Abstract classes** define contracts using pure ``virtual`` methods
- **Pure virtual methods** (``= 0``) must be implemented by derived classes
- **Concrete classes** implement all inherited pure virtuals
- Always provide **virtual destructors** in abstract base classes
- Keep interfaces **minimal and focused**
- Use abstraction for **polymorphic behavior** and **dependency inversion**
- Abstract classes **cannot be instantiated** directly
- Derived classes remain abstract until **all** pure virtuals are implemented