/*
*  Test file created by DXB
*  01/09/20
*  This file demonstrates the new features brought in by c++11
*/

#include <iostream>
#include <array>
#include <vector>
#include <numeric> 
using namespace std; 

/* Inline namespace members treated as if they were part of its 
   parents namespace. */
namespace ChocolateFactory {
    namespace MakeChocolate{
        int getStatus() { return 1; }
        bool isChocolateMade() { return true; }
    }
    inline namespace SellChocolate {
        int getStatus() { return 2; } 
    }
}
int shop{ ChocolateFactory::getStatus() };
int oldShop{ ChocolateFactory::MakeChocolate::getStatus() };
//bool firstShop { ChocolateFactory::isChocolateMade()}; 

/* Non-static data member initialisers now allowed */
class Size {
    //Size():pieces{5}{}  // Needed prior CPP11, now not
private:
    unsigned pieces{ 5 };
};

struct C11 { 
  C11() {} 
  C11( const C11&) = delete; 
  int* m_intPtr = nullptr; 
}; 

/* Converting constructors will convert values of braced list syntax into
   constructor arguments. Braced list synatx does not allow narrowing. If 
   a constructor accepts a std::initializer_list it will be called instead */
struct chocolate {
    chocolate(int){}
    chocolate(int, int){}
    chocolate(int, int, int){}
    chocolate(std::initializer_list<int>){}
};
chocolate galaxy{ 0, 0 };
chocolate dairy_milk(0, 0);
chocolate magic_stars = { 0, 0 };
chocolate snickers{ 0, 0, 0 };
chocolate wispa(1.1); // warning message implicit conversion 
//chocolate twix {1.1};  // error narrowing converesion double to int 

/* Virtual function overrides another virtual function 
   add the keyword final after Cadbury or crunchie() to 
   specify a virtual function cannot be overridden in a 
   derived class or that a class cannot be inherited from. */
struct Cadbury {
//struct Cadbury final {
    virtual void crunchie();
    //virtual void crunchie() final;
    void twirl();
};
struct Hereos : Cadbury {
    void crunchie() override; //correct Hereos::crunchie overrides Cadbury::crunchie
    //void twirl() override; // error Cadbury::twirl is not virtual 
    //void fudge() override;  // error 
};

/* Conversion functions can now be made explicit using the explicit specifier */
struct not_Packaged {
    operator bool() const { return true; }
};
struct yes_Packaged {
    explicit operator bool() const { return true;  }
};

/* Type safe and strongly typed enums */
enum class Colour : unsigned int {
    Red = 0xFF0000,
    Green = 0xFF00,
    Blue = 0xFF
};

enum class Alert : bool {
    Red,
    Green
};

Colour c = Colour::Red; 

/* CPP11 allows you to declare object without specifying their types */
auto amountSold = 76;

/* Lambda expressions have been introduced in CPP11 */
void bar () {
  auto Ingredients = [] {
      cout << "Ingredients include: \n"; 
  };
  Ingredients(); 
}

/* Nullptr designed to replace C's NULL macro */
void food(int);
void food(char*);
void food(char*) {} 

/* using is similar to typedef but easier to read and are compatible
   with templates */
template <typename T>
using Vec = std::vector<T>;
Vec<int> v; 
using String = std::string;
String moto { "Have a lovely day \n" };

//since cpp14 or later:
//void func(auto&& t1){}
//since cpp11 or later:
template <typename T1>
void func(T1&& t1){}

/* The ... syntax creates a parameter pack or expands one. Also able to create
an initialiser list from a parameter pack in order to iterate over variadic
function arguments. */
template <typename First, typename... Args>
auto sum(const First first, const Args... args) -> decltype(first){
    const auto values = { first, args... };
    return std::accumulate(values.begin(), values.end(), First{ 0 });
}

int main ( void ){
  bar(); 
  //food(NULL); // Error - ambiguous 
  food(nullptr); // calls food(char*)
  cout << moto;

  /* constexpr values are those that the compiler can evaluate at compile-time */
  constexpr int salary = 123;
  
  /* Rvalue references introduced */
  int shopEmployees = 0; 
  int& factoryEmployees = shopEmployees; 
  int&& deliveryEmployees = 0; 

  /* Forward referencing introduced */
  int shopManager = 0; 
  auto&& factoryManager = shopManager; 
  auto&& deliveryManager = 0; 
  
  /* decltype takes an expression and returns its type */
  double averageShift = 5.5;
  decltype(averageShift) pay = salary;       // type = double

  /* Static assertions that are evaluated at compile time, If constant expression
     is compared to equal to zero then throw error. */
  constexpr int staffRequired = 0; 
  constexpr int chocolateDistributionStations = 1; 
  static_assert(staffRequired != chocolateDistributionStations, "staffRequired != chocolateDistributionStations"); 
  
  C11 c11; // attempting to reference a deleted function C11 

  /* Template type parameter deduction with lvalues and rvalues */
  int caramel = 0; 
  func(0);
  func(caramel);
  int& mint = caramel; 
  func(mint);
  int&& nuts = 0;
  func(nuts);
  func(std::move(nuts));

  sum(1, 2, 3, 4, 5);  // = 15 
  sum(1, 2, 3);  // = 6
  sum(1.5, 2.0, 3.7);  // = 7.2 

  /* The mutable keyword allows modifying captured variables */
  int brokenChocolate = 1;
  auto foodBank1 = [&brokenChocolate] { brokenChocolate = 2; };
  //auto foodBank2 = [brokenChocolate] { brokenChocolate = 2; };  // Error 
  auto foodBank3 = [brokenChocolate]() mutable { brokenChocolate = 2; };

  /* Syntactic sugar for iterating over a container's elements */
  std::array<int, 5> chocolatePortions { 1, 2, 3, 4, 5 };
  for (int& chocolate_Portions : chocolatePortions) chocolate_Portions *= 2; // chocolatePortions == {2,4,6,8,10}
  for (int chocolate_Portions : chocolatePortions) chocolate_Portions *= 2;  // chocolatePortions == {1,2,3,4,5} 

  not_Packaged not_Packed;
  if (not_Packed) {}; 
  bool notpacked = not_Packed;
  yes_Packaged yes_Packed;
  if (yes_Packed) {};
  //bool yespacked = yes_Packed;  //error 

  return 0;
}
