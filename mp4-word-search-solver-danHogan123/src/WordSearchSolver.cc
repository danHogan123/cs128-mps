#include "WordSearchSolver.hpp"


bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

WordSearchSolver::WordSearchSolver(const std::vector<std::vector<char>>& puzzle):puzzle_(puzzle){
  puzzle_height_= puzzle.size();
  puzzle_width_ = puzzle[1].size();
}


WordLocation WordSearchSolver::FindWord(const std::string& word){
  WordLocation ret_loc{};
 
 for(unsigned int i=0;i<puzzle_height_;++i){
    for(unsigned int j=0; j<puzzle_width_;++j){
      if(SearchHorizontal(word,i,j)){
        return FindWord(word, CheckDirection::kHorizontal);
      }
      if(SearchVertical(word,i,j)){
        return FindWord(word, CheckDirection::kVertical);
      }
      if(SearchRDiag(word,i,j)){
        return FindWord(word, CheckDirection::kRightDiag);
      }
      if(SearchLDiag(word,i,j)){
        return FindWord(word, CheckDirection::kLeftDiag);
      }

    }
  }
  return ret_loc;
  }


WordLocation WordSearchSolver::FindWord(const std::string& word, CheckDirection direction){

WordLocation ret_loc{};
// std::vector<char> word_to_charvec;
// for( size_t i=0; i<word.length();++i){
//   word_to_charvec.push_back(word.at(i));
// }



 if(direction == CheckDirection::kHorizontal){
  for(unsigned int i=0;i<puzzle_height_;++i){
    for(unsigned int j=0; j<puzzle_width_;++j){
     if(SearchHorizontal(word,i,j)){
        return SetHoriz(word,i,j);
      }}}}

       if(direction == CheckDirection::kVertical){
  for(unsigned int i=0;i<puzzle_height_;++i){
    for(unsigned int j=0; j<puzzle_width_;++j){
      if(SearchVertical(word,i,j)){
        return SetVert(word,i,j);
      }}}}


 if(direction == CheckDirection::kRightDiag){
  for(unsigned int i=0;i<puzzle_height_;++i){
    for(unsigned int j=0; j<puzzle_width_;++j){
      if(SearchRDiag(word,i,j)){
        return SetRDiag(word,i,j);
      }}}}


if (direction == CheckDirection::kLeftDiag){
  for(unsigned int i=0;i<puzzle_height_;++i){
    for(unsigned int j=0; j<puzzle_width_;++j){
      if(SearchLDiag(word,i,j)){
        return SetLDiag(word,i,j);
      }}}} 
       return ret_loc;
}


  WordLocation WordSearchSolver::SetHoriz(const std::string& word,unsigned int r, unsigned int c){
    WordLocation ret_loc{};
    ret_loc.word = word;
    for( unsigned int i=0; i<word.length();++i){
    CharPositions temp_c{word[i],r,c+i};
    ret_loc.char_positions.push_back(temp_c);
    }
return ret_loc;
  }

  WordLocation WordSearchSolver::SetVert(const std::string& word,unsigned int r, unsigned int c){
 WordLocation ret_loc{};
    ret_loc.word = word;
    for(unsigned int i=0; i<word.length();++i){
    CharPositions temp_c{word[i],r+i,c};
    ret_loc.char_positions.push_back(temp_c);
    }
return ret_loc;
  }

  WordLocation WordSearchSolver::SetRDiag(const std::string& word,unsigned int r, unsigned int c){
 WordLocation ret_loc{};
    ret_loc.word = word;
    for( unsigned int i=0; i<word.length();++i){
    CharPositions temp_c{word[i],r+i,c+i};
    ret_loc.char_positions.push_back(temp_c);
    }
return ret_loc;
  }

  WordLocation WordSearchSolver::SetLDiag(const std::string& word,unsigned int r, unsigned int c){
 WordLocation ret_loc{};
    ret_loc.word = word;
    for( unsigned int i=0; i<word.length();++i){
    CharPositions temp_c{word[i],r+i,c-i};
    ret_loc.char_positions.push_back(temp_c);
    }
return ret_loc;
  }









bool WordSearchSolver::SearchHorizontal(const std::string& word,unsigned int r, unsigned int c){
  for(unsigned int i=0;i<word.length();++i){
    if(!LocationInBounds(r,c+i) || puzzle_[r][c+i] != word[i]){
      return false;
    }
  }
  return true;
}

bool WordSearchSolver::SearchVertical(const std::string& word,unsigned int r, unsigned int c){
  for(unsigned int i=0;i<word.length();++i){
    if(!LocationInBounds(r+i,c) || puzzle_[r+i][c] != word[i]){
      return false;
    }
  }
  return true;
}

bool WordSearchSolver::SearchLDiag(const std::string& word,unsigned int r, unsigned int c){
  for(unsigned int i=0;i<word.length();++i){
    if(!LocationInBounds(r+i,c-i) || puzzle_[r+i][c-i] != word[i]){
      return false;
    }
  }
  return true;
}

bool WordSearchSolver::SearchRDiag(const std::string& word,unsigned int r, unsigned int c){
  for(unsigned int i=0;i<word.length();++i){
    if(!LocationInBounds(r+i,c+i) || puzzle_[r+i][c+i] != word[i]){
      return false;
    }
  }
  return true;
}

