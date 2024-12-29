#include <gtest/gtest.h>
#include <Board.hpp>
#include <Cell.hpp>
#include <ostream>
#include "TestUtilities.hpp"
using namespace chess;

TEST(
    CheckTest,
    GivenRookAndQueenOfOppositeColorsFacingEachOther_AndGivenTheyHaveTheirKingsBehindThem_ExpectTheyCanNotMoveToTheSidesOrDiagonally) {
  const std::vector<std::vector<Cell>> intialBoardState{
      // clang-format off
/*0                                       1                         2                        3                          4                          5                           6                                 7*/
{Cell(),                     Cell(),                     Cell(),                     Cell(King(Color::Black)), Cell(),                     Cell(),                     Cell(),                     Cell()},//0
{Cell(),                     Cell(),                     Cell(),                     Cell(Rook(Color::Black)), Cell(),                     Cell(),                     Cell(),                     Cell()},//1
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//3
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//4
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(),                     Cell(),                     Cell(),                     Cell(Queen(Color::White)),Cell(),                     Cell(),                     Cell(),                     Cell()},//6
{Cell(),                     Cell(),                     Cell(),                     Cell(King(Color::White)), Cell(),                     Cell(),                     Cell(),                     Cell()},//7
      // clang-format on
  };
  Board board{intialBoardState};
  const Position queenPosition{6, 3};
  const Position rookPosition{1, 3};
  board.highlightMoves(queenPosition);
  std::stringstream ss;
  ss << board;
  const std::string expectedQueenMovement = test::readFileContents(
      "resources/"
      "GivenRookAndQueenOfOppositeColorsFacingEachOther_"
      "AndGivenTheyHaveTheirKingsBehindThem_QueenMoves.txt");
  EXPECT_EQ(expectedQueenMovement, ss.str());

  ss.str("");
  board.highlightMoves(rookPosition);
  ss << board;
  const std::string expectedRookMovement = test::readFileContents(
      "resources/"
      "GivenRookAndQueenOfOppositeColorsFacingEachOther_"
      "AndGivenTheyHaveTheirKingsBehindThem_RookMoves.txt");
  EXPECT_EQ(expectedRookMovement, ss.str());
}
