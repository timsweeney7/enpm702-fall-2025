
#include <iostream>

#include "vehicle.hpp"

// //====</4>====//
// class A {
//  public:
//   A() {
//     std::cout << "A constructor\n";
//     name_ = "Default";  // Assignment
//   }

//  private:
//   std::string name_;  // Constructed first
// };

// int main() {
//     A a;
// }

// //====</5>====//
// class String {
//  public:
//   String() {
//     std::cout << "String default ctor\n";
//   }
//   String(const char* s) : data_{s} {
//     std::cout << "String param ctor\n";
//   }
//  private:
//   std::string data_;
// };

// class A {
//  public:
//   A() {
//     std::cout << "A constructor\n";
//     name_ = String("Default");
//   }
//  private:
//   String name_;
// };

// int main() {
//     A a;
// }

// //====</6>====//
// class A {
//  public:
//   A(int constant, int& reference) {
//     c_ = constant;  // x Wrong
//     r_ = reference;   // x Wrong
//   }

//  private:
//   const int c_;
//   int &r_;

// };  // class A

// int main(){
//     int some_value{67};
//     A a(10, some_value);
// }

// //====</7>====//
// class Rectangle {
//     private:
//     double area_;      // 1. initialized first
//     double width_;     // 2. initialized second
//     double height_;    // 3. initialized third
// public:
//     Rectangle(double w, double h)
//         : width_{w}, height_{h}, area_{width_ * height_} {
//         // area_ is computed using uninitialized width_ and height_
//     }
// };

// int main(){
//     Rectangle(4,10);
// }

// int main() {
//   const transportation::Vehicle camry("White", "Camry", 113);
//   camry.print_status();
// }
int main(){}