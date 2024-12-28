#include <gtest/gtest.h>
#include <Board.hpp>
#include <Cell.hpp>
#include <ostream>
#include "TestUtilities.hpp"
using namespace chess;
TEST(KingTest, movementTest) {
  const std::vector<std::vector<Cell>> intialBoardState{
      // clang-format off
/*0                                       1                         2                        3                          4                          5                           6                                 7*/
{Cell(Rook(Color::Black)),   Cell(Knight(Color::Black)), Cell(Bishop(Color::Black)), Cell(Queen(Color::Black)), Cell(King(Color::Black)),   Cell(Bishop(Color::Black)), Cell(Knight(Color::Black)), Cell(Rook(Color::Black))},//0
{Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black)), Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black))},//1
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(Pawn(Color::Black)), Cell(),                     Cell(),                     Cell(),                     Cell()},//3
{Cell(),                     Cell(),                     Cell(King(Color::White)),   Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//4
{Cell(),                     Cell(),                     Cell(),                     Cell(Pawn(Color::White)), Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(Rook(Color::White)),   Cell(Knight(Color::White)), Cell(Bishop(Color::White)), Cell(Queen(Color::White)),Cell(),                     Cell(Bishop(Color::White)), Cell(Knight(Color::White)), Cell(Rook(Color::White))}//7
      // clang-format on
  };
  Board board{intialBoardState};
  const Position centerKingPosition{4, 2};
  board.highlightMoves(centerKingPosition);
  std::stringstream ss;
  ss << board;
  const std::string expectedMovement = test::readFileContents("resources/KingMovementTest.txt");
  EXPECT_EQ(expectedMovement, ss.str());
}
