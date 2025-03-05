#include <iostream>

#include "circular-linked-list.hpp"

int main()
{
    CircularLinkedList<int> cll;
  //  std::cout << "cll" << cll << std::endl;

    cll.InsertInOrder(38);
    cll.InsertInOrder(36);
    cll.InsertInOrder(32);
    cll.InsertInOrder(16);


  //  cll.ChangeDirection();
std::cout << cll << std::endl;
    cll.Reverse();

//  std::cout << cll << std::endl;
    std::cout << cll << std::endl;

    // CircularLinkedList<int> cll2;
    // std::cout << "cll2--" << cll2 << std::endl;

     //cll2 = cll;
//         std::cout << "poop" << std::endl;

   // std::cout << cll2 << std::endl;

}
