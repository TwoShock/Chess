
#include <gtest/gtest.h>
#include <Board.hpp>
#include <Cell.hpp>
#include <ostream>
#include "TestUtilities.hpp"

using namespace chess;
TEST(PawnTest,
     GivenAPawnThatHasNotMoved_ExpectItCanMoveForwardOnceAndTwiceForFirstMove) {
  const Board board;
  const Position pawnStartPosition{6, 5};
  const Position cellInFront{5, 5};
  const Position cellTwoSpacesInFront{4, 5};
  const Pawn* pawn = board.getPiece<Pawn>(pawnStartPosition);
  EXPECT_TRUE(pawn->isFirstMove());
  const Moves moves = pawn->getPossibleMoves(pawnStartPosition, board);
  ASSERT_EQ(2u, moves.size());
  EXPECT_TRUE(moves.contains({pawnStartPosition, cellInFront}));
  EXPECT_TRUE(moves.contains({pawnStartPosition, cellTwoSpacesInFront}));
}

TEST(PawnTest, GivenAPawnThatHasMoved_ExpectItCanMoveForwardOnce) {
  const Board board;
  const Position pawnStartPosition{6, 5};
  const Position cellInFront{5, 5};
  Pawn* pawn = const_cast<Pawn*>(board.getPiece<Pawn>(pawnStartPosition));
  pawn->setIsFirstMove(false);
  EXPECT_FALSE(pawn->isFirstMove());

  const Moves moves = pawn->getPossibleMoves(pawnStartPosition, board);
  ASSERT_EQ(1u, moves.size());
  EXPECT_TRUE(moves.contains({pawnStartPosition, cellInFront}));
}

TEST(PawnTest,
     GivenAPawnThatHasAFriendlyPieceInFrontOfIt_ExpectItCanNotMoveForward) {
  Board board;
  const Position pawnStartPosition{6, 5};
  const Position cellInFront{5, 5};
  const Pawn* pawn = board.getPiece<Pawn>(pawnStartPosition);
  board.setPiece(cellInFront, Bishop(Color::White));

  const Moves moves = pawn->getPossibleMoves(pawnStartPosition, board);
  ASSERT_EQ(0u, moves.size());
}

TEST(PawnTest,
     GivenAPawnThatHasAEnemyPieceInFrontOfIt_ExpectItCanNotMoveForward) {
  Board board;
  const Position pawnStartPosition{6, 5};
  const Position cellInFront{5, 5};
  const Pawn* pawn = board.getPiece<Pawn>(pawnStartPosition);
  board.setPiece(cellInFront, Bishop(Color::Black));

  const Moves moves = pawn->getPossibleMoves(pawnStartPosition, board);
  ASSERT_EQ(0u, moves.size());
}

TEST(PawnTest,
     GivenAPawnWithTwoPotentialCaptureTargets_ExpectItCanMoveToCaptureBoth) {
  Board board;
  const Position pawnStartPosition{6, 5};
  const Position cellInFront{5, 5};
  const Position cellTwoSpacesInFront{4, 5};
  const Pawn* pawn = board.getPiece<Pawn>(pawnStartPosition);
  EXPECT_TRUE(pawn->isFirstMove());
  board.setPiece({5, 4}, Queen(Color::Black));
  board.setPiece({5, 6}, Pawn(Color::Black));
  const Moves moves = pawn->getPossibleMoves(pawnStartPosition, board);
  ASSERT_EQ(4u, moves.size());
  EXPECT_TRUE(moves.contains({pawnStartPosition, cellInFront}));
  EXPECT_TRUE(moves.contains({pawnStartPosition, cellTwoSpacesInFront}));
  EXPECT_TRUE(moves.contains({pawnStartPosition, {5, 4}}));
  EXPECT_TRUE(moves.contains({pawnStartPosition, {5, 6}}));
}

TEST(
    PawnTest,
    GivenAPawnWithTwoFriendlyTargetsInCapturePositions_ExpectItCannotMoveTheir) {
  Board board;
  const Position pawnStartPosition{6, 5};
  const Position cellInFront{5, 5};
  const Position cellTwoSpacesInFront{4, 5};
  const Pawn* pawn = board.getPiece<Pawn>(pawnStartPosition);
  EXPECT_TRUE(pawn->isFirstMove());
  board.setPiece({5, 4}, Queen(Color::White));
  board.setPiece({5, 6}, Pawn(Color::White));
  const Moves moves = pawn->getPossibleMoves(pawnStartPosition, board);
  ASSERT_EQ(2u, moves.size());
  EXPECT_TRUE(moves.contains({pawnStartPosition, cellInFront}));
  EXPECT_TRUE(moves.contains({pawnStartPosition, cellTwoSpacesInFront}));
}

TEST(PawnTest, BlackPawnForwardMovementAndCaptureTest) {
  Board board;
  const Position pawnStartPosition{1, 5};
  const Position cellInFront{2, 5};
  const Position cellTwoSpacesInFront{3, 5};
  const Pawn* pawn = board.getPiece<Pawn>(pawnStartPosition);
  EXPECT_TRUE(pawn->isFirstMove());
  Moves moves = pawn->getPossibleMoves(pawnStartPosition, board);
  ASSERT_EQ(2u, moves.size());
  EXPECT_TRUE(moves.contains({pawnStartPosition, cellInFront}));
  EXPECT_TRUE(moves.contains({pawnStartPosition, cellTwoSpacesInFront}));

  board.setPiece({2, 4}, Queen(Color::White));
  board.setPiece({2, 6}, Pawn(Color::White));
  moves = pawn->getPossibleMoves(pawnStartPosition, board);
  ASSERT_EQ(4u, moves.size());
  EXPECT_TRUE(moves.contains({pawnStartPosition, cellInFront}));
  EXPECT_TRUE(moves.contains({pawnStartPosition, cellTwoSpacesInFront}));
  EXPECT_TRUE(moves.contains({pawnStartPosition, {2, 4}}));
  EXPECT_TRUE(moves.contains({pawnStartPosition, {2, 6}}));
}

TEST(PawnTest, GivenAWhitePawnAndABlackPawnThatHasPassedItViaEnpassantFromTheLeft_ExpectItCanCaptureIt) {
  Board board;
  const Position pawnStartPosition{3, 5};
  const Position leftOfStartPosition{3, 4};
  const Position cellInFront{2, 5};
  Pawn pawn{Color::White};
  pawn.setIsFirstMove(false);
  board.setPiece(pawnStartPosition, pawn);

  Pawn pawnToTake{Color::Black};
  pawnToTake.setCanBeTakenByEnpassant(true);
  board.setPiece(leftOfStartPosition, pawnToTake);
  const Moves moves = pawn.getPossibleMoves(pawnStartPosition, board);
  EXPECT_EQ(2u, moves.size());
  EXPECT_TRUE(moves.contains({pawnStartPosition, cellInFront}));
  EXPECT_TRUE(moves.contains({pawnStartPosition, {2,4}}));
}

TEST(PawnTest, GivenAWhitePawnAndABlackPawnThatHasPassedItViaEnpassantFromTheRight_ExpectItCanCaptureIt) {
  Board board;
  const Position pawnStartPosition{3, 5};
  const Position rightOfStartPosition{3, 6};
  const Position cellInFront{2, 5};
  Pawn pawn{Color::White};
  pawn.setIsFirstMove(false);
  board.setPiece(pawnStartPosition, pawn);

  Pawn pawnToTake{Color::Black};
  pawnToTake.setCanBeTakenByEnpassant(true);
  board.setPiece(rightOfStartPosition, pawnToTake);
  const Moves moves = pawn.getPossibleMoves(pawnStartPosition, board);
  EXPECT_EQ(2u, moves.size());
  EXPECT_TRUE(moves.contains({pawnStartPosition, cellInFront}));
  EXPECT_TRUE(moves.contains({pawnStartPosition, {2,6}}));
}
