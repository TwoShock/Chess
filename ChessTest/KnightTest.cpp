
#include <gtest/gtest.h>
#include <Board.hpp>
#include <Cell.hpp>
#include <ostream>
#include "TestUtilities.hpp"

using namespace chess;
namespace {

auto expectKnightPossibleMovesGivenStartingPosition =
    [](Position position, const Board& board, std::vector<Move> expectedMoves) {
      const Knight* knight = board.getPiece<Knight>(position);
      Moves moves = knight->getPossibleMoves(position, board);
      ASSERT_EQ(expectedMoves.size(), moves.size());
      for (const auto move : expectedMoves) {
        EXPECT_TRUE(moves.contains(move));
      }
    };
}  // namespace
TEST(KnightTest, CheckAllKnightPossibleMovesAtTheStartOfTheGame) {
  const Board board;

  const Position leftWhiteKnightPos{7, 1};
  const Position rightWhiteKnightPos{7, 6};
  const Position leftBlackKnightPos{0, 1};
  const Position rightBlackKnightPos{0, 6};
  const Knight* leftWhiteKnight = board.getPiece<Knight>(leftWhiteKnightPos);

  expectKnightPossibleMovesGivenStartingPosition(
      leftWhiteKnightPos, board,
      {Move{leftWhiteKnightPos, {5, 0}}, Move{leftWhiteKnightPos, {5, 2}}});

  expectKnightPossibleMovesGivenStartingPosition(
      rightWhiteKnightPos, board,
      {Move{rightWhiteKnightPos, {5, 5}}, Move{rightWhiteKnightPos, {5, 7}}});

  expectKnightPossibleMovesGivenStartingPosition(
      leftBlackKnightPos, board,
      {Move{leftBlackKnightPos, {2, 0}}, Move{leftBlackKnightPos, {2, 2}}});

  expectKnightPossibleMovesGivenStartingPosition(
      rightBlackKnightPos, board,
      {Move{rightBlackKnightPos, {2, 5}}, Move{rightBlackKnightPos, {2, 7}}});
}

TEST(
    KnightTest,
    GivenAKnightPlacedInTheCenter_AndGivenTwoPotentialCaptures_ExpectMovementIsPossible) {
    //the other two moves are blocked by a piece of the same color thats why only two moves are possible
  const std::vector<std::vector<Cell>> intialBoardState{
      // clang-format off
		{Cell(Rook(Color::Black)),Cell(Knight(Color::Black)),Cell(Bishop(Color::Black)),Cell(Queen(Color::Black)),Cell(King(Color::Black)),Cell(Bishop(Color::Black)),Cell(Knight(Color::Black)),Cell(Rook(Color::Black))},
		{Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
		{Cell(Pawn(Color::Black)),Cell(Pawn(Color::Black)),Cell(Pawn(Color::Black)),Cell(Pawn(Color::Black)),Cell(Pawn(Color::Black)),Cell(Pawn(Color::Black)),Cell(Pawn(Color::Black)),Cell(Pawn(Color::Black))},
		{Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
		{Cell(),Cell(),Cell(),Cell(Knight(Color::Black)),Cell(),Cell(),Cell(),Cell()},
		{Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
		{Cell(Pawn(Color::White)),Cell(Pawn(Color::White)),Cell(Pawn(Color::White)),Cell(Pawn(Color::White)),Cell(Pawn(Color::White)),Cell(Pawn(Color::White)),Cell(Pawn(Color::White)),Cell(Pawn(Color::White))},
		{Cell(Rook(Color::White)),Cell(Knight(Color::White)),Cell(Bishop(Color::White)),Cell(Queen(Color::White)),Cell(King(Color::White)),Cell(Bishop(Color::White)),Cell(Knight(Color::White)),Cell(Rook(Color::White))}
      // clang-format on
  };
  const Board board{intialBoardState};
  const Position knightPos{4, 3};
  const Knight* knight = board.getPiece<Knight>(knightPos);
  expectKnightPossibleMovesGivenStartingPosition(
      knightPos, board, {{{knightPos, {6, 2}}, {knightPos, {6, 4}}}});
}