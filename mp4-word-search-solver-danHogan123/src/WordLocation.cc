#include "WordLocation.hpp"

//do not modify

std::ostream& operator<<(std::ostream& os, const WordLocation& wl) {
  os << wl.word << '\n';
  for (const auto& cp : wl.char_positions) os << cp;
  return os;
}