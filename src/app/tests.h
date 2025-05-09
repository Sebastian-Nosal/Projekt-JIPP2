#include <SmartArray.h>
#include <iostream>

class Pizza {
private:
 int id;
 bool avaible;
 std::string name;
 float price;
 SmartArray<string> ingredients;
 

 public:
 Pizza(std::string pizzaName,SmartArray<string> pizzaIngredients, float pizzaPrice, bool isActive);
  
};