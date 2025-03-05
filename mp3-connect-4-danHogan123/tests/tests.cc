// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("Valid Drop", "[Disk_Placement]"){
  Board b;
  SECTION("drop in one col"){
  InitBoard(b);
    DropDiskToBoard(b,DiskType::kPlayer1,0);
 REQUIRE(b.board[0][0] == DiskType::kPlayer1);
  }
  SECTION("2 Disks 2 col"){
InitBoard(b);
  DropDiskToBoard(b,DiskType::kPlayer1,0);
  DropDiskToBoard(b,DiskType::kPlayer2,0);
  DropDiskToBoard(b,DiskType::kPlayer1,3);
  DropDiskToBoard(b,DiskType::kPlayer2,3);
  REQUIRE(b.board[0][0] == DiskType::kPlayer1);
  REQUIRE(b.board[1][0] == DiskType::kPlayer2);
  REQUIRE(b.board[0][3] == DiskType::kPlayer1);
  REQUIRE(b.board[1][3] == DiskType::kPlayer2);
  }

  SECTION("disk in full col"){
    InitBoard(b);
    DropDiskToBoard(b,DiskType::kPlayer1,0);
    DropDiskToBoard(b,DiskType::kPlayer1,0);
    DropDiskToBoard(b,DiskType::kPlayer1,0);
    DropDiskToBoard(b,DiskType::kPlayer1,0);
    DropDiskToBoard(b,DiskType::kPlayer1,0);
    DropDiskToBoard(b,DiskType::kPlayer1,0);
    REQUIRE_THROWS_AS(DropDiskToBoard(b,DiskType::kPlayer1,0),std::runtime_error);
  }
  SECTION("dist out of bounds"){
    REQUIRE(BoardLocationInBounds(2,4));
    REQUIRE(BoardLocationInBounds(1,5));
    REQUIRE(BoardLocationInBounds(0,6));
    REQUIRE_FALSE(BoardLocationInBounds(7,0));
    REQUIRE_FALSE(BoardLocationInBounds(-7,0));
    REQUIRE_FALSE(BoardLocationInBounds(0,98));
  }
  }

TEST_CASE("search and check", "[winners]"){
   Board b;
   SECTION("horizontal"){
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  REQUIRE(CheckForWinner(b,DiskType::kPlayer1));
  REQUIRE(SearchForWinner(b,DiskType::kPlayer1,WinningDirection::kHorizontal));
  REQUIRE_FALSE(CheckForWinner(b,DiskType::kPlayer2));
  REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer2,WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer1,WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer1,WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer1,WinningDirection::kRightDiag));}

  
  SECTION("vertical"){
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  REQUIRE(CheckForWinner(b,DiskType::kPlayer2));
  REQUIRE_FALSE(CheckForWinner(b,DiskType::kPlayer1));
  REQUIRE(SearchForWinner(b,DiskType::kPlayer2,WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer1,WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer2,WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer2,WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer2,WinningDirection::kLeftDiag));
  }


  SECTION("right diag"){
  
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);

  REQUIRE(CheckForWinner(b,DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(b,DiskType::kPlayer2));
  REQUIRE(SearchForWinner(b,DiskType::kPlayer1,WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer2,WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer2,WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer2,WinningDirection::kHorizontal));
  }

   SECTION("left diag"){
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);

  REQUIRE(CheckForWinner(b,DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(b,DiskType::kPlayer2));
  REQUIRE(SearchForWinner(b,DiskType::kPlayer1,WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer2,WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer2,WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer2,WinningDirection::kHorizontal));
  }

  SECTION("no winners"){
    InitBoard(b);
    DropDiskToBoard(b,DiskType::kPlayer1,1);
    DropDiskToBoard(b,DiskType::kPlayer2,2);

    REQUIRE_FALSE(CheckForWinner(b,DiskType::kPlayer1));
    REQUIRE_FALSE(CheckForWinner(b,DiskType::kPlayer1));

    REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer1,WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer1,WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer1,WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer1,WinningDirection::kRightDiag));

     REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer2,WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer2,WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer2,WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(b,DiskType::kPlayer2,WinningDirection::kRightDiag));

  }
}

/////////////////////////////////////////////////////////////////////////////////////////////