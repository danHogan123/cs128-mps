#ifndef WORDSEARCHSOLVER_HPP
#define WORDSEARCHSOLVER_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "WordLocation.hpp"

// WordLocation SearchHorizontal(std::string str);


enum class CheckDirection { kHorizontal, kVertical, kLeftDiag, kRightDiag };

class WordSearchSolver {
public:
  WordSearchSolver(const std::vector<std::vector<char>>& puzzle);
  WordLocation FindWord(const std::string& word);
  WordLocation FindWord(const std::string& word, CheckDirection direction);

  WordLocation SetHoriz(const std::string& word,unsigned int r, unsigned int c);
  WordLocation SetVert(const std::string& word,unsigned int r, unsigned int c);
  WordLocation SetRDiag(const std::string& word,unsigned int r, unsigned int c);
  WordLocation SetLDiag(const std::string& word,unsigned int r, unsigned int c);


  bool SearchHorizontal(const std::string& word, unsigned int r, unsigned int c);
  bool SearchVertical(const std::string& word, unsigned int r, unsigned int c);
  bool SearchRDiag(const std::string& word, unsigned int r, unsigned int c);
  bool SearchLDiag(const std::string& word, unsigned int r, unsigned int c);




private:
  bool LocationInBounds(size_t row, size_t col) const;
  std::vector<std::vector<char>> puzzle_;
  size_t puzzle_height_;
  size_t puzzle_width_;
};

#endif