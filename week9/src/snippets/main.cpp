#include <iostream>

// //====</1>====//
// class Base
// {
// public:
//     Base(int base_value = 50) : base_member_{base_value}
//     {
//         /*empty body*/
//     }

// protected:
//     int base_member_;
// }; // class Base

// class Derived : public Base
// {
// public:
//     Derived(double derived_value)
//         : derived_member_{derived_value}
//     {
//         /*empty body*/
//     }

// private:
//     double derived_member_;
// }; // class Derived

// int main()
// {
//     Derived derived(20.5);
// }

// //====</5>====//

class Base
{
public:
    Base(int base_value = 50) : base_member_{base_value} {}
    void test() { std::cout << "Base::test()\n"; }

protected:
    int base_member_;
}; // class Base

class Derived : public Base
{
public:
    Derived(double derived_value, int base_value)
        : Base(base_value), derived_member_{derived_value}
    {
    }
    // void test() { std::cout << "Derived::test()\n"; }

private:
    double derived_member_;
}; // class Derived

int main()
{
    Derived derived(20.5, 10);
    derived.test(); // Base::test() called
}