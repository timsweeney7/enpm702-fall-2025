====================
Class Relationships
====================

Class relationships describe how classes interact and depend on each other. They represent real-world connections between objects and define the structure of your program. They are how you model the real world and, more importantly, how you create code that is reusable, maintainable, and flexible.

   
Association
-----------

**Definition:** Association is a loose relationship where objects exist independently. One object uses or interacts with another, but neither owns the other. If one object is destroyed, the other can continue existing.

**Key Characteristics:**

- Objects exist independently
- Neither object owns the other
- Relationship is typically "uses-a"
- Both objects can survive independently

**Example:** A Teacher and a Student have an association. If the teacher leaves, students still exist. If a student graduates, the teacher remains.

UML Representation
~~~~~~~~~~~~~~~~~~

In UML diagrams, association is shown with a simple line connecting two classes. Multiplicity can be indicated at each end:

**Multiplicity Notations:**

- ``n`` = exactly n
- ``0..1`` = zero or one
- ``*`` or ``0..*`` = zero or more
- ``1..*`` = one or more

Aggregation
-----------

**Definition:** Aggregation is a type of association and represents a "has-a" relationship where the container has a weak ownership of the contained objects. The contained objects can exist independently of the container. When the container is destroyed, the contained objects continue to exist.

**Key Characteristics:**

- Represents a "has-a" relationship
- Weak ownership (hollow diamond in UML)
- Contained objects can exist independently
- Container destruction doesn't destroy contained objects

**Example:** A Fleet "contains" Vehicles. If the fleet is dissolved, the vehicles still exist and can be transferred to another fleet or operate independently.

**Code Example:**

.. code-block:: cpp

   class Vehicle {
   private:
       std::string id_;
   public:
       Vehicle(const std::string& id) : id_{id} {}
       // Vehicle can exist independently
   };

   class Fleet {
   private:
       std::vector<Vehicle*> vehicles_;  // Non-owning pointers
   public:
       void add_vehicle(Vehicle* v) {
           vehicles_.push_back(v);
       }
       // Vehicles are NOT destroyed when Fleet is destroyed
   };

Composition
-----------

**Definition:** Composition is a strong "has-a" relationship with exclusive ownership. The contained object is an integral part of the container and cannot exist independently. When the container is destroyed, all its parts are destroyed as well.

**Key Characteristics:**

- Strong ownership (filled diamond in UML)
- Contained objects cannot exist independently
- Container destruction destroys all parts
- Represents "part-of" relationship

**Example:** A Vehicle has Sensors. The sensors are integral parts of the vehicle. If the vehicle is destroyed (scrapped), its sensors are destroyed with it.

**Code Example:**

.. code-block:: cpp

   class Sensor {
   private:
       std::string type_;
       double reading_{0.0};
   public:
       Sensor(const std::string& type) : type_{type} {}
   };

   class Vehicle {
   private:
       std::vector<Sensor> sensors_;  // Owns sensors by value
   public:
       Vehicle() {
           sensors_.emplace_back("lidar");
           sensors_.emplace_back("radar");
       }
       // Sensors are automatically destroyed with Vehicle
   };

Inheritance
-----------------------------

**Definition:** Inheritance represents an "is-a" relationship where a derived class inherits attributes and behaviors from a base class. The derived class specializes or extends the base class, providing specific implementations while maintaining the common interface.

**Key Characteristics:**

- Represents an "is-a" relationship
- Derived class inherits from base class
- Enables code reuse and polymorphism
- Supports specialization and extension

**Example:** RoboTaxi "is-a" Vehicle. Taxi "is-a" Vehicle. Both inherit common vehicle behavior but add their own specific features.

Types of Inheritance
~~~~~~~~~~~~~~~~~~~~

**Single Inheritance**

A class inherits from exactly one base class.

.. code-block:: cpp

   class Animal {
   protected:
       std::string name_;
       int age_;
   public:
       Animal(const std::string& name, int age) 
           : name_{name}, age_{age} {}
   };

   class Bird : public Animal {
   private:
       double wingspan_;
   public:
       Bird(const std::string& name, int age, double wingspan)
           : Animal(name, age), wingspan_{wingspan} {}
   };

   class Elephant : public Animal {
   private:
       double trunk_length_;
   public:
       Elephant(const std::string& name, int age, double trunk_length)
           : Animal(name, age), trunk_length_{trunk_length} {}
   };

.. note::

   - ``Bird`` and ``Elephant`` inherit ``Animal``'s ``public`` and ``protected`` members
   - UML diagrams typically don't show inherited members

**Multiple Inheritance**

Multiple inheritance occurs when a class inherits from more than one base class. The derived class gains access to all ``public`` and ``protected`` members from all parent classes.

.. code-block:: cpp

   class Animal {
   protected:
       std::string species_;
   public:
       Animal(const std::string& species) : species_{species} {}
   };

   class Human {
   protected:
       std::string language_;
   public:
       Human(const std::string& language) : language_{language} {}
   };

   class MythicalCreature : public Animal, public Human {
   public:
       MythicalCreature(const std::string& species, 
                       const std::string& language)
           : Animal(species), Human(language) {}
   };

.. important::

   We focus exclusively on **single inheritance** in this course. For assignments and projects, you are welcome to use any inheritance approach.

Generalization and Specialization
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Generalization**

Bottom-up approach which should be used every time classes have specific differences and common similarities, so that the similarities can be grouped in a superclass and the differences maintained in subclasses.

**Process:**

1. Identify common attributes and methods across multiple classes
2. Extract commonalities into a base class
3. Keep differences in specialized subclasses

**Specialization**

Top-down approach which creates new classes from an existing class. If certain properties only apply to some of the classes, subclasses can be created for these specific properties.

**Process:**

1. Start with a general base class
2. Create derived classes for specific variants
3. Add specialized attributes and methods to derived classes

UML Representation
~~~~~~~~~~~~~~~~~~

The ``protected`` specifier is denoted with a ``#`` symbol in UML diagrams.

.. code-block:: text

   +--------------------+
   | Base               |
   +--------------------+
   # base_member_: int  |  <- # indicates protected
   +--------------------+
   | +base_method()     |
   +--------------------+
            ▲
            |
            |
   +--------------------+
   | Derived            |
   +--------------------+
   | -derived_member_   |
   +--------------------+
   | +derived_method()  |
   +--------------------+

Inheritance Access Types
~~~~~~~~~~~~~~~~~~~~~~~~~

The access specifier used during inheritance determines how base class members are accessible in the derived class:

.. list-table::
   :header-rows: 1
   :widths: 25 25 25 25

   * - Base Class Member
     - ``public`` inheritance
     - ``protected`` inheritance
     - ``private`` inheritance
   * - ``public``
     - ``public``
     - ``protected``
     - ``private``
   * - ``protected``
     - ``protected``
     - ``protected``
     - ``private``
   * - ``private``
     - not accessible (hidden)
     - not accessible (hidden)
     - not accessible (hidden)

.. note::

   - ``private`` members are inherited but hidden from derived classes
   - Default inheritance in C++ is ``private``
   - Always explicitly specify ``public`` inheritance for is-a relationships

**Best Practice Example:**

.. code-block:: cpp

   class Base {
   public:
       void public_method();
   protected:
       void protected_method();
   private:
       void private_method();
   };

   // Use public inheritance for is-a relationships
   class Derived : public Base {
       // public_method() is public
       // protected_method() is protected
       // private_method() is not accessible
   };

Constructors in Inheritance
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. warning::

   The constructors of a class must address the attributes specific to that class.

**Problem:** How do we initialize base class attributes when constructing a derived object?

**Wrong Approach #1:** Initialize base class members in derived class initializer list

.. code-block:: cpp

   class Base {
   protected:
       int base_member_;
   public:
       Base(int base_value = 50) : base_member_{base_value} {}
   };

   class Derived : public Base {
   private:
       double derived_member_;
   public:
       // ERROR: Cannot initialize inherited members
       Derived(double derived_value, int base_value)
           : derived_member_{derived_value}, base_member_{base_value} {}
   };

**Wrong Approach #2:** Assign base class members in constructor body

.. code-block:: cpp

   class Derived : public Base {
   private:
       double derived_member_;
   public:
       Derived(double derived_value, int base_value)
           : derived_member_{derived_value} { 
           base_member_ = base_value;  // Works, but not ideal
       }
   };

.. warning::

   This approach works but is performed in two steps and will not work if the attribute is a ``const`` or a reference.

**Correct Approach:** Explicitly call the base class constructor

.. code-block:: cpp

   class Base {
   protected:
       int base_member_;
   public:
       Base(int base_value = 50) : base_member_{base_value} {}
   };

   class Derived : public Base {
   private:
       double derived_member_;
   public:
       Derived(double derived_value, int base_value)
           : Base(base_value),  // Call base constructor FIRST
             derived_member_{derived_value} { 
           // Empty body
       }
   };

.. code-block:: cpp

   int main() {
       Derived derived(20.5, 10);
       // Execution order:
       // 1. Base(10) is called -> base_member_ = 10
       // 2. Derived(20.5, 10) is called -> derived_member_ = 20.5
       // 3. Control returns to main()
   }

.. important::

   **Best Practice:**
   
   - Add parameters for base class attributes in the derived class constructor
   - Explicitly call the base class constructor in the member initializer list
   - Each constructor worries only about its own attributes

Key Takeaways
-------------

- **Association:** "uses-a" - independent objects that interact
- **Aggregation:** "has-a" - weak ownership, parts can survive independently
- **Composition:** "has-a" - strong ownership, parts destroyed with whole
- **Inheritance:** "is-a" - derived class extends base class
- Always use ``public`` inheritance for is-a relationships
- Call base class constructors explicitly in derived class initializer lists
- Focus on single inheritance for clarity and maintainability