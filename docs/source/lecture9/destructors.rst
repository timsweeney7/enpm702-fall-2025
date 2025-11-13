===========
Destructors
===========

**Definition:** A destructor is a special member function that cleans up an object's resources when it goes out of scope or is explicitly deleted. The destructor is automatically called: you don't invoke it manually.

Key Characteristics
-------------------

**Naming**
  ``~ClassName()`` (e.g., ``~Vehicle()``)

**No parameters, no return type**
  Unlike constructors, destructors take no arguments and return nothing

**One per class**
  Cannot be overloaded

**Automatic invocation**
  Called at scope exit or ``delete``

What Does a Destructor Do?
---------------------------

A destructor performs **cleanup operations** before an object is destroyed:

- **Release dynamically allocated memory** (``delete``, ``delete[]``)
- **Close file handles, network connections, database connections**
- **Release mutexes or other synchronization primitives**
- **Decrement reference counts** in shared ownership schemes
- **Any other resource cleanup** needed for proper RAII

**Example:**

.. code-block:: cpp

   class FileHandler {
   private:
       FILE* file_;
   public:
       FileHandler(const char* filename) : file_(fopen(filename, "r")) {}
       
       ~FileHandler() {  // Destructor ensures file is closed
           if (file_) {
               fclose(file_);
           }
       }
   };
   // file_ is automatically closed when FileHandler goes out of scope

Destructor Execution Order
---------------------------

Destructors are called in the **reverse order** of constructor calls:

.. code-block:: cpp

   class Base {
   public:
       Base() { std::cout << "Base constructor\n"; }
       ~Base() { std::cout << "Base destructor\n"; }
   };

   class Derived : public Base {
   public:
       Derived() { std::cout << "Derived constructor\n"; }
       ~Derived() { std::cout << "Derived destructor\n"; }
   };

   int main() {
       Derived d;
   }
   // Output:
   // Base constructor
   // Derived constructor
   // Derived destructor    <- Reversed order
   // Base destructor       <- Reversed order

This ensures that:

1. Derived class resources are cleaned up first
2. Base class resources are cleaned up last
3. No dangling references during destruction

``virtual`` Destructors and Inheritance
----------------------------------------

.. warning::

   **Critical:** When deleting through a base pointer, a ``virtual`` destructor ensures the derived class destructor runs first. Without it, only the base destructor runs, causing **resource leaks** and **undefined behavior**.

The Problem
~~~~~~~~~~~

.. code-block:: cpp

   class Base {
   public:
       ~Base() { std::cout << "~Base()\n"; }  // NOT virtual!
   };

   class Derived : public Base {
   private:
       int* data_;
   public:
       Derived() : data_(new int[1000]) {}
       
       ~Derived() { 
           delete[] data_; 
           std::cout << "~Derived()\n"; 
       }
   };

   Base* ptr = new Derived();
   delete ptr;  // UNDEFINED BEHAVIOR!
                // Only ~Base() called, not ~Derived()
                // Leaks memory from data_!

.. warning::

   Without ``virtual``, the destructor is selected at compile time based on the pointer type (``Base*``), not the actual object type (``Derived``). The derived destructor never runs!

The Solution
~~~~~~~~~~~~

.. code-block:: cpp

   class Base {
   public:
       virtual ~Base() { std::cout << "~Base()\n"; }  // Virtual!
   };

   class Derived : public Base {
   private:
       int* data_;
   public:
       Derived() : data_(new int[1000]) {}
       
       ~Derived() override { 
           delete[] data_; 
           std::cout << "~Derived()\n"; 
       }
   };

   Base* ptr = new Derived();
   delete ptr;  // Correct behavior
                // Calls ~Derived() first, then ~Base()
                // No memory leak!

   // Output:
   // ~Derived()
   // ~Base()

.. important::

   **Rule:** Any class intended to be a polymorphic base class **must** have a virtual destructor.

When to Use Virtual Destructors
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Always use virtual destructors when:**

- The class has any virtual methods
- The class is designed to be inherited from
- Objects may be deleted through base class pointers
- The class is part of a polymorphic hierarchy

**Don't need virtual destructors when:**

- The class is final (cannot be inherited)
- The class is never used polymorphically
- No derived class instances will be deleted through base pointers

The ``= default`` Keyword
--------------------------

**Definition:** The ``= default`` keyword requests the compiler generate the default implementation of a special member function (constructor, destructor, copy/move operations).

Why Use It?
~~~~~~~~~~~

- **Explicit intent:** Shows you deliberately want the default behavior
- **Enables special rules:** Compiler-generated functions can be trivial/constexpr
- **Rule of Zero compliance:** Don't write what the compiler can generate
- **Better optimization:** Compiler-generated code is often optimal

**Example:**

.. code-block:: cpp

   class Vehicle {
   public:
       virtual ~Vehicle() = default;         // Compiler generates virtual destructor body
       Vehicle() = default;                  // Compiler generates default constructor
       Vehicle(const Vehicle&) = default;    // Compiler generates copy constructor
   };

.. note::

   ``= default`` is particularly important for ``virtual`` destructors in abstract base classes where you don't need custom cleanup logic but must ensure the destructor is ``virtual``.

When to Use ``= default``
~~~~~~~~~~~~~~~~~~~~~~~~~~

**Use** ``= default`` **for destructors when:**

- You need a virtual destructor but have no cleanup logic
- You're following the Rule of Zero
- You want to explicitly document that default behavior is intended

**Write a custom destructor when:**

- You need to release manually managed resources
- You need to close file handles or network connections
- You need to perform logging or other side effects
- You're managing RAII wrappers

Common Patterns
---------------

Pattern 1: Abstract Base with Virtual Destructor
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: cpp

   class Shape {
   public:
       virtual ~Shape() = default;           // Virtual destructor
       virtual double area() const = 0;      // Pure virtual
       virtual void draw() const = 0;        // Pure virtual
   };

   class Circle : public Shape {
   private:
       double radius_;
   public:
       ~Circle() override = default;         // No cleanup needed
       double area() const override { return 3.14159 * radius_ * radius_; }
       void draw() const override { /* drawing code */ }
   };

Pattern 2: RAII Class with Custom Destructor
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: cpp

   class DatabaseConnection {
   private:
       void* connection_;  // Opaque handle
   public:
       DatabaseConnection(const char* host) {
           connection_ = connect_to_database(host);
       }
       
       ~DatabaseConnection() {
           if (connection_) {
               close_connection(connection_);
               connection_ = nullptr;
           }
       }
       
       // Delete copy operations (connection is unique)
       DatabaseConnection(const DatabaseConnection&) = delete;
       DatabaseConnection& operator=(const DatabaseConnection&) = delete;
   };

Pattern 3: Inheritance with Resource Management
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: cpp

   class Vehicle {
   public:
       virtual ~Vehicle() = default;  // Virtual for polymorphism
       virtual void drive() = 0;
   };

   class RoboTaxi : public Vehicle {
   private:
       std::unique_ptr<SensorArray> sensors_;  // RAII wrapper
       std::unique_ptr<NavigationSystem> nav_; // RAII wrapper
   public:
       // Compiler-generated destructor automatically cleans up unique_ptrs
       ~RoboTaxi() override = default;
       
       void drive() override { /* ... */ }
   };

Common Pitfalls
---------------

Pitfall 1: Forgetting Virtual Destructor
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: cpp

   class Base {
   public:
       virtual void foo() = 0;
       // Missing: virtual ~Base() = default;
   };

   std::unique_ptr<Base> ptr = std::make_unique<Derived>();
   // When ptr goes out of scope: UNDEFINED BEHAVIOR!

**Fix:** Always add virtual destructor to polymorphic bases.

Pitfall 2: Calling Virtual Functions in Destructors
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: cpp

   class Base {
   public:
       virtual ~Base() {
           cleanup();  // Does NOT use derived version!
       }
       virtual void cleanup() { /* base cleanup */ }
   };

   class Derived : public Base {
   public:
       ~Derived() override { /* ... */ }
       void cleanup() override { /* derived cleanup */ }
   };

.. warning::

   Virtual dispatch does NOT work in constructors or destructors. Only the current class's version is called.

Pitfall 3: Exception Safety
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: cpp

   class Resource {
   public:
       ~Resource() {
           // Never throw from destructors!
           // If this throws, std::terminate is called
           cleanup();  
       }
   };

.. important::

   Destructors should be ``noexcept`` (they are by default). Never let exceptions escape from destructors.

Best Practices
--------------

1. **Always make base class destructors virtual**
   
   .. code-block:: cpp

      class Base {
      public:
          virtual ~Base() = default;
      };

2. **Use** ``= default`` **when no custom cleanup is needed**
   
   .. code-block:: cpp

      class Widget {
      public:
          virtual ~Widget() = default;
      };

3. **Follow the Rule of Zero**
   
   - Let compiler generate destructors when possible
   - Use RAII wrappers (``unique_ptr``, ``shared_ptr``, ``vector``, etc.)
   - Only write custom destructors when managing raw resources

4. **Mark overridden destructors with** ``override``
   
   .. code-block:: cpp

      class Derived : public Base {
      public:
          ~Derived() override = default;
      };

5. **Never throw from destructors**
   
   - Destructors are implicitly ``noexcept``
   - Throwing from destructor calls ``std::terminate``

6. **Clean up in reverse order of construction**
   
   - Compiler does this automatically
   - Ensures no dangling references

Key Takeaways
-------------

- Destructors clean up resources automatically when objects are destroyed
- Use ``virtual`` destructors in polymorphic base classes
- Use ``= default`` for virtual destructors when no cleanup is needed
- Never throw exceptions from destructors
- Follow the Rule of Zero: prefer RAII wrappers over manual resource management
- Always use ``override`` when overriding virtual destructors
- Virtual dispatch doesn't work in constructors/destructors