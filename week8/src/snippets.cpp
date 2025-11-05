/**
 * @file snippets.cpp
 * @author zeidk (zeidk@umd.edu)
 * @brief A collection of small, isolated code snippets used to demonstrate
 * various C++ and OOP concepts.
 * @version 0.1
 * @date 2025-11-04
 * * @copyright Copyright (c) 2025
 * */

#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include <chrono>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

// default main so CMake builds
int main(){}

// //====</1>====//
// // Function that takes const std::string&
// void process_string(const std::string &str) {
//     // Simple work to prevent optimization
//     if (!str.empty()) {
//         std::cout << ""; // Minimal work
//     }
// }

// // Function that takes std::string_view
// void process_string_view(std::string_view str) {
//     // Same simple work
//     if (!str.empty()) {
//         std::cout << ""; // Minimal work
//     }
// }

// int main() {
//     constexpr int iterations{1'000'000};
//     auto test_string{"This is a test string for performance comparison"};

//     std::cout << "Testing " << iterations << " iterations\n";

//     // Test const std::string&
//     auto start{std::chrono::high_resolution_clock::now()};
//     for (int i{0}; i < iterations; ++i) {
//         process_string(test_string); // Creates temporary std::string
//     }
//     auto end{std::chrono::high_resolution_clock::now()};
//     auto time1{
//         std::chrono::duration_cast<std::chrono::microseconds>(end - start)
//             .count()};

//     // Test std::string_view
//     start = std::chrono::high_resolution_clock::now();
//     for (int i{0}; i < iterations; ++i) {
//         process_string_view(test_string); // No temporary
//     }
//     end = std::chrono::high_resolution_clock::now();
//     auto time2{
//         std::chrono::duration_cast<std::chrono::microseconds>(end - start)
//             .count()};

//     // Results
//     std::cout << "const std::string&: " << time1 << " μs\n";
//     std::cout << "std::string_view:   " << time2 << " μs\n";
//     std::cout << "Speedup: " << static_cast<double>(time1) / time2 << "x\n";
// }

// //====</2>====//
// int find_index(const std::vector<int> &numbers, int target) {
//     // TODO: Write logic
// }

// int main() {
//     std::vector<int> numbers{10, 20, 30, 40, 30};
//     auto result{find_index(numbers, 30)};
//     // if (result) {
//     //     std::cout << "Index: " << *result << '\n';
//     //     std::cout << "Index: " << result.value() << '\n';
//     // }
//     // std::cout << "Index: " << result.value_or(-1) << '\n';
// }

// //====</5>====//
// class String {
//   public:
//     String() { std::cout << "String default ctor\n"; }
//     String(const char *s) : data_{s} { std::cout << "String param ctor\n"; }

//   private:
//     std::string data_;
// };

// class A {
//   public:
//     A() {
//         std::cout << "A constructor\n";
//         name_ = String("Default");
//     }

//   private:
//     String name_;
// };

// int main() { A a; }

// //====</6>====//
// class A {
//   public:
//     A(int x, int &y) {
//         c_ = x;  // Wrong
//         r_ = y; // Wrong
//     }

//   private:
//     const int c_;
//     int &r_;
// };

// int main() {
//     int some_value{43};
//     A a(10, some_value);
// }

// //====</7>====//
// class Rectangle {
//   private:
//     double area_;   // 1. initialized first
//     double width_;  // 2. initialized second
//     double height_; // 3. initialized third
//   public:
//     Rectangle(double w, double h)
//         : width_{w}, height_{h}, area_{width_ * height_} {
//         // area_ is computed using uninitialized width_ and height_
//     }
// };

// int main() { Rectangle(4, 10); }

// //====</8>====//
// class Point {
//   private:
//     double x_;
//     double y_;

//   public:
//     Point(double x, double y) : x_{x}, y_{y} { /*body*/ }

//     void move(double dx, double dy) {
//         this->x_ += dx; // same as x_ += dx;
//         this->y_ += dy; // same as y_ += dy;
//     }

//     void print() const {
//         std::cout << "(" << this->x_ << ", " << this->y_ << ")\n";
//     }
// };

// int main() {
//     Point point(3, 4);
//     point.move(2, 2);
//     point.print();
// }

// //====</9>====//
// class Counter {
//   private:
//     int value_;

//   public:
//     Counter(int v = 0) : value_{v} {}

//     Counter &increment() {
//         ++value_;
//         return *this; // allows chaining
//     }

//     void print() const { std::cout << "Value: " << value_ << '\n'; }
// };

// int main() {
//     Counter c;
//     c.increment().increment().increment().print();
// }

// //====</10>====//
// class Vehicle {
//   private:
//     inline static int vehicle_count_{0}; // C++17 and later
//     std::string model_;

//   public:
//     Vehicle(const std::string &model) : model_{model} { vehicle_count_++; };

//     [[nodiscard]] static int get_vehicle_count() noexcept {
//         return vehicle_count_;
//     };
// };

// int main() {
//     std::cout << Vehicle::get_vehicle_count() << '\n'; // 0
//     Vehicle vehicle("Sedan");
//     std::cout << vehicle.get_vehicle_count() << '\n'; // 1
// }
