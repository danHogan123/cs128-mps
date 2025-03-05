#include "illini_book.hpp"
#include <iostream>

int main() {
 // IlliniBook ib("./example/persons.csv", "./example/relations.csv");
 
  IlliniBook ib("/home/vagrant/src/mp11-illini-book-danHogan123/example/persons.csv"
  , "/home/vagrant/src/mp11-illini-book-danHogan123/example/relations.csv");

  //ib.WriteOut();
  // std::cout << ib.AreRelated(17, 2, "128") << std::endl;  
  // std::cout << ib.AreRelated(1, 2, "124") << std::endl;  
  // std::cout << ib.AreRelated(1, 6, "128") << std::endl;  
  // std::cout << ib.AreRelated(1, 6, "124") << std::endl; 


  // std::cout << ib.AreRelated(1, 2) << std::endl;         // true
  // std::cout << ib.AreRelated(3, 2) << std::endl;         // true
  // std::cout << ib.AreRelated(1, 9) << std::endl;  //false

  // std::cout << ib.AreRelated(1, 8, "128") << std::endl;         // true
  // std::cout << ib.AreRelated(1, 7,"128") << std::endl;         // flase
  //std::cout << ib.AreRelated(1, 9) << std::endl;



std::vector<int> steps = ib.GetSteps(1,1);
std::vector<int> step = ib.GetSteps(1,9);
std::vector<int> ste = ib.GetSteps(1,2);

for (auto& place : steps)
  std::cout << place;
std::cout << "" << std::endl;

for (auto& place : step)
  std::cout << place;
std::cout << "" << std::endl;

for (auto& place : ste)
  std::cout << place;
std::cout << "" << std::endl;




  return 0;
}
