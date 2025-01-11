#include <gtest/gtest.h>
#include <Board.hpp>
#include <Cell.hpp>
#include <ostream>
#include "TestUtilities.hpp"
using namespace chess;
TEST(QueenTest, movementTest) {
  const std::vector<std::vector<Cell>> intialBoardState{
      // clang-format off
/*0                                       1                         2                        3                          4                          5                           6                                 7*/
{Cell(Rook(Color::Black)),   Cell(Knight(Color::Black)), Cell(Bishop(Color::Black)), Cell(Queen(Color::Black)), Cell(King(Color::Black)),   Cell(Bishop(Color::Black)), Cell(Knight(Color::Black)), Cell(Rook(Color::Black))},//0
{Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black)), Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black))},//1
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//3
{Cell(),                     Cell(),                     Cell(Queen(Color::White)),  Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//4
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(Rook(Color::White)),   Cell(Knight(Color::White)), Cell(Bishop(Color::White)), Cell(Queen(Color::White)), Cell(King(Color::White)),   Cell(Bishop(Color::White)), Cell(Knight(Color::White)), Cell(Rook(Color::White))}//7
      // clang-format on
  };
  Board board{intialBoardState};
  const Position centerQueenPosition{4, 2};
  board.highlightMoves(centerQueenPosition);
  std::stringstream ss;
  ss << board;
  const std::string expectedMovement = test::readFileContents("resources/QueenMovementTest.txt");
  EXPECT_EQ(expectedMovement, ss.str());
}
TEST(QueenTest, centerQueenMovementTest) {
  const std::vector<std::vector<Cell>> intialBoardState{
      // clang-format off
/*0                                       1                         2                        3                          4                          5                           6                                 7*/
{Cell(),                     Cell(),                     Cell(),                     Cell(King(Color::Black)), Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//3
{Cell(),                     Cell(),                     Cell(Queen(Color::White)),  Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//4
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(Rook(Color::White)),   Cell(Knight(Color::White)), Cell(),                     Cell(Queen(Color::White)), Cell(King(Color::White)),   Cell(Bishop(Color::White)), Cell(Knight(Color::White)), Cell(Rook(Color::White))}//7
      // clang-format on
  };
  Board board{intialBoardState};
  const Position centerQueenPosition{4, 2};
  board.highlightMoves(centerQueenPosition);
  std::stringstream ss;
  ss << board;
  const std::string expectedMovement = test::readFileContents("resources/CenterQueenMovementTest.txt");
  EXPECT_EQ(expectedMovement, ss.str());
}
