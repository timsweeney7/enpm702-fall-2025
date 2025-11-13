======================
The ``final`` Keyword
======================

**Definition:** ``final`` prevents further derivation or further overriding. Use it to lock a design decision and communicate that a hierarchy is closed.

Purpose and Benefits
--------------------

The ``final`` keyword serves two main purposes:

**Prevent Class Inheritance**
  Ensures a class cannot be used as a base class

**Prevent Method Overriding**
  Ensures a virtual method cannot be overridden in derived classes

**Benefits:**

- **Design clarity:** Explicitly communicates intent
- **Safety:** Prevents unintended inheritance
- **Optimization:** Enables compiler optimizations (devirtualization)
- **API stability:** Locks implementation details
- **Documentation:** Self-documenting code

Prevent Class Inheritance
--------------------------

**Syntax:** Place ``final`` after the class name and base class list.

.. code-block:: cpp

   class RoboTaxi final : public Vehicle {
       // RoboTaxi implementation
   };

   // ERROR: cannot inherit from final class
   // class SuperRoboTaxi : public RoboTaxi {};

When to Use ``final`` Classes
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Use** ``final`` **for classes when:**

- The class is a leaf node in the inheritance hierarchy
- Further specialization would violate the design
- The class manages resources in a way that would break with inheritance
- You want to prevent the fragile base class problem
- Performance is critical (enables devirtualization)

**Example: Value Types**

.. code-block:: cpp

   // String is a complete, self-contained type
   class String final {
   private:
       char* data_;
       size_t size_;
   public:
       String(const char* str);
       ~String();
       // No meaningful way to extend String
   };

**Example: Implementation Details**

.. code-block:: cpp

   // Internal implementation that shouldn't be extended
   class DatabaseConnectionImpl final : public DatabaseConnection {
   private:
       void* native_handle_;
   public:
       void connect() override;
       void disconnect() override;
       // Inheritance would break invariants
   };

Prevent Method Overriding
--------------------------

**Syntax:** Place ``final`` after the method signature, before the method body.

.. code-block:: cpp

   class Vehicle {
   public:
       virtual ~Vehicle() = default;
       virtual void drive() = 0;
       
       // Cannot be overridden in derived classes
       virtual void move() final { 
           /* fixed behavior */ 
       }
   };

   class RoboTaxi : public Vehicle {
   public:
       void drive() override { /* OK */ }
       
       // ERROR: cannot override final method
       // void move() override { }
   };

When to Use ``final`` Methods
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Use** ``final`` **for methods when:**

- The method's implementation must not change in derived classes
- Overriding would violate class invariants
- The method implements a critical algorithm or security check
- The base implementation is performance-critical
- You want to enforce the Template Method pattern

**Example: Security-Critical Methods**

.. code-block:: cpp

   class SecureConnection {
   public:
       virtual ~SecureConnection() = default;
       
       // Security check must not be bypassed
       virtual bool authenticate(const Credentials& creds) final {
           return verify_signature(creds) && check_permissions(creds);
       }
       
       // Derived classes can implement transport
       virtual void send(const Data& data) = 0;
   };

**Example: Template Method Pattern**

.. code-block:: cpp

   class Algorithm {
   public:
       // Template method - fixed algorithm structure
       void execute() final {
           initialize();
           process();
           finalize();
       }
       
   protected:
       // Customization points
       virtual void initialize() = 0;
       virtual void process() = 0;
       virtual void finalize() = 0;
       
       virtual ~Algorithm() = default;
   };

Combining ``final`` and ``override``
------------------------------------

A method can be both ``override`` and ``final``:

.. code-block:: cpp

   class Base {
   public:
       virtual ~Base() = default;
       virtual void foo() = 0;
   };

   class Middle : public Base {
   public:
       // Overrides Base::foo and prevents further overriding
       void foo() override final {
           // Implementation
       }
   };

   class Derived : public Middle {
   public:
       // ERROR: cannot override final method
       // void foo() override { }
   };

.. note::

   This pattern is useful when you want to provide a definitive implementation in a middle class of a hierarchy.

Design Considerations
---------------------

When to Use ``final``
~~~~~~~~~~~~~~~~~~~~~

**Good reasons:**

- **Leaf classes:** The class is a complete implementation with no meaningful extensions
- **Security:** Prevent tampering with security-critical methods
- **Invariants:** Overriding would break class invariants
- **Performance:** Enable devirtualization in hot paths
- **API contract:** Lock implementation details in a stable API

**Example: Complete Implementation**

.. code-block:: cpp

   // No meaningful extensions possible
   class MD5Hash final {
   public:
       std::array<uint8_t, 16> compute(const std::vector<uint8_t>& data);
   };

**Example: Fixed Behavior**

.. code-block:: cpp

   class Transaction {
   public:
       // Must execute in this exact order
       void execute() final {
           begin();
           perform_operation();
           commit();
       }
       
   protected:
       virtual void perform_operation() = 0;
   };

When NOT to Use ``final``
~~~~~~~~~~~~~~~~~~~~~~~~~~

**Avoid** ``final`` **when:**

- The design might evolve and need extension
- You're creating a library that users might want to extend
- There's no clear reason to prevent inheritance
- You're prematurely optimizing

**Example: Premature Finalization**

.. code-block:: cpp

   // Bad - prevents potentially useful extensions
   class Button final : public Widget {
       // What if someone wants RoundedButton or IconButton?
   };

**Better:**

.. code-block:: cpp

   // Allow extension by default
   class Button : public Widget {
       // Derived classes can extend if needed
   };
   
   // Only finalize when there's a clear reason
   class SystemButton final : public Button {
       // OS-specific implementation that shouldn't be extended
   };

Performance Implications
~~~~~~~~~~~~~~~~~~~~~~~~

``final`` can enable compiler optimizations:

**Devirtualization**
  Compiler can replace virtual calls with direct calls

**Inlining**
  Direct calls can be inlined for better performance

**Dead code elimination**
  Unused virtual methods can be removed

.. code-block:: cpp

   class Base {
   public:
       virtual void foo() { /* ... */ }
   };

   class Derived final : public Base {
   public:
       void foo() override { /* ... */ }
   };

   void call_foo(Derived* d) {
       d->foo();  // Can be devirtualized because Derived is final
   }

.. warning::

   Don't use ``final`` solely for performance without profiling. The optimization benefits are often minimal, and premature finalization limits flexibility.

Common Patterns
---------------

Pattern 1: Leaf Classes in a Hierarchy
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: cpp

   class Shape {
   public:
       virtual ~Shape() = default;
       virtual double area() const = 0;
       virtual void draw() const = 0;
   };

   class Polygon : public Shape {
   public:
       virtual std::vector<Point> vertices() const = 0;
   };

   // Final implementation - no need to extend further
   class Triangle final : public Polygon {
   public:
       double area() const override { /* ... */ }
       void draw() const override { /* ... */ }
       std::vector<Point> vertices() const override { /* ... */ }
   };

Pattern 2: Fixed Algorithm with Customization Points
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: cpp

   class DataProcessor {
   public:
       // Fixed processing pipeline
       void process(const Data& input) final {
           if (!validate(input)) return;
           auto transformed = transform(input);
           store(transformed);
       }
       
   protected:
       virtual bool validate(const Data& input) = 0;
       virtual Data transform(const Data& input) = 0;
       virtual void store(const Data& output) = 0;
       
       virtual ~DataProcessor() = default;
   };

Pattern 3: Value-Semantic Types
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: cpp

   // Complete value type - no meaningful inheritance
   class UUID final {
   private:
       std::array<uint8_t, 16> bytes_;
   public:
       UUID();
       explicit UUID(const std::string& str);
       
       std::string to_string() const;
       bool operator==(const UUID& other) const;
       bool operator<(const UUID& other) const;
   };

Pattern 4: Internal Implementation Classes
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: cpp

   // Public interface
   class HttpClient {
   public:
       virtual ~HttpClient() = default;
       virtual Response get(const std::string& url) = 0;
       virtual Response post(const std::string& url, const Data& body) = 0;
   };

   // Internal implementation - shouldn't be extended
   class HttpClientImpl final : public HttpClient {
   private:
       void* curl_handle_;
   public:
       Response get(const std::string& url) override;
       Response post(const std::string& url, const Data& body) override;
   };

Comparison with Other Languages
--------------------------------

**Java:**

.. code-block:: java

   // Java uses 'final' similarly
   public final class String {
       // Cannot be extended
   }
   
   public class Base {
       public final void method() {
           // Cannot be overridden
       }
   }

**C#:**

.. code-block:: csharp

   // C# uses 'sealed' instead of 'final'
   public sealed class String {
       // Cannot be extended
   }

**Python:**

.. code-block:: python

   # Python has no built-in final keyword
   # Uses typing.final decorator (type hint only)
   from typing import final
   
   @final
   class MyClass:
       pass

Best Practices
--------------

1. **Be conservative with** ``final``
   
   - Default to allowing extension
   - Only use ``final`` when there's a clear reason

2. **Use** ``final`` **for leaf classes in closed hierarchies**
   
   .. code-block:: cpp

      // Library provides these concrete implementations
      class PngImage final : public Image { };
      class JpegImage final : public Image { };

3. **Use** ``final`` **methods for fixed algorithms**
   
   .. code-block:: cpp

      class Authenticator {
      public:
          bool authenticate(const User& user) final {
              return check_password(user) && check_permissions(user);
          }
      protected:
          virtual bool check_password(const User& user) = 0;
          virtual bool check_permissions(const User& user) = 0;
      };

4. **Document why something is** ``final``
   
   .. code-block:: cpp

      // final: MD5 is a fixed algorithm; extension would break standard
      class MD5Hasher final {
          // ...
      };

5. **Combine with** ``override`` **appropriately**
   
   .. code-block:: cpp

      class Derived : public Base {
      public:
          void method() override final {
              // Overrides Base::method and prevents further overriding
          }
      };

Common Mistakes
---------------

Mistake 1: Finalizing Too Early
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: cpp

   // Bad - prevents potentially useful extensions
   class Vehicle final {
       // What about RoboTaxi, Taxi, Bus, etc.?
   };

**Fix:** Only finalize leaf nodes, not intermediate abstractions.

Mistake 2: Mixing ``final`` with Pure Virtual
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: cpp

   class Base {
   public:
       // ERROR: final and pure virtual are contradictory
       // virtual void foo() final = 0;
   };

A pure virtual method must be overridden, so it cannot be ``final``.

Mistake 3: Using ``final`` for Optimization Without Profiling
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: cpp

   // Questionable - optimizing before measuring
   class MyClass final {
       // Is this really a hot path?
   };

**Better:** Profile first, optimize with ``final`` only if it matters.

Key Takeaways
-------------

- ``final`` prevents class inheritance or method overriding
- Use for **leaf classes** in closed hierarchies
- Use for **fixed algorithms** that shouldn't change
- Use for **security-critical** methods
- **Don't overuse** - allow extension by default
- Enables compiler optimizations (devirtualization)
- Can combine with ``override``
- Cannot combine with pure virtual (``= 0``)
- Document why something is ``final``
- Profile before using ``final`` for performance