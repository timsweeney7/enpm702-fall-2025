============
Polymorphism
============

**Definition:** Polymorphism (Greek: *poly* = many, *morph* = form) is a core OOP principle. Polymorphism allows objects of different classes to be treated uniformly through a common interface.

C++ supports two types of polymorphism:

- **Compile-time polymorphism** — resolved at compile time
- **Runtime polymorphism** — resolved at runtime

Compile-Time Polymorphism
--------------------------

**Definition:** Compile-time polymorphism (also called *static polymorphism* or *early binding*) is resolved during compilation. The compiler determines which function to call based on the **static type** at compile time.

**Key Characteristics:**

- Resolution happens at compile time
- Based on the declared type of the variable
- No runtime overhead
- Uses function/operator overloading and method redefinition

**Examples:** function overloading, operator overloading, and method redefinition.

.. note::

   The function resolution happens at compile time based on the declared type of the variable, not the actual object it contains.

Method Order Check
~~~~~~~~~~~~~~~~~~

When a method is called on a derived class object:

1. The compiler first checks if the method exists in the derived class
2. If not found, it searches up the inheritance hierarchy through base classes
3. The compiler uses the first matching method it finds

.. code-block:: cpp

   class Base {
   public:
       void test() { 
           std::cout << "Base::test()\n"; 
       }
   };

   class Derived : public Base {
       // No test() method defined
   };

   int main() {
       Derived derived;
       derived.test();  // Calls Base::test()
   }

In the example, ``Base::test()`` is used since we did not provide a version for ``Derived::test()``.

Method Redefinition
~~~~~~~~~~~~~~~~~~~

**Definition:** Method redefinition allows a derived class to provide its own implementation of a base class method when the base class version is too general or needs specialization.

.. code-block:: cpp

   class Base {
   public:
       void test() { 
           std::cout << "Base::test()\n"; 
       }
   };

   class Derived : public Base {
   public:
       void test() {  // Redefines Base::test()
           std::cout << "Derived::test()\n";
       }
   };

   int main() {
       Derived derived;
       derived.test();  // Calls Derived::test()
   }

.. note::

   Method redefinition is compile-time polymorphism because the method selection is based on the static type known at compile time.

Runtime Polymorphism
--------------------

**Definition:** Runtime polymorphism (*dynamic polymorphism* or *late binding*) decides which ``virtual`` method implementation runs based on the *dynamic type* (actual object type) at runtime, not the static type of the pointer/reference.

**Key Requirements:**

1. A ``virtual`` method in a base class
2. A call through a *base* reference or *base* pointer to a *derived* object
3. The actual method called depends on the real object type at runtime

.. important::

   Runtime polymorphism in C++ requires a ``virtual`` method in a base class and a call through a base reference or base pointer to a derived object. The actual method called depends on the real object type at runtime.

The ``virtual`` Keyword
~~~~~~~~~~~~~~~~~~~~~~~

**Definition:** The ``virtual`` keyword tells the compiler to use **dynamic dispatch** for a method. This means:

1. The method call is resolved at **runtime**, not compile time
2. The **actual object type** determines which method runs, not the pointer/reference type
3. The compiler creates a **vtable** (virtual method table) to track which implementation to call

.. code-block:: cpp

   // in class Vehicle (vehicle.hpp)
   class Vehicle {
   public:
       // virtual -> can be overridden in derived classes
       virtual void drive();
       
       // NOT virtual -> cannot be overridden (static binding)
       void update_location(const Location& location);
   };

.. code-block:: cpp

   int main() {
       using transportation::Vehicle;
       using transportation::RoboTaxi;
       
       // Actual object: RoboTaxi
       // Pointer type: Vehicle
       std::unique_ptr<Vehicle> rt = 
           std::make_unique<RoboTaxi>("ROBOTAXI-001", 4);
       
       rt->drive();              // Calls RoboTaxi::drive() - dynamic dispatch
       rt->update_location(loc); // Calls Vehicle::update_location() - static binding
   }

.. warning::

   - Without ``virtual``, C++ uses static binding based on the pointer type, not the actual object!
   - Note that we wrote: ``std::unique_ptr<Vehicle> rt = ...`` and not ``auto rt = ...`` which is equivalent to ``std::unique_ptr<RoboTaxi> rt``. Remember that we want a base class pointer (or reference) to a derived object for polymorphism to work.

The Problem Without Polymorphism
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Challenge:** You must drive different vehicle types uniformly (``RoboTaxi``, ``Taxi``, ...), yet each type performs the task differently.

**Non-Polymorphic Overloads (Not Scalable):**

.. code-block:: cpp

   // Overloads choose at compile time based on the static type
   void run_shift(transportation::RoboTaxi& v) { v.drive(); }
   void run_shift(transportation::Taxi& v)     { v.drive(); }

   int main() {
       transportation::RoboTaxi rt{"ROBOTAXI-001", 4};
       transportation::Taxi     tx{"TAXI-001", 4};
       
       run_shift(rt);  // Calls RoboTaxi version
       run_shift(tx);  // Calls Taxi version
   }

.. warning::

   Overload resolution is a compile-time choice. Each new derived type requires another overload. Bodies tend to duplicate (*violates DRY principle*). Does not support heterogeneous collections.

**Polymorphic Solution (Scalable):**

.. code-block:: cpp

   // Base interface with virtual method
   class Vehicle {
   public:
       virtual ~Vehicle() = default;  // Essential for polymorphic bases
       virtual void drive();          // Virtual (can be overridden)
   };

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
       
       run_shift(*rt);             // Calls RoboTaxi::drive()
       run_shift(std::move(tx));   // Calls Taxi::drive()
   }

.. important::

   Only one ``run_shift()`` is needed. The call *site* uses a base reference or pointer. The *target* method is determined at runtime based on the actual object type (the most-derived override).

When to Use ``auto`` vs. Explicit Base Type
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Question:** When should you use ``auto`` versus an explicit base type?

**Answer:** The choice depends on **where polymorphism needs to happen**.

**Explicit Base Type:**

.. code-block:: cpp

   std::unique_ptr<Vehicle> rt = std::make_unique<RoboTaxi>(...);
   
   // Polymorphic calls directly
   rt->drive();

**Use when:**

- Multiple polymorphic calls needed locally
- Polymorphism happens at point of creation
- Building polymorphic collections

**Using** ``auto``:

.. code-block:: cpp

   auto rt = std::make_unique<RoboTaxi>(...);
   
   // Direct calls to RoboTaxi
   rt->drive();
   
   // Pass to polymorphic function
   run_shift(std::move(rt));

**Use when:**

- Concrete type needed initially
- Polymorphism delegated to function calls
- Need derived-specific methods before passing to functions

The Container Problem with ``auto``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**This WORKS** - function parameter accepts conversion:

.. code-block:: cpp

   auto rt = std::make_unique<RoboTaxi>(...);  // unique_ptr<RoboTaxi>
   run_shift(std::move(rt));  // Converts to unique_ptr<Vehicle> at call

**This FAILS** - container requires exact type match:

.. code-block:: cpp

   auto rt = std::make_unique<RoboTaxi>(...);  // unique_ptr<RoboTaxi>
   std::vector<std::unique_ptr<Vehicle>> fleet;
   
   fleet.push_back(std::move(rt));     // ERROR: Type mismatch!
   fleet.emplace_back(std::move(rt));  // ERROR: Still doesn't work!

.. warning::

   **Why?** Function parameters allow implicit conversions at the call site. Container storage requires **exact type matches**: ``unique_ptr<RoboTaxi>`` ≠ ``unique_ptr<Vehicle>``. This applies to **ALL** containers (``vector``, ``deque``, ``list``, ``set``, ``map``, etc.).

Complete Comparison Table
~~~~~~~~~~~~~~~~~~~~~~~~~~

.. list-table::
   :header-rows: 1
   :widths: 50 25 25

   * - Operation
     - Explicit Base Type
     - Using ``auto``
   * - Pass to function with base parameter
     - ✓
     - ✓
   * - Store in ANY container of base pointers
     - ✓
     - ✗
   * - Use ``push_back``/``emplace_back``/``insert`` with variable
     - ✓
     - ✗
   * - Direct insertion: ``vec.push_back(make_unique<...>())``
     - ✓
     - N/A*
   * - Call derived-specific methods
     - ✗
     - ✓
   * - Polymorphic calls at point of use
     - ✓
     - ✗

*\* No auto variable involved — temporary converts at insertion point*

Why This Happens: Type System Rules
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Function Parameters:**

.. code-block:: cpp

   void run_shift(std::unique_ptr<Vehicle> v);  // Accepts base type
   
   auto rt = std::make_unique<RoboTaxi>(...);   // unique_ptr<RoboTaxi>
   run_shift(std::move(rt));  // ✓ Compiler converts RoboTaxi* → Vehicle*
                              //   Conversion happens at call boundary

**Container Storage:**

.. code-block:: cpp

   std::vector<std::unique_ptr<Vehicle>> fleet;  // Template parameter is FIXED
   
   auto rt = std::make_unique<RoboTaxi>(...);    // unique_ptr<RoboTaxi>
   fleet.push_back(std::move(rt));  // ✗ Template types don't convert!
                                    // unique_ptr<RoboTaxi> ≠ unique_ptr<Vehicle>

.. warning::

   **Key insight:** ``unique_ptr<Derived>`` is NOT a subtype of ``unique_ptr<Base>``, even though ``Derived*`` converts to ``Base*``. Template instantiations don't inherit type relationships!

Solutions for Polymorphic Collections
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Option 1: Direct construction (BEST)**

.. code-block:: cpp

   std::vector<std::unique_ptr<Vehicle>> fleet;
   fleet.push_back(std::make_unique<RoboTaxi>(...));  // ✓ Implicit conversion
   fleet.push_back(std::make_unique<Taxi>(...));      // ✓ Implicit conversion

**Option 2: Use base type from the start**

.. code-block:: cpp

   std::unique_ptr<Vehicle> rt = std::make_unique<RoboTaxi>(...);
   rt->drive();  // Polymorphic call
   fleet.push_back(std::move(rt));  // ✓ Types match exactly

**Option 3: Explicit cast (AVOID - verbose and error-prone)**

.. code-block:: cpp

   auto rt = std::make_unique<RoboTaxi>(...);
   fleet.push_back(std::unique_ptr<Vehicle>(std::move(rt)));  // ✓ But ugly

Decision Framework
~~~~~~~~~~~~~~~~~~

1. **Need to store in a base-type container?**
   
   → Use **explicit base type** OR **direct insertion**

2. **Need polymorphic calls at point of use?**
   
   → Use **explicit base type**

3. **Need derived-specific methods before passing to functions?**
   
   → Use **auto**, then pass to functions

4. **Only passing to functions, no container storage?**
   
   → Either works; **auto** is more flexible

.. important::

   **Rule of thumb:** If you're building polymorphic collections, use explicit base type or direct insertion. If you're only calling functions, ``auto`` is fine.

The ``override`` Keyword
~~~~~~~~~~~~~~~~~~~~~~~~

**Definition:** The ``override`` keyword is a **safety feature** that tells the compiler "I intend this method to override a base class virtual method".

**Benefits:**

- **Catches typos:** If signatures don't match, compilation fails
- **Documents intent:** Makes it clear this overrides a base method
- **Prevents accidental hiding:** Detects when you think you're overriding but aren't

.. code-block:: cpp

   class Vehicle {
   public:
       virtual void drive();
   };

   class RoboTaxi : public Vehicle {
   public:
       void drive() override;        // OK - matches base signature
       // void drive(int) override;  // ERROR - no matching virtual in base
       // void driev() override;     // ERROR - typo caught!
   };

.. important::

   Always use ``override`` when overriding virtual methods. It's free safety!

Avoid Slicing & Embrace Polymorphic Collections
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: cpp

   std::vector<std::unique_ptr<transportation::Vehicle>> fleet;
   fleet.emplace_back(std::make_unique<transportation::RoboTaxi>("ROBOTAXI-001", 4));
   fleet.emplace_back(std::make_unique<transportation::Taxi>("TAXI-001", 4));

   for (auto& v : fleet) {
       v->drive();   // Runtime dispatch for each element's actual type
   }

.. warning::

   Do not store derived objects by value in a ``std::vector<Vehicle>``. This causes *object slicing* where derived class data is lost and polymorphism doesn't work. Use owning pointers (``unique_ptr``, ``shared_ptr``), or non-owning pointers/references with external lifetime management.

Requirements for Runtime Polymorphism
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. **Inheritance relationship** ✓
   
   - Derived classes inherit from a common base (``Vehicle``)

2. **Base handle to derived object** ✓
   
   - Use ``Vehicle&``, ``Vehicle*``, ``std::unique_ptr<Vehicle>``, or ``std::shared_ptr<Vehicle>``

3. **``virtual`` method in the base** ✓
   
   - Mark the interface ``virtual``; override it in derived classes

.. note::

   The call target depends on the **dynamic type** of the object (what it actually is at runtime), not the **static type** of the handle (how the pointer/reference was declared). This is *late binding*.

Key Takeaways
-------------

- **Compile-time polymorphism:** Function/operator overloading, method redefinition
- **Runtime polymorphism:** Virtual methods with dynamic dispatch
- Use ``virtual`` in base classes for methods that derived classes will override
- Always use ``override`` in derived classes for safety
- Prefer explicit base type when building polymorphic collections
- Use ``auto`` when you need concrete type initially, then pass to functions
- Remember: ``unique_ptr<Derived>`` ≠ ``unique_ptr<Base>`` for containers
- Direct insertion works best for polymorphic collections