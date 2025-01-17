#include <gtest/gtest.h>
#include <Board.hpp>
#include <Cell.hpp>
#include <ostream>
#include "TestUtilities.hpp"
using namespace chess;
TEST(RookTest, movementTest) {
  const std::vector<std::vector<Cell>> intialBoardState{
      // clang-format off
/*0                                       1                         2                        3                          4                          5                           6                                 7*/
{Cell(Rook(Color::Black)),   Cell(Knight(Color::Black)), Cell(Bishop(Color::Black)), Cell(Queen(Color::Black)), Cell(King(Color::Black)),   Cell(Bishop(Color::Black)), Cell(Knight(Color::Black)), Cell(Rook(Color::Black))},//0
{Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black)), Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black))},//1
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//3
{Cell(),                     Cell(),                     Cell(Rook(Color::White)),   Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//4
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(Rook(Color::White)),   Cell(Knight(Color::White)), Cell(Bishop(Color::White)), Cell(Queen(Color::White)), Cell(King(Color::White)),   Cell(Bishop(Color::White)), Cell(Knight(Color::White)), Cell(Rook(Color::White))}//7
      // clang-format on
  };
  Board board{intialBoardState};
  const Position centerRookPosition{4, 2};
  board.highlightMoves(centerRookPosition);
  std::stringstream ss;
  ss << board;
  const std::string expectedMovement = test::readFileContents("resources/RookMovementTest.txt");
  EXPECT_EQ(expectedMovement, ss.str());
}
