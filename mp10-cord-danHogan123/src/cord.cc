#include "cord.hpp"

#include <stdexcept>

#include "cord_utilities.hpp"

Cord::Cord(std::string_view sv)
{
    if (sv.empty()) {throw std::invalid_argument("");}

    length_ = sv.size();
    data_ = new char[sv.size()+1];
    for (unsigned int i = 0; i<length_; ++i)
    {
        data_[i] = sv[i];
       // std::cout << sv[i] << std::endl;
    }
    data_[length_] = '\0';
}

Cord::~Cord()
{
    delete[] data_;
    data_ = nullptr;
}



std::string Cord::StringHelp() const {
   std::string result;
  if (data_ != nullptr && data_[0] != '\0') {
    result += data_;
  } else {
    result += left_->StringHelp();
    result += right_->StringHelp();
  }
  return result;
}




SharedPointer<char> Cord::ToString() const
{
std::string str = StringHelp();
//std::cout << str << std::endl;
char* letters = new char[str.length()+1];

for(unsigned int i =0; i<str.length(); i++)
    letters[i] = str[i];
letters[str.length()] = '\0';
SharedPointer<char> word(letters);

return word;
}




