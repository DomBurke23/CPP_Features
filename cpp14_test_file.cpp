/*
 *  Test file created by DXB
 *  01/09/20
 *  This file demonstrates the new features brought in by c++14
 */

#include <string>
#include <iostream> 

/* Deduce return type as 'int' */
auto f(int i){
    return i;
}

constexpr int factorial(int n) {
    /* CPP14 now allows if statements, loops and multiple returns */
    if (n <= 1) {
        return 1;
    }
    else {
        return n * factorial(n - 1);
    }
}

/* CPP14 now allows the auto type-specifier in the parameter list, enabling polymorphic lambdas */
auto identity = [](auto x){ return x; };
int three = identity(3);  // == 3 
std::string foo = identity("foo"); // == "foo" 

/* CPP14 allows variables to be templated */
template<class T> 
constexpr T pi = T(3.1415926535897932385);
template<class T>
T circular_area(T r) { // function template 
    return pi<T> * r * r;  // pi<T> is a variable template instantiation 
}

/* Indicates that a unit (function, class, etc) is discouraged */
void JurassicPeriod();
[[deprecated("Use NeogenePeriod() instead.")]]
void JurassicPeriod(){
std::clog << "Jurassic Period [201.3-152.1] million years ago.\n";
}

//since cpp14 or later:
void func(auto&& t1){}
//since cpp11 or later:
//template <typename T1>
//void func(T1&& t1){}

typedef unsigned int uint32;

int main(void) {
    /* Binary Literals introduced in cpp14 to provide a
    convenient way to prepresent a base-2 number */
    uint32 A = 0b110; // = 6 
    
    factorial(5); // = 120 

    /* Template type parameter deduction with lvalues and rvalues */
    int apple = 0;
    func(0);
    func(apple);
    int& pear = apple;
    func(pear);
    int&& mango = 0;
    func(mango);
    func(std::move(mango));

    return 0;
}