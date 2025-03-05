#include <iostream>
#include <string>


#include "functions.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./bin/exec word" << std::endl;
    return 1;
  }
 

  std::string word = argv[1];
 // std::cout << "input = " << word << std::endl;
  std::string small = MakeLower(word);

//checks for valid characters
 // std::cout << "lowercase word = " << small << std::endl;
   for(unsigned int i=0; i<word.size();i++){
     if (small[i] != 'a' && small[i] != 'e'&& small[i] != 'i' && small[i] != 'o' && small[i] != 'u' && small[i] != 'p' &&small[i] != 'k' && small[i] != 'h' && small[i] != 'l' && small[i] !='m' && small[i]!='n' && small[i]!='w' && small[i] != ' ' && small[i] != '\'' ){
         std::cout << word <<" contains a character not a part of the Hawaiian language." << std::endl;
         return 1;}
  }
     std::string x = ChangePro(small);
  //  std::cout << x << std::endl;

 
  std::string phonetics = TakeOff(x);
  std::cout << phonetics << std::endl;
}