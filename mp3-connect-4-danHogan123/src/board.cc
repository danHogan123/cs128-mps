#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  // below was minimal to get tests to actually compile and given test case to
  // fail
  BoardToStr(b);
  for(unsigned int i=0; i<Board::kBoardHeight;i++){
    for(unsigned int j=0; j<Board::kBoardWidth;j++){
      b.board[i][j] = DiskType::kEmpty;
    }
  }

//  if(CheckForWinner(b,DiskType::kPlayer1)){
//   std::cout << "horray" << std::endl;
//  }
  std::cout << (BoardToStr(b)) << std::endl;


}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}

void DropDiskToBoard(Board& b, DiskType disk, int col){
 const int kFive = 5;
 for(int i=0;i<Board::kBoardHeight;++i){
  if(i==kFive){
  throw std::runtime_error("uggh no more room");
  }
  if(!BoardLocationInBounds(i,col)){
    throw std::runtime_error("missed the slot");
  }
 if(b.board[i][col]==DiskType::kEmpty){
   b.board[i][col]= disk;
   break;
 } 
 } 
  }


  bool CheckForWinner(Board& b, DiskType disk){

 bool verified = false;

if(SearchForWinner(b,disk,WinningDirection::kHorizontal)){
   verified = true;
}
if(SearchForWinner(b,disk,WinningDirection::kVertical)){
  verified = true;
}
if(SearchForWinner(b,disk,WinningDirection::kLeftDiag)){
  verified = true;
}
if(SearchForWinner(b,disk,WinningDirection::kRightDiag)){
  verified = true;
}
return verified;
}

  
  bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check){
    bool verified = false;

if( to_check == WinningDirection::kHorizontal){
verified = CheckHoriz(b,disk);
 }

if( to_check == WinningDirection::kVertical){
verified = CheckVert(b,disk);
}

if( to_check == WinningDirection::kLeftDiag){
verified = CheckLeftDiag(b,disk);
}

if( to_check == WinningDirection::kRightDiag){
verified = CheckRightDiag(b,disk);
}
  return verified;
}

bool CheckHoriz(Board& b, DiskType disk){
  bool ret_boo = false;
    for(unsigned int i=0; i<Board::kBoardHeight;++i){
    for(unsigned int j=0; j<4;++j){
     if((b.board[i][j]==disk) && (b.board[i][j+1]==disk)  && (b.board[i][j+2]==disk)  && (b.board[i][j+3]==disk)){
      ret_boo = true; }
    }
  }
  return ret_boo;
}

bool CheckVert(Board& b, DiskType disk){
    bool ret_boo = false;
    for(unsigned int i=0; i<4;++i){
    for(unsigned int j=0; j<Board::kBoardWidth;++j){
     if((b.board[i][j]==disk) && (b.board[i+1][j]==disk)  && (b.board[i+2][j]==disk)  && (b.board[i+3][j]==disk)){
      ret_boo = true; }
    }
  }
  return ret_boo;
}


bool CheckLeftDiag(Board& b, DiskType disk){
   bool ret_boo = false;
    for(unsigned int i=0; i<Board::kBoardHeight;++i){
    for(unsigned int j=3; j<Board::kBoardWidth;++j){ 
         if(b.board[i][j]==disk){
       if((b.board[i+1][j-1]==disk) && (b.board[i+2][j-2]==disk) && (b.board[i+3][j-3]==disk)){
      ret_boo = true; }
        }}

    }
    
  return ret_boo;
}

bool CheckRightDiag(Board& b, DiskType disk){
  bool ret_boo = false;
    for(unsigned int i=0; i<Board::kBoardHeight;++i){
    for(unsigned int j=0; j<4;++j){
     if((b.board[i][j]==disk) && (b.board[i+1][j+1]==disk)  && (b.board[i+2][j+2]==disk)  && (b.board[i+3][j+3]==disk)){
      ret_boo = true; }
    }
  }
  return ret_boo;
}





  bool BoardLocationInBounds(int row, int col){
   bool bounds = false;
   if( (row<Board::kBoardHeight) && (row>=0) && (col<Board::kBoardWidth) && (col>=0)){
   bounds = true;}
   return bounds;
  }

